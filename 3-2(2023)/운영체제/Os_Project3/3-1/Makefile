all:
	gcc -o numgen numgen.c
	gcc -o fork fork.c -pthread
	gcc -o thread thread.c -pthread
clean:
	$ rm -rf tmp*
	$ sync
	$ echo 3 | sudo tee /proc/sys/vm/drop_caches

