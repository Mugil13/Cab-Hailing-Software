#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int AdvanceBooking() {
  char choice[10];
  int hours;

  printf("\n\033[1;37mEnter yes/no: \033[0m");
  scanf("%s", choice);

  if (strcmp(choice, "yes") == 0) {
    printf("\033[1;37mEnter the number of hours for pre-booking: \033[0m");
    scanf("%d", &hours);

    if (hours < 1 || hours > 24) {
      printf("\n\033[1;31mYou have exceeded the pre-booking time limit!\033[0m\n");
      return 0;
    } else {
      return 1;
    }
  } else if (strcmp(choice, "no") == 0) {
    return 0;
  } else {
    printf("\033[1;37mEnter a valid choice: \033[0m\n");
    return 0;
  }
}
