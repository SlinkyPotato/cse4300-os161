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
  // mkdir(newDirectory, 0700); // make a new directory
	readCurrentDir();
	return 0;
}

int readCurrentDir() {
  struct dirent *dir;
  DIR *d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
  return 0;
}