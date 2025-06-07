#include <stdio.h>

int Cab_assigner(float cabs[][2], int length) {
  float distance_weightage = 0.70;
  float rating_weightage = 0.30;

  float min_distance = cabs[0][0];
  float max_distance = cabs[0][0];

  for (int i = 0; i < length; i++) {
    if (cabs[i][0] < min_distance) {
      min_distance = cabs[i][0];
    }
    if (cabs[i][0] > max_distance) {
      max_distance = cabs[i][0];
    }
  }

  float normalised_distance[12];
  float scores[12];

  for (int i = 0; i < length; i++) {
    if (min_distance == max_distance) {
      normalised_distance[i] = 1.0;
    } else {
      normalised_distance[i] =
          (1 - ((cabs[i][0] - min_distance) / (max_distance - min_distance)));
    }

    scores[i] = (normalised_distance[i] * distance_weightage) +
                (cabs[i][1] * rating_weightage);
    printf("Cab no. %d\ncab distance (from user) = %.2f\nrating = %.2f\nfscore "
           "= %.2f\n",
           i + 1, cabs[i][0], cabs[i][1], scores[i]);
  }

  float highest_score = -1;
  int index = 0;

  for (int i = 0; i < length; i++) {
    if (scores[i] > highest_score) {
      highest_score = scores[i];
      index = i;
    }
  }

  return index;
}
