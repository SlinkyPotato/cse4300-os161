// Change the current directory

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

// In-file headers
int readCurrentDir();

int main(int argc, char const *argv[]) {
  // Change Directory
  // char *directory = "/home/brian/Downloads/temp";
  char *directory = "P:/temp";
  char *newDirectory = "createdByProgram";
  int didChange;
  didChange = chdir(directory);
  printf("Did directory change? %d\n", didChange);
  // mkdir(newDirectory, 0700);
  readCurrentDir();
}

int readCurrentDir() {
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
  return 0;
}
