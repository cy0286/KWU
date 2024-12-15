#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <asm/syscall_wrapper.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/sched/mm.h>
#include <linux/mm_types.h>

#define __NR_ftrace 336

typedef asmlinkage int (*syscall_ptr_t)(const struct pt_regs *regs);
syscall_ptr_t *syscall_table;
syscall_ptr_t real_ftrace;

struct task_struct *t;
struct mm_struct *mm;
struct vm_area_struct *mmap;
char path[100];

static asmlinkage int file_varea(const struct pt_regs *regs)
{	
	pid_t pid = regs->di;
    	
	struct task_struct *findtask = &init_task;
    while (findtask->pid != pid) 
	{
    	findtask = next_task(findtask);
        if (findtask == &init_task) 
		{
			return -1;
		}
    }
	
	t = pid_task(find_vpid(pid), PIDTYPE_PID);
	mm = get_task_mm(t);
	mmap = mm->mmap;	

	// Print information
    printk("######## Loaded files of a process '%s(%d)' in VM ########\n", findtask->comm, findtask->pid);
	
	while(mmap!=NULL)
	{
		if(mmap->vm_file)
		{
			printk("mem[%lx~%lx] code[%lx~%lx] data[%lx~%lx] heap[%lx~%lx] %s\n",
			mmap->vm_start, mmap->vm_end, mm->start_code, mm->end_code, mm->start_data, mm->end_data, 
			mm->start_brk, mm->brk, d_path(&mmap->vm_file->f_path, path, 100));
		}
		mmap = mmap->vm_next;
	}
	printk("################################################################\n");
	return pid;
}

void make_rw(void *addr)
{
	unsigned int level;
	pte_t *pte = lookup_address((u64)addr, &level);
	if(pte->pte &~ _PAGE_RW)
		pte->pte |= _PAGE_RW;
}

void make_ro(void *addr)
{
	unsigned int level;
	pte_t *pte = lookup_address((u64)addr, &level);
	pte->pte = pte->pte &~ _PAGE_RW;
}

asmlinkage int __init hooking_init(void)
{
	syscall_table = (syscall_ptr_t *) kallsyms_lookup_name("sys_call_table");
	
	make_rw(syscall_table);
	real_ftrace = syscall_table[__NR_ftrace];
	syscall_table[__NR_ftrace] = file_varea;

	return 0;	
}

asmlinkage void __exit hooking_exit(void)
{
	syscall_table[__NR_ftrace] = real_ftrace;
	make_ro(syscall_table);
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");


