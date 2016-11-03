#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

// Function Declarations
int readCurrentDir();

int main(int argc, char const *argv[]) {
	char *fileLocation = "../";
	char *newDirectory = "MyNewDirectory";
	chdir(fileLocation); // change into the parent directory
  mkdir(newDirectory, 0700); // make a new directory
	readCurrentDir();
	return 0;
}

int readCurrentDir() {
  struct dirent *dir; // pointer to dirent
  DIR *d = opendir("."); // open current directory
  if (d) { // if open successful
    while ((dir = readdir(d)) != NULL) { // while a file exists
      printf("%s\n", dir->d_name); // print the name of file
    }
    closedir(d); // clean up and close directory
  }
  return 0;
}