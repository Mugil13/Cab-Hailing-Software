#include "userdetails.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

int Bill_generation(int advance_booking, char type_of_cab[], float distance,
                    float cancellation_fee, struct USER users[], int userindex,
                    int sz) {
  char cabtype[3][20] = {"minisedan", "SUV", "Sedan"};
  float basefare[3] = {75.61, 133.0, 45.40};
  float fare_per_km[3] = {13.56, 25.60, 30.68};
  float cab_cancellation_fee[3] = {15.80, 31.60, 23.70};
  float bill_amount;

  srand(time(NULL));
  int hour = rand() % 24;

  for (int i = 0; i < 3; i++) {
    float new_basefare;

    if (strcmp(type_of_cab, cabtype[i]) == 0) {
      if (advance_booking == 1) {
        new_basefare = basefare[i] * 1.5;
        bill_amount =
            new_basefare + (fare_per_km[i] * distance) + cancellation_fee;
      } else if (hour == 8 || hour == 9 || hour == 10 || hour == 18 ||
                 hour == 19 || hour == 20) {

        new_basefare = basefare[i] * 1.5;
        bill_amount =
            new_basefare + (fare_per_km[i] * distance) + cancellation_fee;
      } else {
        new_basefare = basefare[i];
        bill_amount =
            new_basefare + (fare_per_km[i] * distance) + cancellation_fee;
      }

      // printf("--------BILL-------\n");
      printf("\n\033[1;37mTime: %d:00\n", hour);
      printf("\nTotal Bill Amount = Rs. %.2f\n\n\n", bill_amount);

      centerJustify("Bill split-up");
      printf("\nBase fare: Rs. %.2f\n", basefare[i]);
      printf("\nFare per Kilometre: Rs. %.2f\033[0m\n", fare_per_km[i]);
      if (advance_booking) {
        printf("\n\033[1;37mAdvance booking fee: Rs. %.2f\033[0m\n",
               0.5 * basefare[i]);
      } else if (hour == 8 || hour == 9 || hour == 10 || hour == 18 ||
                 hour == 19 || hour == 20) {

        printf("\n\033[1;37mSurge fee: Rs. %.2f\033[0m\n", 0.5 * basefare[i]);
      }
      // printf("cancellation fee: %f\n\n ", cancellation_fee);

      char cancel[10];
      printf("\n\n\033[1;33mDo you wish to cancel your trip? \033[0m\n");
      scanf("%s", cancel);

      if (strcmp(cancel, "yes") == 0) {
        cancellation_fee += cab_cancellation_fee[i];
        users[userindex].cancellationfee = cancellation_fee;
        writeUserDetails(users, sz);
        printf("\n\033[1;31mA cancellation fee of %.2f will be added to your "
               "next trip!\033[0m\n",
               users[userindex].cancellationfee);

        printf("\033[1;37m");
        centerJustify("Thank you for booking with us!");
        printf("\033[0m");

        exit(1);

      } else {
        cancellation_fee = 0;
        users[userindex].cancellationfee = cancellation_fee;
        writeUserDetails(users, sz);
      }
    }
  }

  return cancellation_fee;
}
