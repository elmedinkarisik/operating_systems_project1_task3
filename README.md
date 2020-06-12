1)  Group members:
	-Dinko Omeragić
	-Elmedin Karišik
	-Faris Šahović
	-Mirza Nikšić

2)  Files/directories in submission:
	-Makefile
	-shell
	-shell.c
	-test_file.txt
	-README.md

3)  Q1: If we have a single-core, uniprocessor system that supports multiprogramming, how many processes can be in a running state in such system, at any given time?
    A1: In such a system, there can be only one process in a running state.

    Q2: Explain why are system calls needed for shared memory method of inter-process communication (IPC). If there are multiple threads in one process, are the system calls needed for sharing memory between those threads?
    A2: Because we have to establish a mapping between process' address spaces to a named memory object that may be shared across processes and in Linux, that is done using the mmap system call. No, system calls are not needed, because threads within one process share memory space and they don't involve the kernel.

4)  We have created a shell that can be run in the terminal. Within the shell, we have implemented 9 commands (7 commands given in the task and 2 helper commands, 'help' and 'exit'). 

5)  If you do not have the shell file compiled, you can compile it by running 'make' in the terminal of the directoy where shell.c resides. If you wish to remove the compiled shell file, you can run 'make clean' in the terminal of said directory. 
    The shell can be opened by typing './shell' in the terminal of the directory where the shell file is located. Within the shell, you can run the 'help', which will give you a list of all commands implemented. You can also run 'exit' to get out of the shell.
    And of course, you can run our custom commands.
    How to run them:
	$ countChar /path/to/file
	$ countLines /path/to/file
	$ countWords /path/to/file
	$ camelCase /path/to/file
	$ countOccur /path/to/file string_to_search
	$ toUpperCase /path/to/file
	$ toLowerCase /path/to/file

6)  It was rather challenging to get back to programming in C. Especially with the camelCase method, because it requires a lot of work with pointers. 

7)  sources:
	-labs and lectures
	-https://brennan.io/2015/01/16/write-a-shell-in-c/
	-https://stackexchange.com/
	-https://stackoverflow.com/
   
