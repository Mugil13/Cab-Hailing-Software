#include <stdbool.h>
#include <stdio.h>

#define NUM_CITIES 10
#define MAX_DISTANCE 9999

// Function to find the index of the node with the minimum distance value
int minDistance(int dist[], bool visited[]) {
  int min = MAX_DISTANCE, min_index;

  for (int v = 0; v < NUM_CITIES; v++) {
    if (!visited[v] && dist[v] <= min) {
      min = dist[v];
      min_index = v;
    }
  }

  return min_index;
}

// Dijkstra's algorithm
int dijkstra(int graph[NUM_CITIES][NUM_CITIES], int src, int dest) {
  int dist[NUM_CITIES];
  bool visited[NUM_CITIES];
  int parent[NUM_CITIES];

  for (int i = 0; i < NUM_CITIES; i++) {
    dist[i] = MAX_DISTANCE;
    visited[i] = false;
    parent[i] = -1;
  }

  dist[src] = 0;

  for (int count = 0; count < NUM_CITIES - 1; count++) {
    int u = minDistance(dist, visited);
    visited[u] = true;

    for (int v = 0; v < NUM_CITIES; v++) {
      if (!visited[v] && graph[u][v] && dist[u] != MAX_DISTANCE &&
          dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
        parent[v] = u;
      }
    }
  }

  // Shortest distance
  printf("Distance: %d km\n", dist[dest]);
  return dist[dest];
}

int dijkstras(int pickup, int dropoff) {
  // Example distance matrix for cities in Tamil Nadu
  //    printf("Cities with their nodes:\n\n0. Chennai\n1. Kanchipuram\n2. "
  //         "Cuddalore\n3. Thanjavur\n4. Tiruchi\n5. Dindigul\n6. Madurai\n7. "
  //         "Virudhunagar\n8. Tirunelveli\n9. Kanyakumari\n\n");

  int distanceMatrix[NUM_CITIES][NUM_CITIES] = {
      {0, 170, 250, 0, 0, 0, 0, 0, 0, 0}, {170, 0, 0, 130, 0, 0, 0, 0, 0, 0},
      {250, 0, 0, 330, 0, 0, 0, 0, 0, 0}, {0, 140, 330, 0, 80, 110, 0, 0, 0, 0},
      {0, 0, 0, 80, 0, 0, 150, 0, 0, 0},  {0, 0, 0, 120, 0, 0, 0, 200, 0, 0},
      {0, 0, 0, 0, 150, 0, 0, 0, 130, 0}, {0, 0, 0, 0, 0, 200, 0, 0, 0, 100},
      {0, 0, 0, 0, 0, 0, 130, 0, 0, 140}, {0, 0, 0, 0, 0, 0, 0, 100, 170, 0}};

  int dist = dijkstra(distanceMatrix, pickup, dropoff);

  return dist;
}
