#include "Login.c"
#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS 1000
struct USER users[MAX_USERS];

int GetuserDetails() {
  int i = 0;
  struct USER user1;
  FILE *fp = fopen("USERS.txt", "r");
  if (fp == NULL) {
    printf("Error opening the file.\n");
    return 1;
  }

  while (fread(&user1, sizeof(struct USER), 1, fp)) {
    users[i] = user1;
    i++;
  }
  fclose(fp);
  return i;
}

void writeUserDetails(struct USER users[], int i) {
  FILE *fp = fopen("USERS.txt", "w");

  for (int j = 0; j < i; j++) {
    struct USER usera = users[j];
    fwrite(&usera, sizeof(struct USER), 1, fp);
  }

  fclose(fp);
}
