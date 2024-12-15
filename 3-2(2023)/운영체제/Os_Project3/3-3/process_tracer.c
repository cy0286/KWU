#include <linux/module.h>
#include <linux/highmem.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <asm/syscall_wrapper.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

#define __NR_ftrace 336

typedef asmlinkage int (*syscall_ptr_t)(const struct pt_regs *regs);
syscall_ptr_t *syscall_table;
syscall_ptr_t real_ftrace;

static asmlinkage int process_tracer(const struct pt_regs *regs)
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
	// Process Name
    	printk("##### TASK INFORMATION of '[%d] %s' #####\n", findtask->pid, findtask->comm);

	// Current Process Status
	 if(findtask->state == TASK_RUNNING)
	{
    		printk(" - task state : Running or ready\n");
  	}
  	else if(findtask->state == TASK_INTERRUPTIBLE)
	{
   	 	printk(" - task state : Wait with ignoring all signals\n");
  	}
  	else if(findtask->state == TASK_UNINTERRUPTIBLE)
	{
		printk(" - task state : Wait\n");
  	}
  	else if(findtask->state == TASK_STOPPED)
	{
    		printk(" - task state : Stopped\n");
  	}
  	else if(findtask->exit_state == EXIT_ZOMBIE)
	{
    		printk(" - task state : Zombie process\n");   
  	}  
  	else if(findtask->exit_state == EXIT_DEAD)
	{
    		printk(" - task state : Dead\n");
  	}   
	else
	{
    		printk(" - task state : etc\n");
  	}

	// Process Group Information
	struct task_struct *group = findtask->group_leader;
	printk(" - Process Group Leader : [%d] %s\n", group->pid, group->comm);   
    	
	// Number of context switches in the process
	printk(" - Number of context switches : %d\n", findtask->nvcsw);

	// Number of forks calls
	printk(" - Number of calling fork() : %d\n", findtask->fork_count);

	// Parent Process Information
	struct task_struct *parent = findtask->parent;
	printk(" - its parent process : [%d] %s\n", parent->pid, parent->comm); 
	
	// Sibling Process Information  
	struct task_struct *sibling;
	struct list_head *sibling_list;
	int sibling_count = 0;

	printk(" - its sibling process(es) :\n");
	list_for_each(sibling_list, &findtask->parent->children)
	{
		sibling = list_entry(sibling_list, struct task_struct, sibling);
		if(sibling->pid != pid)
		{
			printk("     > [%d] %s\n", sibling->pid, sibling->comm);
			sibling_count++;
		}
	}
	
	if(sibling_count == 0)
	{
		printk("     > It has no sibling.\n");
	}
	else
	{
		printk("     > This process has %d sibling process(es)\n", sibling_count);
	}

	// Child Process Information
	struct task_struct *children;
	struct list_head *child_list;
	int child_count = 0;
	
	printk(" - its child process(es) :\n");
	list_for_each(child_list, &findtask->children)
	{
		children = list_entry(child_list, struct task_struct, sibling);
		if(sibling->pid != pid)
		{
			printk("     > [%d] %s\n", children->pid, children->comm);
			child_count++;
		}
	}
	
	if(child_count == 0)
	{
		printk("     > It has no child.\n");
	}
	else
	{
		printk("     > This process has %d child process(es)\n", child_count);
	}
	
	printk("##### END of INFORMATION #####\n");

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
	syscall_table[__NR_ftrace] = process_tracer;

	return 0;	
}

asmlinkage void __exit hooking_exit(void)
{
	make_rw(syscall_table);
	syscall_table[__NR_ftrace] = real_ftrace;
	make_ro(syscall_table);
}

module_init(hooking_init);
module_exit(hooking_exit);
MODULE_LICENSE("GPL");


