#include <stdio.h>

int main(int argc, char const *argv[]) {
  int myIntValue = 500;
  int *myFirstPointer;

  myFirstPointer = &myIntValue;

  printf("Value of myIntValue: %d\n", myIntValue);
  printf("Address of myIntValue: %d\n", &myIntValue);
  printf("Address of myFirstPointer: %d\n", myFirstPointer);
  printf("Value of myFirstPointer: %d\n", *myFirstPointer);
  return 0;
}
