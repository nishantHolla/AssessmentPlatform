
#include "ap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void viewTest() {
  /*
    Function that allows user to view a test.
  */

  printInBox("View test", 1, 2);
  printf("\n");

  char testName[MAX_STRING_LENGTH] = "";
  char file[MAX_STRING_LENGTH] = "";

  // get test name that is to be viewed
  while (1) {
    while (strlen(testName) == 0)
      getString(testName, "Enter test name: ");

    strcpy(file, testName);
    strcat(file, "-result.txt");

    // check if test exists
    if (!fileExists(file)) {
      printf("Error: Could not find test results.\n");
      strcpy(testName, "");
      continue;
    }

    break;
  }

  // open result file of the test
  FILE *resultFile = fopen(file, "r");
  if (!resultFile) {
    printf("Error: Could not open result file.\n");
    return;
  }

  // allocate memory on the heap to store all the results of the test
  struct result *results =
      (struct result *)malloc(sizeof(struct result) * MAX_QUESTION);
  int ri = 0;

  // parse the result file and fill the results
  while (1) {
    char name[MAX_STRING_LENGTH] = "";
    char time[MAX_STRING_LENGTH] = "";

    readString(name, resultFile);
    strcpy(results[ri].name, name);

    if (strlen(name) == 0)
      break;

    readString(time, resultFile);
    strcpy(results[ri].time, time);

    int qi = 0;
    while (1) {
      char line[MAX_STRING_LENGTH] = "";
      readString(line, resultFile);

      if (strlen(line) == 0) {
        results[ri].numberOfQuestions = qi;
        break;
      }

      int qResult;
      char qTime[MAX_STRING_LENGTH];
      sscanf(line, "%d %s", &qResult, qTime);

      results[ri].result[qi].result = qResult;
      strcpy(results[ri].result[qi].timeTaken, qTime);
      qi++;
    }

    ri++;
  }

  // display all available results of the test
  printf("\nFollowing results were found:\n\n");
  for (int i = 0; i < ri; i++) {
    char line[MAX_STRING_LENGTH];
    sprintf(line, "%d) Taken by %s on %s", i + 1, results[i].name,
            results[i].time);
    printInBox(line, 4, 2);
  }

  printf("\n");

  // get which restult to view
  int selection = getSelection(ri, "Which result to view? ") - 1;
  const int tableWidth =
      strlen("Q.No") + strlen("Result") + strlen("Time taken") + 2 * 3 * 3 + 2;

  int totalScore = 0;
  int totalTime = 0;

  // print top border of the table
  printf("\n %s", BOX_TL);
  for (int i = 0; i < tableWidth; i++)
    printf("%s", BOX_H);
  printf("%s\n", BOX_TR);

  // display the header of the table
  printf(" %s   Q.No   %s   Result   %s   Time taken   %s\n", BOX_V, BOX_V,
         BOX_V, BOX_V);

  // display table bar
  printf(" %s", BOX_V);
  for (int i = 0; i < tableWidth; i++)
    printf("%s", BOX_H);
  printf("%s\n", BOX_V);

  // display result
  for (int i = 0; i < results[selection].numberOfQuestions; i++) {
    int timeTaken = atoi(results[selection].result[i].timeTaken);
    totalTime += timeTaken;
    if (results[selection].result[i].result)
      totalScore++;

    char timeString[MAX_STRING_LENGTH];
    formatTime(timeString, timeTaken);
    printf(" %s%9d %s%11d %s%15s %s\n", BOX_V, i + 1, BOX_V,
           results[selection].result[i].result, BOX_V, timeString, BOX_V);
  }

  // display table bar
  printf(" %s", BOX_V);
  for (int i = 0; i < tableWidth; i++)
    printf("%s", BOX_H);
  printf("%s\n", BOX_V);

  // display totals
  char totalTimeString[MAX_STRING_LENGTH] = "";
  formatTime(totalTimeString, totalTime);
  printf(" %s%9s %s%9d/%d %s%15s %s\n", BOX_V, "Total", BOX_V, totalScore,
         results[selection].numberOfQuestions, BOX_V, totalTimeString, BOX_V);

  // print bottom border of the table
  printf(" %s", BOX_BL);
  for (int i = 0; i < tableWidth; i++)
    printf("%s", BOX_H);
  printf("%s\n", BOX_BR);

  printf("\n");

  fclose(resultFile);
  free(results);
}
