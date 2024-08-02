
#include "ap.h"
#include <stdio.h>

int main() {
  /*
    The main function asks the user for the action they want to perform and
    calls the required functions for that action
  */

  // print all possible actions
  printf("\n\
1) Make test\n\
2) Take Test\n\
3) View Test\n");

  // get action to perform from the user
  int action = getSelection(3, "\n");

  // perform the action
  printf("\n\n");
  if (action == 1)
    makeTest();
  else if (action == 2)
    takeTest();
  else
    viewTest();

  return 0;
}
