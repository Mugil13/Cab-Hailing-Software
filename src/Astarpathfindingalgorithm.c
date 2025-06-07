#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 34
#define COLS 44
int locationarr[2];
typedef struct {
  int row;
  int col;
  int f;
  int g;
  int h;
  bool obstacle;
  struct Node *parent;
} Node;

bool isvalid(int row, int col, Node grid[ROWS][COLS]) {
  if (row >= 0 && row < ROWS && col >= 0 && col < COLS &&
      !grid[row][col].obstacle) {
    return true;
  } else {
    return false;
  }
}

double calculateHeuristicDistance(Node *current, Node *dest) {
  return sqrt((current->row - dest->row) * (current->row - dest->row) +
              (current->col - dest->col) * (current->col - dest->col));
}

int Astarpathfinder(Node grid[ROWS][COLS], Node *start, Node *dest) {
  bool visited[ROWS][COLS];
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      visited[i][j] = false;
    }
  }
  Node *openlist[ROWS * COLS];
  int openlistcount = 0;
  openlist[openlistcount++] = start;

  start->g = 0;
  start->h = calculateHeuristicDistance(start, dest);
  start->f = start->g + start->h;

  while (openlistcount > 0) {
    int lowestFIndex = 0;
    for (int i = 1; i < openlistcount; i++) {
      if (openlist[i]->f < openlist[lowestFIndex]->f) {
        lowestFIndex = i;
      }
    }
    Node *current = openlist[lowestFIndex];

    for (int i = lowestFIndex; i < openlistcount - 1; i++) {
      openlist[i] = openlist[i + 1];
    }
    openlistcount--;

    visited[current->row][current->col] = true;

    if (current == dest) {
      Node *path = current;
      int distance = 0;
      while (path != start) {
        distance++;
        path = path->parent;
      }
      return distance;
    }

    int surroudingrows[4] = {0, 0, -1, 1};
    int surroundingcols[4] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; i++) {
      int Row = current->row + surroudingrows[i];
      int Col = current->col + surroundingcols[i];

      if (isvalid(Row, Col, grid) && !visited[Row][Col]) {
        Node *neighbor = &grid[Row][Col];
        int G = current->g + 1;

        if (G < neighbor->g || !visited[neighbor->row][neighbor->col]) {
          neighbor->g = G;
          neighbor->h = calculateHeuristicDistance(neighbor, dest);
          neighbor->f = neighbor->g + neighbor->h;
          neighbor->parent = current;

          if (!visited[neighbor->row][neighbor->col]) {
            openlist[openlistcount++] = neighbor;
            visited[neighbor->row][neighbor->col] = true;
          }
        }
      }
    }
  }
}

int astarfunc(char pickup1[], char destination1[]) {
  Node grid[ROWS][COLS];

  int initialGrid[ROWS][COLS] = {
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
       0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
       0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
       0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0},
      {1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0,
       0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
       0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
      {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
      {1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1,
       0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
      {1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
       0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
      {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
       1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1},
      {0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0,
       1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
      {0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0,
       1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
      {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0,
       1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1},
      {0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0,
       1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1,
       0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
      {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1,
       0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
      {0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1,
       0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1,
       0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
      {0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0,
       0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
       0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1,
       1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
      {0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
       1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
      {0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
       0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
      {0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
       0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
      {0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1,
       0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
      {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1,
       1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
      {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1},
      {0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1,
       1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0,
       0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1},
      {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
       1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1},
      {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
       0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
      {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
       1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0}};

  int places[45][2] = {
      {0, 0},   {0, 8},   {0, 24},  {0, 31},  {1, 33},  {2, 17},  {3, 43},
      {5, 1},   {6, 43},  {7, 18},  {8, 6},   {8, 34},  {9, 12},  {11, 29},
      {11, 42}, {14, 0},  {14, 9},  {14, 28}, {14, 33}, {16, 0},  {16, 2},
      {16, 19}, {16, 41}, {16, 43}, {17, 11}, {19, 30}, {20, 18}, {20, 33},
      {20, 38}, {21, 7},  {21, 24}, {22, 0},  {24, 16}, {24, 43}, {25, 3},
      {25, 30}, {26, 24}, {28, 11}, {29, 26}, {31, 42}, {32, 0},  {32, 17},
      {32, 35}, {33, 9},  {33, 24}};

  char placenames[45][50] = {"home",
                             "government museum",
                             "grand gallada",
                             "arignar anna zoo",
                             "jeeva park",
                             "valluvar kottam",
                             "ashtalakshmi temple",
                             "connemara library",
                             "iskcon temple",
                             "dakshikachitra museum",
                             "santhome cathedral",
                             "madras war cemetry",
                             "crocodile bank",
                             "express avenue mall",
                             "shirdi sai baba temple",
                             "nettukuppam",
                             "thousand lights mosque",
                             "fort St.george",
                             "chetpet lake",
                             "santhome church",
                             "phoenix mall",
                             "kapaleeshvarar temple",
                             "mgm dizzee world",
                             "vdapalani murugan temple",
                             "t nagar",
                             "parthasarathy temple",
                             "vr mall",
                             "cmbt bus stand",
                             "anna nagar tower",
                             "forum mall",
                             "ripon building",
                             "bm birla planetarium",
                             "anna centenary library",
                             "vgp snow kingdom",
                             "vit college of engineering",
                             "semmozhi poonga",
                             "guindy national park",
                             "annai velankanni shrine",
                             "perignar anna memorial",
                             "tholkappia poonga",
                             "grand Square",
                             "sivan park",
                             "ssn college of engineering",
                             "dav public school",
                             "appolo hospital"};

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      grid[i][j].row = i;
      grid[i][j].col = j;
      grid[i][j].obstacle = (initialGrid[i][j] == 1);
      grid[i][j].parent = NULL;
    }
  }

  int indexdestination = 0, indexpickup = 0;
  char destination[50], pickup[50];

  strcpy(pickup, pickup1);
  strcpy(destination, destination1);

  for (int i = 0; i < strlen(pickup); i++) {
    pickup[i] = tolower(pickup[i]);
  }
  for (int i = 0; i < strlen(destination); i++) {
    destination[i] = tolower(destination[i]);
  }

  for (int i = 0; i < 45; i++) {
    if (strcmp(destination, placenames[i]) == 0) {
      indexdestination = i;
    }
  }

  for (int i = 0; i < 45; i++) {
    if (strcmp(pickup, placenames[i]) == 0) {
      indexpickup = i;
    }
  }

  int rowdest = places[indexdestination][0];
  int coldest = places[indexdestination][1];

  int rowpickup = places[indexpickup][0];
  int colpickup = places[indexpickup][1];

  Node *start = &grid[rowpickup][colpickup];
  Node *goal = &grid[rowdest][coldest];

  int dist = Astarpathfinder(grid, start, goal);
  return dist;
}

int cab(char pickup1[], int row_cab, int col_cab) {
  Node grid[ROWS][COLS];

  int initialGrid[ROWS][COLS] = {
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
       0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
       0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
       0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0},
      {1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0,
       0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
       0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
      {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
      {1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1,
       0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
      {1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1,
       0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
      {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
       1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1},
      {0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0,
       1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
      {0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0,
       1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
      {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0,
       1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1},
      {0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0,
       1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
      {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1,
       0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
      {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1,
       0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
      {0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1,
       0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1,
       0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
      {0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0,
       0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
       0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1,
       1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
      {0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
       1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
      {0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
       0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
      {0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
       0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
      {0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1,
       0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
      {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1,
       1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
      {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1},
      {0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1,
       1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0,
       0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1},
      {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
       1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1},
      {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
       0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
      {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
       1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0}};

  int places[45][2] = {
      {0, 0},   {0, 8},   {0, 24},  {0, 31},  {1, 33},  {2, 17},  {3, 43},
      {5, 1},   {6, 43},  {7, 18},  {8, 6},   {8, 34},  {9, 12},  {11, 29},
      {11, 42}, {14, 0},  {14, 9},  {14, 28}, {14, 33}, {16, 0},  {16, 2},
      {16, 19}, {16, 41}, {16, 43}, {17, 11}, {19, 30}, {20, 18}, {20, 33},
      {20, 38}, {21, 7},  {21, 24}, {22, 0},  {24, 16}, {24, 43}, {25, 3},
      {25, 30}, {26, 24}, {28, 11}, {29, 26}, {31, 42}, {32, 0},  {32, 17},
      {32, 35}, {33, 9},  {33, 24}};

  char placenames[45][50] = {"home",
                             "government museum",
                             "grand gallada",
                             "arignar anna zoo",
                             "jeeva park",
                             "valluvar kottam",
                             "ashtalakshmi temple",
                             "connemara library",
                             "iskcon temple",
                             "dakshikachitra museum",
                             "santhome cathedral",
                             "madras war cemetry",
                             "crocodile bank",
                             "express avenue mall",
                             "shirdi sai baba temple",
                             "nettukuppam",
                             "thousand lights mosque",
                             "fort St.george",
                             "chetpet lake",
                             "santhome church",
                             "phoenix mall",
                             "kapaleeshvarar temple",
                             "mgm dizzee world",
                             "vdapalani murugan temple",
                             "t nagar",
                             "parthasarathy temple",
                             "vr mall",
                             "cmbt bus stand",
                             "anna nagar tower",
                             "forum mall",
                             "ripon building",
                             "bm birla planetarium",
                             "anna centenary library",
                             "vgp snow kingdom",
                             "vit college of engineering",
                             "semmozhi poonga",
                             "guindy national park",
                             "annai velankanni shrine",
                             "perignar anna memorial",
                             "tholkappia poonga",
                             "grand Square",
                             "sivan park",
                             "ssn college of engineering",
                             "dav public school",
                             "appolo hospital"};

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      grid[i][j].row = i;
      grid[i][j].col = j;
      grid[i][j].obstacle = (initialGrid[i][j] == 1);
      grid[i][j].parent = NULL;
    }
  }

  int indexdestination = 0, indexpickup = 0;
  char pickup[50];
  strcpy(pickup, pickup1);
  for (int i = 0; i < strlen(pickup); i++) {
    pickup[i] = tolower(pickup[i]);
  }

  for (int i = 0; i < 45; i++) {
    if (strcmp(pickup, placenames[i]) == 0) {
      indexpickup = i;
    }
  }

  int rowpickup = places[indexpickup][0];
  int colpickup = places[indexpickup][1];

  Node *start = &grid[rowpickup][colpickup];
  Node *goal = &grid[row_cab][col_cab];

  int dist = Astarpathfinder(grid, start, goal);
  return dist;
}

void location(char drop[]) {

  int places[45][2] = {
      {0, 0},   {0, 8},   {0, 24},  {0, 31},  {1, 33},  {2, 17},  {3, 43},
      {5, 1},   {6, 43},  {7, 18},  {8, 6},   {8, 34},  {9, 12},  {11, 29},
      {11, 42}, {14, 0},  {14, 9},  {14, 28}, {14, 33}, {16, 0},  {16, 2},
      {16, 19}, {16, 41}, {16, 43}, {17, 11}, {19, 30}, {20, 18}, {20, 33},
      {20, 38}, {21, 7},  {21, 24}, {22, 0},  {24, 16}, {24, 43}, {25, 3},
      {25, 30}, {26, 24}, {28, 11}, {29, 26}, {31, 42}, {32, 0},  {32, 17},
      {32, 35}, {33, 9},  {33, 24}};

  char placenames[45][50] = {"home",
                             "government museum",
                             "grand gallada",
                             "arignar anna zoo",
                             "jeeva park",
                             "valluvar kottam",
                             "ashtalakshmi temple",
                             "connemara library",
                             "iskcon temple",
                             "dakshikachitra museum",
                             "santhome cathedral",
                             "madras war cemetry",
                             "crocodile bank",
                             "express avenue mall",
                             "shirdi sai baba temple",
                             "nettukuppam",
                             "thousand lights mosque",
                             "fort St.george",
                             "chetpet lake",
                             "santhome church",
                             "phoenix mall",
                             "kapaleeshvarar temple",
                             "mgm dizzee world",
                             "vdapalani murugan temple",
                             "t nagar",
                             "parthasarathy temple",
                             "vr mall",
                             "cmbt bus stand",
                             "anna nagar tower",
                             "forum mall",
                             "ripon building",
                             "bm birla planetarium",
                             "anna centenary library",
                             "vgp snow kingdom",
                             "vit college of engineering",
                             "semmozhi poonga",
                             "guindy national park",
                             "annai velankanni shrine",
                             "perignar anna memorial",
                             "tholkappia poonga",
                             "grand Square",
                             "sivan park",
                             "ssn college of engineering",
                             "dav public school",
                             "appolo hospital"};
  int dropindex;
  for (int i = 0; i < 45; i++) {
    if (strcmp(drop, placenames[i]) == 0) {
      dropindex = i;
    }
  }

  locationarr[0] = places[dropindex][0];
  locationarr[1] = places[dropindex][1];
}
