This is a small shell program that I created for my Operating Systems class.
This program is to perform various shell functions using the fork() system call that you would use in a command line, such as
exit, cd, showpid, and ls.


Files:
	Makefile - The Makefile to run the program.
	test.c - The main program. 

Instructions to compile: Type make to create the Makefile contents and the executable for the program. 

Instructions for running: Run the program by typing ./test

Challenges encountered: While trying to make this program, I encountered the main problem of
			the error message printing when I try to execute the built-in commands cd and showpid.
			The two commands do work as intended, but they also get an error message even if they were successful.
			Another challenge I encountered was with showpid only showing me 2 processes.

Sources used:
	https://www.geeksforgeeks.org/fork-system-call/
	http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/exec.html
	https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
	https://www.geeksforgeeks.org/getppid-getpid-linux/
