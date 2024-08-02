#ifndef AP_H_
#define AP_H_ 1

#include <stdio.h>

#define MAX_STRING_LENGTH 1000
#define MAX_QUESTION 100
#define MAX_OPTIONS 50

#ifdef _WIN32

#define BOX_TL "+"
#define BOX_TR "+"
#define BOX_BL "+"
#define BOX_BR "+"
#define BOX_V "|"
#define BOX_H "-"

#else

#define BOX_TL "┏"
#define BOX_TR "┓"
#define BOX_BL "┗"
#define BOX_BR "┛"
#define BOX_V "┃"
#define BOX_H "━"

#endif

struct resultOption {
  int result;
  char timeTaken[MAX_STRING_LENGTH];
};

struct result {
  char name[MAX_STRING_LENGTH];
  char time[MAX_STRING_LENGTH];
  int numberOfQuestions;
  struct resultOption result[MAX_OPTIONS];
};

// ap

void makeTest();
void takeTest();
void viewTest();

// utils

void getString(char *container, char *prompt);
void readString(char *container, FILE *file);
int getSelection(int max, char *prompt);
int fileExists(char *path);
void printInBox(char *text, int lp, int ip);
void formatTime(char *container, int seconds);

#endif // AP_H_
