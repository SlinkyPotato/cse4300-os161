#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <kern/syscall.h>

int main(void) {
	_exit(123);
	return 0;
}
