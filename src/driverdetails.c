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

#define MAX_DRIVERS 12
driver drivers[MAX_DRIVERS];

int GetDetails() {
  FILE *fp = fopen("driver.txt", "r");
  if (fp == NULL) {
    printf("Error opening the file.\n");
    return 1;
  }

  int rec = 0;

  while (rec < MAX_DRIVERS &&
         fscanf(fp, "%49[^,],%9[^,],%24[^,],%49[^,],%f,%d,%d,%d\n",
                drivers[rec].drivername, drivers[rec].cabtype,
                drivers[rec].cabmodel, drivers[rec].reg_number,
                &drivers[rec].rating, &drivers[rec].no_trips,
                &drivers[rec].location_col, &drivers[rec].location_row) == 8) {
    rec++;
  }

  fclose(fp);

  return 0;
}

int write_details(driver drivers[]) {
  FILE *fp = fopen("driver.txt", "w");
  if (fp == NULL) {
    printf("Error opening the file.\n");
    return 1;
  }

  for (int i = 0; i < MAX_DRIVERS; i++) {
    fprintf(fp, "%s,%s,%s,%s,%.1f,%d,%d,%d\n", drivers[i].drivername,
            drivers[i].cabtype, drivers[i].cabmodel, drivers[i].reg_number,
            drivers[i].rating, drivers[i].no_trips, drivers[i].location_col,
            drivers[i].location_row);
  }
  fclose(fp);
  return 0;
}
