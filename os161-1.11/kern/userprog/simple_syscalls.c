#include <stdio.h>
#include <unistd.h>
#include <syscall.h>

/*
* System Call used to exit out of infinite loop
*/
void sys_exit(int exitCode) {
	kprintf("sjfsdfsdfs %d", exitCode);
}

/*
* System Call that accepts and integer and prints it
* using the internal kprintf().
*
* return: 1 if the integer is a multiple of 4
*         0 otherwise
*/
int sys_printint(int c) {

}

/*
* System Call that accepts a string and length of the string and prints
* the reverse of the string using the internal kprintf().
*
* return: 1 if the length of the string is multiple of 2
*         0 otherwise
*/
int sys_reversestring(const char *str, int len) {

}

