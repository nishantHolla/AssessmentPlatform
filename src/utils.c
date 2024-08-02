#include "ap.h"
#include <stdio.h>
#include <string.h>

void getString(char *container, char *prompt) {
  /*
    Function that displays a promt and gets a string from the user and stores it
    in a container.
  */

  printf("%s", prompt);
  fgets(container, MAX_STRING_LENGTH, stdin);
  container[strcspn(container, "\n")] = 0;
}

int getSelection(int max, char *prompt) {
  /*
    Function that returns an integer number from the user that lies between 1
    and max.
  */

  while (1) {
    int ans = 0;
    printf("%s [1-%d]: ", prompt, max);
    scanf("%d", &ans);
    getchar();
    if (ans >= 1 && ans <= max)
      return ans;
  }
}

void readString(char *container, FILE *file) {
  /*
    Function that reads a line into container from the given file.
  */

  char *c = fgets(container, MAX_STRING_LENGTH, file);
  if (!c) {
    strcpy(container, "");
    return;
  }
  container[strcspn(container, "\n")] = 0;
}

int fileExists(char *path) {
  FILE *f = fopen(path, "r");
  if (!f)
    return 0;
  fclose(f);
  return 1;
}

void printInBox(char *text, int lp, int ip) {
  /*
    Function that prints the given text in a box.
    lp (left padding) is the amount of spaces to be given to the left of the
    box. ip (inner padding) is the amount of spaces to be given between the text
    and the box.
  */

  int l = strlen(text) + 2;

  for (int i = 0; i < lp; i++)
    printf(" ");
  printf("%s", BOX_TL);
  for (int i = 0; i < l; i++)
    printf("%s", BOX_H);
  printf("%s\n", BOX_TR);

  for (int i = 0; i < lp; i++)
    printf(" ");
  printf("%s", BOX_V);
  for (int i = 0; i < ip / 2; i++)
    printf(" ");
  printf("%s", text);
  for (int i = 0; i < ip / 2; i++)
    printf(" ");
  printf("%s\n", BOX_V);

  for (int i = 0; i < lp; i++)
    printf(" ");
  printf("%s", BOX_BL);
  for (int i = 0; i < l; i++)
    printf("%s", BOX_H);
  printf("%s\n", BOX_BR);
}

void formatTime(char *container, int seconds) {
  /*
    Function that formats time into minutes and seconds given number of seconds
  */

  int m = seconds / 60;
  int s = seconds - m;

  sprintf(container, "%dm %ds", m, s);
}
