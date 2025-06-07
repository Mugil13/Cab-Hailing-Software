#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char drivername[50];
  char cabtype[10];
  char cabmodel[25];
  char reg_number[50];
  float rating;
  int no_trips;
  int location_col;
  int location_row;
} driver;

int GetDetails() {
  FILE *fp = fopen("driver.txt", "r");
  if (fp == NULL) {
    printf("error opnening the file");
    return 1;
  }
  driver drivers[6];
  int read = 0;
  int rec = 0;

  while (!feof(fp)) {
    read = fscanf(fp, "%50[^,],%10[^,],%25[^,],%50[^,],%f,%d,%d,%d",
                  &drivers[rec].drivername, &drivers[rec].cabtype,
                  &drivers[rec].cabmodel, &drivers[rec].reg_number,
                  &drivers[rec].rating, &drivers[rec].no_trips,
                  &drivers[rec].location_col, &drivers[rec].location_row);

    if (read == 8) {
      rec++;
    }
  }

  for (int i; i < 6; i++) {
    printf("%s\n", drivers[i].cabtype);
  }

  return 0;
}
