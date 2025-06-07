#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>


void centerJustify(const char* text) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int terminal_width = w.ws_col;
    int text_length = strlen(text);

    int padding = (terminal_width - text_length) / 2;
    if (padding > 0) {
        printf("%*s%s\n", padding, "", text);
    } else {
        printf("%s\n", text);
    }
}


struct USER {
  char name[50];
  char email[50];
  char phone[50];
  char username[50];
  char password[50];
  float cancellationfee;
};

struct USER login() {
  struct USER user;

  FILE *fp;

  int choice;
  int found_username = 0;

  printf("\033[1;37m\n");
  centerJustify("Welcome to our cab hailing system!\n");
  printf("Let's get you started!\n");
  printf("What would you like to do? \n1. Login\n2. Register\033[0m\n\n\033[1;33mEnter Choice: \033[0m");
  scanf("%d", &choice);
  printf("\n");
  if (choice == 1) {
  login:
    char uname[50], pwd[50];
    printf("Enter your username: ");
    scanf("%s", uname);

    printf("Enter your password: ");
    scanf("%s", pwd);

    fp = fopen("USERS.txt", "r");
    if (fp == NULL) {
      printf("Error opening file.\n");
      exit(1);
    }

    while (fread(&user, sizeof(struct USER), 1, fp)) {
      if (strcmp(uname, user.username) == 0) {
        found_username = 1;
        if (strcmp(pwd, user.password) == 0) {
          printf("\n\033[1;32m%s, You have successfully logged into your account!\033[0m\n",
                 user.name);
          centerJustify("\033[1;32mContinue booking with us!!\n");
          fclose(fp);
          return user;
        } else {
          printf("\033[1;31mWrong password entered. Please try again.\033[0m\n");
          fclose(fp);
          exit(1);
        }
      }
    }

    if (found_username == 0) {
      printf("\033[1;31mThe given username doesn't exist. Please try again.\033[0m\n");
      fclose(fp);
      exit(1);
    }

    fclose(fp);
  } else if (choice == 2) {
    printf("Enter your name: ");
    scanf("%s", user.name);

    printf("Enter your Email ID: ");
    scanf("%s", user.email);

    printf("Enter phone number: ");
    scanf("%s", user.phone);

    printf("Enter a username: ");
    scanf("%s", user.username);

    printf("Enter your password: ");
    scanf("%s", user.password);
    user.cancellationfee = 0;

    fp = fopen("USERS.txt", "a");
    if (fp == NULL) {
      printf("\033[1;31mError opening file.\033[0m\n");
      exit(1);
    }

    fwrite(&user, sizeof(struct USER), 1, fp);
    fclose(fp);
    printf("\n\n");
    goto login;
  }

  return user;
}
