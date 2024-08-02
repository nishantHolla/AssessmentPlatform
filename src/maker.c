
#include "ap.h"
#include <stdio.h>
#include <string.h>

void makeTest() {
  /*
    Function that allows user to make a new test.
  */

  // print heading
  printInBox("Make test", 1, 2);
  printf("\n");

  char name[MAX_STRING_LENGTH] = "";
  char file[MAX_STRING_LENGTH + 10] = "";

  // get name of the test to make
  while (1) {
    while (strlen(name) == 0)
      getString(name, "Enter test name: ");

    strcpy(file, name);
    strcat(file, "-test.txt");

    // check if test exists
    if (fileExists(file)) {
      printf("Error: Test with name %s exists.\n", name);
      strcpy(name, "");
      continue;
    }

    break;
  }

  // create the test file
  FILE *testFile = fopen(file, "w");
  if (!testFile) {
    printf("Error: Could not open test file.\n");
    return;
  }

  fprintf(testFile, "%s\n", name);
  int questionNuber = 1;

  // get all questions of the test
  while (1) {
    printf("\n(Enter empty question / option to exit)\n\n");
    printf("Question %d: ", questionNuber);

    char question[MAX_STRING_LENGTH] = "";
    getString(question, "");
    if (strlen(question) == 0 || questionNuber == MAX_QUESTION)
      break;

    fprintf(testFile, "%s\n", question);
    printf("\n");

    int optionNumber = 1;

    // get all options of the question
    while (1) {
      char option[MAX_STRING_LENGTH] = "";
      char prompt[MAX_STRING_LENGTH] = "";

      sprintf(prompt, "\tOption %d: ", optionNumber);
      getString(option, prompt);

      if (strlen(option) == 0 || optionNumber == MAX_OPTIONS)
        break;

      fprintf(testFile, "%s\n", option);
      optionNumber++;
    }

    fprintf(testFile, "\n");
    printf("\n");

    // get correct answer for the question
    int answer = getSelection(optionNumber - 1, "\tThe correct answer is");

    fprintf(testFile, "%d\n\n", answer);
    printf("\n");

    questionNuber++;
  }

  fclose(testFile);
}
