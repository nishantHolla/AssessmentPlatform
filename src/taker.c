
#include "ap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void takeTest() {
  /*
    Function that allows user to take a test.
  */

  // print heading
  printInBox("Take test", 1, 2);
  printf("\n");

  char dump[MAX_STRING_LENGTH] = "";
  char userName[MAX_STRING_LENGTH] = "";
  char testName[MAX_STRING_LENGTH] = "";
  char file[MAX_STRING_LENGTH + 10] = "";

  // get user name
  while (strlen(userName) == 0) {
    getString(userName, "Enter your name: ");
  }

  // get test name
  while (1) {
    while (strlen(testName) == 0) {
      getString(testName, "Enter test name: ");
    }

    strcpy(file, testName);
    strcat(file, "-test.txt");

    // check if test exists
    if (!fileExists(file)) {
      printf("Error: Test not found.\n");
      strcpy(testName, "");
      continue;
    }

    break;
  }

  // read the test file
  FILE *testFile = fopen(file, "r");
  if (!testFile) {
    printf("Error: Could not open test file.\n");
    return;
  }

  // discard the first line of the file
  readString(dump, testFile);

  char rf[MAX_STRING_LENGTH + 20];
  strcpy(rf, testName);
  strcat(rf, "-result.txt");

  // open the result file
  FILE *resultFile = fopen(rf, "a");
  if (!resultFile) {
    printf("Error: Could not open result file.\n");
    return;
  }

  time_t testStartTime;
  struct tm *timeinfo;
  char start_time[80];

  // get the current time
  time(&testStartTime);
  timeinfo = localtime(&testStartTime);
  strftime(start_time, sizeof(start_time), "%Y-%m-%d %H:%M:%S", timeinfo);

  fprintf(resultFile, "%s\n%s\n", userName, start_time);
  printf("\n");

  // ask all questions in the test
  int questionNumber = 1;
  while (1) {
    char question[MAX_STRING_LENGTH] = "";
    readString(question, testFile);

    if (strlen(question) == 0)
      break;

    printf("\nQuestion %d: %s\n\n", questionNumber++, question);

    // print all options of the current question
    int optionNumber = 1;
    while (1) {
      char option[MAX_STRING_LENGTH] = "";
      readString(option, testFile);
      if (strlen(option) == 0)
        break;
      char optionLine[MAX_STRING_LENGTH] = "";
      sprintf(optionLine, "Option %d: %s", optionNumber++, option);
      printInBox(optionLine, 4, 2);
    }

    // get the correct answer for the current question
    char correctAnswer[MAX_STRING_LENGTH] = "";
    readString(correctAnswer, testFile);

    printf("\n");

    time_t start, end;

    // start timer
    time(&start);

    // ask for user's answer
    int answer = getSelection(optionNumber - 1, "Your answer ");

    // end timer
    time(&end);

    // get time elapsed
    int time = difftime(end, start);

    // check if answer is correct and mark it in result file along with time
    int correctAnswerInt = atoi(correctAnswer);
    if (correctAnswerInt == answer) {
      fprintf(resultFile, "1 %d\n", time);
    } else {
      fprintf(resultFile, "0 %d\n", time);
    }

    // discard next line in test file
    readString(dump, testFile);
  }

  fprintf(resultFile, "\n");
  fclose(testFile);
  fclose(resultFile);
}
