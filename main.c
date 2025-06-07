#include "Astarpathfindingalgorithm.c"
#include "Cab_score.c"
#include "Dijkstras.c"
#include "advance_booking.c"
#include "bill_generation.c"
#include "driverdetails.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
  struct USER temp;
  int userindex;
  temp = login();
  int sz = GetuserDetails();
  for (int i = 0; i < sz + 1; i++) {
    if (strcmp(users[i].name, temp.name) == 0) {
      userindex = i;
    }
  }
  int choice;
  int pickupl, dropoff;
  char cabtype[10];
  char pickup[100];
  char pickst[100];
  int pick;
  char dropst[100];
  int drop;
  char destination[100];
  char abc[100];
  char yes[10];
  float rating;

  fgets(abc, sizeof(abc), stdin);

  printf("\n\033[1;37mChoose the mode of travel: \n1. Within Chennai\n2. "
         "Within Tamil Nadu\033[0m\033[1;33m\n\nEnter choice:\033[0m");
  scanf("%d", &choice);
  printf("\n");

  if (choice == 1) {

    printf("\033[1;37mEnter the pickup location: \033[0m");
    getchar();
    fgets(pickup, sizeof(pickup), stdin);

    size_t len = strlen(pickup);
    if (len > 0 && pickup[len - 1] == '\n') {
      pickup[len - 1] = '\0';
    }

    printf("\033[1;37mEnter the destination: \033[0m");
    fgets(destination, sizeof(destination), stdin);
    len = strlen(destination);
    if (len > 0 && destination[len - 1] == '\n') {
      destination[len - 1] = '\0';
    }

    printf("\n\033[1;37mEnter the type of cab: \033[0m");
    scanf("%s", cabtype);
    printf("\n\033[1;33mDo you want to book your ride in advance?\033[0m");
    int adv = AdvanceBooking();
    if (adv == 1) {
      printf("\n\033[1;32mAdvanced Booking accepted\033[0m\n\n");
    } else {
      printf("\n\033[1;31mAdvanced Booking rejected\033[0m\n\n");
      printf("\033[1;33mDo you wish to continue booking? \033[0m");
      scanf("%s", yes);
      printf("\n\n");

      if (strcmp(yes, "yes") != 0) {
        exit(1);
      }
    }

    GetDetails();
    int details_length = 4;
    int cablocation[details_length];
    float details[details_length][2];
    int j = 0;

    for (int i; i < 12; i++) {
      if (strcmp(cabtype, drivers[i].cabtype) == 0) {
        cablocation[j] = i;
        details[j][0] =
            cab(pickup, drivers[i].location_row, drivers[i].location_col);

        details[j][1] = drivers[i].rating;
        j++;
      }
    }

    int index = Cab_assigner(details, details_length);
    int cabindex = cablocation[index];
    printf("\n\n");

    printf("\n\033[1;37m");
    centerJustify("Driver Details");
    printf("\nDriver's name: %s\n", drivers[cabindex].drivername);
    printf("\nCar Model: %s\n", drivers[cabindex].cabmodel);
    printf("\nRegistration number of the cab: %s\n",
           drivers[cabindex].reg_number);
    float distance = astarfunc(pickup, destination);
    printf("\nTotal distance travelled in km: %.2f km\n", distance);

    printf("\n\n");
    centerJustify("BILL");
    printf("\033[0m");
    float cancfee =
        Bill_generation(adv, drivers[cabindex].cabtype, distance,
                        users[userindex].cancellationfee, users, userindex, sz);
    
    printf("\033[1;37m");
    centerJustify("You have reached your destination!!");
    printf("\nWe hope you had a safe journey.Please enter your "
           "feedback rating below.\n");
    printf("\033[1;37mEnter the cab rating: \033[0m");
    scanf("%f", &rating);

    drivers[cabindex].rating = (float)((drivers[cabindex].rating + rating) / 2);
    drivers[cabindex].no_trips = drivers[cabindex].no_trips + 1;

    location(destination);
    drivers[cabindex].location_row = locationarr[0];
    drivers[cabindex].location_col = locationarr[1];
    write_details(drivers);
  }

  if (choice == 2) {
    printf("\033[1;37mEnter the pickup location: \033[0m");
    scanf("%s", pickst);
    printf("\033[1;37mEnter the drop location: \033[0m");
    scanf("%s", dropst);
    char dplacearr[10][100] = {"Chennai",    "Kanchipuram",  "Cuddalore",
                               "Thanjavur",  "Tiruchi",      "Dindigul",
                               "Madurai",    "Virudhunagar", "Tirunelveli",
                               "Kanyakumari"};
    for (int i = 0; i < 10; i++) {
      if (strcmp(pickst, dplacearr[i]) == 0) {
        pick = i;
      }

      if (strcmp(dropst, dplacearr[i]) == 0) {
        drop = i;
      }
    }

    printf("\n\n\033[1;37mEnter the type of cab: \033[0m");
    scanf("%s", cabtype);

    printf("\n\033[1;33mDo you want to pre-book or advance book your "
           "ride?\033[0m");
    int adv = AdvanceBooking();
    if (adv == 1) {
      printf("\n\033[1;32mAdvanced Booking accepted\033[0m\n\n");
    } else {
      printf("\n\033[1;31mAdvanced Booking rejected\033[0m\n\n");

      printf("\033[1;33mDo u want to continue? \033[0m");
      scanf("%s", yes);

      if (strcmp(yes, "yes") != 0) {
        exit(1);
      }
    }
    GetDetails();
    int details_length = 4;
    int cablocation[details_length];
    float details[details_length][2];
    int j = 0;

    for (int i; i < 12; i++) {
      if (strcmp(cabtype, drivers[i].cabtype) == 0) {
        cablocation[j] = i;
        details[j][0] =
            cab("home", drivers[i].location_row, drivers[i].location_col);

        details[j][1] = drivers[i].rating;
        j++;
      }
    }

    int index = Cab_assigner(details, details_length);
    int cabindex = cablocation[index];
    printf("\n\n\033[1;37m");

    centerJustify("Driver Details");
    printf("\nDriver's name: %s\n", drivers[cabindex].drivername);
    printf("\nCar model: %s\n", drivers[cabindex].cabmodel);
    printf("\nRegistration number of the cab:%s\n",
           drivers[cabindex].reg_number);

    float distance = astarfunc(pickup, destination);

    printf("\n\n");
    centerJustify("BILL");
    printf("\033[0m\n");
    int dist = dijkstras(pick, drop);
    float cancfee =
        Bill_generation(adv, drivers[cabindex].cabtype, dist,
                        users[userindex].cancellationfee, users, userindex, sz);

    printf("\033[1;37m");
    centerJustify("You have reached your destination!!");
    printf("\nWe hope you had a safe journey.Please enter your "
           "feedback rating below.\n");

    printf("\nEnter the cab rating: \033[0m");
    scanf("%f", &rating);
    drivers[cabindex].rating = (float)((drivers[cabindex].rating + rating) / 2);
    drivers[cabindex].no_trips = drivers[cabindex].no_trips + 1;
    write_details(drivers);
  }

  printf("\033[1;37m");
  centerJustify("Thank you for booking with us!");
  printf("\033[0m");
}