#ifndef _SYSCALL_H_
#define _SYSCALL_H_

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);

void sys_exit(int exitCode); // assn3

int sys_printint(int c); // assn3

int sys_reversestring(const char *str, int len); // assn3

#endif /* _SYSCALL_H_ */
