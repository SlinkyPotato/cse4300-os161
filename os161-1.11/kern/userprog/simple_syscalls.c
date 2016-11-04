#include <stdio.h>
#include <unistd.h>
#include <syscall.h>

/*
* System Call used to exit out of infinite loop
*/
void sys_exit(int exitCode) {
	if (curthread->t_stack != NULL) {
			/*
			 * Check the magic number we put on the bottom end of
			 * the stack in thread_fork. If these assertions go
			 * off, it most likely means you overflowed your stack
			 * at some point, which can cause all kinds of
			 * mysterious other things to happen.
			 */
			assert(curthread->t_stack[0] == (char)0xae);
			assert(curthread->t_stack[1] == (char)0x11);
			assert(curthread->t_stack[2] == (char)0xda);
			assert(curthread->t_stack[3] == (char)0x33);
		}

	splhigh();

	if (curthread->t_vmspace) {
		/*
		 * Do this carefully to avoid race condition with
		 * context switch code.
		 */
		struct addrspace *as = curthread->t_vmspace;
		curthread->t_vmspace = NULL;
		as_destroy(as);
	}

	if (curthread->t_cwd) {
		VOP_DECREF(curthread->t_cwd);
		curthread->t_cwd = NULL;
	}

	assert(numthreads>0);
	numthreads--;
	mi_switch(S_ZOMB);

	panic("Thread came back from the dead!\n");
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

