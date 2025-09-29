#include "chunk.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    siete = 6
};

const int directii[siete][3] = {{-1, 0, 0}, {1, 0, 0},  {0, -1, 0},
                          {0, 1, 0},  {0, 0, -1}, {0, 0, 1}};

char ***chunk_rotate_y(char ***chunk, int width, int height, int depth) {
    char ***copies = malloc(depth * sizeof(*copies));
    for (int i = 0; i < depth; i++) {
        copies[i] = malloc(height * sizeof(**copies));
        for (int j = 0; j < height; j++) {
            copies[i][j] = malloc(width * sizeof(***copies));
        }
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int z = 0; z < depth; z++) {
                copies[z][y][x] = chunk[x][y][depth - 1 - z];
            }
        }
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            free(chunk[x][y]);
        }
        free(chunk[x]);
    }
    free(chunk);

    int aux = width;
    width = depth;
    depth = aux;

    return copies;
}


typedef struct {
  int x, y, z;
} bloc;

void corp_apply_gravity(char ***chunk, int width, int height, int depth,
                        int startX, int startY, int startZ) {
  bloc *queue = (bloc *)malloc(width * height * depth * sizeof(bloc));
  int front = 0, rear = 0;

  char B = chunk[startX][startY][startZ];
  chunk[startX][startY][startZ] = 0;

  bloc *corp = (bloc *)malloc(width * height * depth * sizeof(bloc));
  int corp_size = 0;

  queue[rear++] = (bloc){startX, startY, startZ};

  while (front < rear) {  // alcatuiesc corpul in vector de tip bloc*
    bloc b = queue[front++];
    corp[corp_size++] = b;

    for (int d = 0; d < siete; d++) {
      int nouX = b.x + directii[d][0];
      int nouY = b.y + directii[d][1];
      int nouZ = b.z + directii[d][2];

      if (nouX >= 0 && nouX < width && nouY >= 0 && nouY < height &&
          nouZ >= 0 && nouZ < depth && chunk[nouX][nouY][nouZ] == B) {
        queue[rear++] = (bloc){nouX, nouY, nouZ};
        chunk[nouX][nouY][nouZ] = 0;
      }
    }
  }

  bool can_fall = true;
  while (can_fall) {  // mut coordonatele corpului in jos cat se poate
    for (int i = 0; i < corp_size; i++) {
      if (corp[i].y - 1 < 0 || chunk[corp[i].x][corp[i].y - 1][corp[i].z]) {
        can_fall = false;
        break;
      }
    }

    if (can_fall) {
      for (int i = 0; i < corp_size; i++)
        corp[i].y--;
    }
  }

  for (int i = 0; i < corp_size; i++) {
    chunk[corp[i].x][corp[i].y][corp[i].z] = B;
  }

  free(queue);
  free(corp);
}

void merge_apply_gravity(char ***temp_chunk, char ***chunk, int width,
                         int height, int depth, int startX, int startY,
                         int startZ) {
  bloc *queue = (bloc *)malloc(width * height * depth * sizeof(bloc));
  int front = 0, rear = 0;

  chunk[startX][startY][startZ] = 0;

  bloc *corp = (bloc *)malloc(width * height * depth * sizeof(bloc));
  int corp_size = 0;

  queue[rear++] = (bloc){startX, startY, startZ};

  while (front < rear) {  // alcatuiesc corpul in vector de tip bloc*
    bloc b = queue[front++];
    corp[corp_size++] = b;

    for (int d = 0; d < siete; d++) {
      int nouX = b.x + directii[d][0];
      int nouY = b.y + directii[d][1];
      int nouZ = b.z + directii[d][2];

      if (nouX >= 0 && nouX < width && nouY >= 0 && nouY < height &&
          nouZ >= 0 && nouZ < depth && chunk[nouX][nouY][nouZ]) {
        queue[rear++] = (bloc){nouX, nouY, nouZ};
        chunk[nouX][nouY][nouZ] = 0;
      }
    }
  }

  bool can_fall = true;
  int k = 0;
  while (can_fall) {  // mut coordonatele corpului in jos cat se poate
    for (int i = 0; i < corp_size; i++) {
      if (corp[i].y - 1 < 0 || chunk[corp[i].x][corp[i].y - 1][corp[i].z]) {
        can_fall = false;
        break;
      }
    }

    if (can_fall) {
      k++;
      for (int i = 0; i < corp_size; i++)
        corp[i].y--;
    }
  }

  for (int i = 0; i < corp_size && corp[i].y + k < height; i++) {
    chunk[corp[i].x][corp[i].y][corp[i].z] =
        temp_chunk[corp[i].x][corp[i].y + k][corp[i].z];
  }

  free(queue);
  free(corp);
}

char ***chunk_apply_gravity(char ***chunk, int width, int height, int depth,
                            int *new_height) {
  for (int y = 0; y < height; y++) {  // gravitatie de jos in sus
    for (int x = 0; x < width; x++) {
      for (int z = 0; z < depth; z++) {
        if (chunk[x][y][z]) {
          corp_apply_gravity(chunk, width, height, depth, x, y, z);
        }
      }
    }
  }

  char ***temp_chunk = (char ***)malloc(width * sizeof(char **));
  bool ***visited = (bool ***)malloc(width * sizeof(bool **));
  for (int x = 0; x < width; x++) {
    temp_chunk[x] = (char **)malloc(height * sizeof(char *));
    visited[x] = (bool **)malloc(height * sizeof(bool *));
    for (int y = 0; y < height; y++) {
      temp_chunk[x][y] = (char *)malloc(depth * sizeof(char));
      visited[x][y] = (bool *)malloc(depth * sizeof(bool));
      for (int z = 0; z < depth; z++) {
        temp_chunk[x][y][z] = chunk[x][y][z];
        visited[x][y][z] = false;
      }
    }
  }

  for (int y = 0; y < height; y++) {  // gravitatie de jos in sus
    for (int x = 0; x < width; x++) {
      for (int z = 0; z < depth; z++) {
        if (temp_chunk[x][y][z] && !visited[x][y][z]) {
          merge_apply_gravity(temp_chunk, chunk, width, height, depth, x, y, z);
          bloc *queue = (bloc *)malloc(width * height * depth * sizeof(bloc));
          int front = 0, rear = 0;
          queue[rear++] = (bloc){x, y, z};

          while (front < rear) {
            bloc b = queue[front++];
            visited[b.x][b.y][b.z] = true;

            for (int d = 0; d < siete; d++) {
              int nouX = b.x + directii[d][0];
              int nouY = b.y + directii[d][1];
              int nouZ = b.z + directii[d][2];
              if (nouX >= 0 && nouX < width && nouY >= 0 && nouY < height &&
                  nouZ >= 0 && nouZ < depth) {
                if (!visited[nouX][nouY][nouZ] &&
                    temp_chunk[nouX][nouY][nouZ]) {
                  visited[nouX][nouY][nouZ] = true;
                  queue[rear++] = (bloc){nouX, nouY, nouZ};
                }
              }
            }
          }
          free(queue);
        }
      }
    }
  }

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      free(visited[x][y]);
    }
    free(visited[x]);
  }
  free(visited);

  for (int y = 0; y < height; y++) {  // gravitatie de jos in sus
    for (int x = 0; x < width; x++) {
      for (int z = 0; z < depth; z++) {
        if (chunk[x][y][z]) {
          corp_apply_gravity(chunk, width, height, depth, x, y, z);
        }
      }
    }
  }

  // elimin aerul de sus
  int top = height - 1;
  while (top >= 0) {
    bool is_empty = true;
    for (int x = 0; x < width && is_empty; x++) {
      for (int z = 0; z < depth && is_empty; z++) {
        if (chunk[x][top][z]) {
          is_empty = false;
        }
      }
    }
    if (is_empty) {
      top--;
    } else {
      break;
    }
  }

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      free(temp_chunk[x][y]);
    }
    free(temp_chunk[x]);
  }
  free(temp_chunk);

  *new_height = top + 1;  // newh dupa eliminarea aerului

  return chunk;
}
