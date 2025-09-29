#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>

enum {
    siete = 6
};

void bfs(char ***chunk, int h, int height, char **graph, char **vizitat,
         int linii, int coloane, int startX, int startY, char B, char block) {
  const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  int **q = malloc(linii * coloane * sizeof(int *));
  for (int i = 0; i < linii * coloane; i++) {
    q[i] = malloc(2 * sizeof(int));
  }  // q pentru bfs
  int fata = 0, spate = 0;

  // adaugam punctul de start in coada
  q[spate][0] = startX;
  q[spate++][1] = startY;
  vizitat[startX][startY] = 1;

  while (fata < spate) {
    int x = q[fata][0];
    int y = q[fata][1];
    fata++;

    // plasam celula curenta
    chunk_place_block(chunk, linii, height, coloane, x, h, y, block);

    // vecini
    for (int d = 0; d < 4; d++) {
      int nouX = x + directions[d][0];
      int nouY = y + directions[d][1];

      // verificam daca e in limite nevizitat si are aceeasi valoare
      if (nouX >= 0 && nouX < linii && nouY >= 0 && nouY < coloane &&
          !vizitat[nouX][nouY] && graph[nouX][nouY] == B) {
        vizitat[nouX][nouY] = 1;
        q[spate][0] = nouX;
        q[spate++][1] = nouY;
      }
    }
  }
}

void bfs3d(char ***chunk, char ***vizitat, int width, int height, int depth,
           int startX, int startY, int startZ, char block) {
  int **q = malloc(width * height * depth * sizeof(int *));  // q pentru bfs
  for (int i = 0; i < width * height * depth; i++) {
    q[i] = calloc(3, sizeof(int));
  }
  int fata = 0, spate = 0;
  // adaugam punctul de start in coada
  q[spate][0] = startX;
  q[spate][1] = startY;
  q[spate++][2] = startZ;
  vizitat[startX][startY][startZ] = 1;
  char B = chunk[startX][startY][startZ];

  while (fata < spate) {
    int x = q[fata][0];
    int y = q[fata][1];
    int z = q[fata][2];
    fata++;

    // plasam celula curenta
    chunk_place_block(chunk, width, height, depth, x, y, z, block);

    // vecini
    const int directii[siete][3] = {{-1, 0, 0}, {1, 0, 0},  {0, -1, 0},
                          {0, 1, 0},  {0, 0, -1}, {0, 0, 1}};
    for (int d = 0; d < siete; d++) {
      int nouX = x + directii[d][0];
      int nouY = y + directii[d][1];
      int nouZ = z + directii[d][2];

      // verificam daca e in limite nevizitat si are aceeasi valoare
      if (nouX >= 0 && nouX < width && nouY >= 0 && nouY < height &&
          nouZ >= 0 && nouZ < depth && !vizitat[nouX][nouY][nouZ] &&
          chunk[nouX][nouY][nouZ] == B) {
        if (spate >= width * height * depth) {
          q = realloc(q, width * height * depth * 2 * sizeof(int *));
          for (int i = spate; i < width * height * depth * 2; i++)
            q[i] = calloc(3, sizeof(int));
        }

        vizitat[nouX][nouY][nouZ] = 1;
        q[spate][0] = nouX;
        q[spate][1] = nouY;
        q[spate++][2] = nouZ;
      }
    }
  }
}

char ***chunk_shell(char ***chunk, int width, int height, int depth,
                    char target_block, char shell_block) {
  int copy[width][height][depth];
  for (int d = 0; d < width; d++) {
    for (int r = 0; r < height; r++) {
      for (int c = 0; c < depth; c++) {
        copy[d][r][c] = chunk[d][r][c];
      }
    }
  }
  for (int cx = 0; cx < width; cx++)
    for (int cy = 0; cy < height; cy++)
      for (int cz = 0; cz < depth; cz++)
        if (copy[cx][cy][cz] == target_block) {
          for (float dx = 0; dx < (float)width; dx++)
            for (float dy = 0; dy < (float)height; dy++)
              for (float dz = 0; dz < (float)depth; dz++)
                if ((dx - (float)cx) * (dx - (float)cx) +
                            (dy - (float)cy) * (dy - (float)cy) +
                            (dz - (float)cz) * (dz - (float)cz) <
                        3 &&
                    chunk[(int)dx][(int)dy][(int)dz] != target_block)
                  chunk_place_block(chunk, width, height, depth, (int)dx, (int)dy,
                  (int)dz, shell_block);
        }
  return chunk;
}

char ***chunk_fill_xz(char ***chunk, int width, int height, int depth, int x,
                      int y, int z, char block) {
  char **graph = malloc((width) * sizeof(char *));
  char **vizitat = malloc((width) * sizeof(char *));
  for (int i = 0; i < width; i++) {
    graph[i] = calloc(depth, sizeof(char));
    vizitat[i] = calloc(depth, sizeof(char));
  }
  if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
    return chunk;
  }
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < depth; j++) {
      vizitat[i][j] = 0;
      graph[i][j] = chunk[i][y][j];
    }
  }
  bfs(chunk, y, height, graph, vizitat, width, depth, x, z, chunk[x][y][z],
      block);
  for (int i = 0; i < width; i++)
    free(vizitat[i]);
  free(vizitat);
  return chunk;
}

char ***chunk_fill(char ***chunk, int width, int height, int depth, int x,
                   int y, int z, char block) {
  char ***vizitat = malloc(width * sizeof *vizitat);
  for (int x = 0; x < width; x++) {
    vizitat[x] = malloc(height * sizeof **vizitat);
    for (int y = height - 1; y >= 0; y--) {
      vizitat[x][y] = malloc(depth * sizeof ***vizitat);
    }
  }
  if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
    return chunk;
  }
  bfs3d(chunk, vizitat, width, height, depth, x, y, z, block);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      free(vizitat[i][j]);
    }
    free(vizitat[i]);
  }
  free(vizitat);
  return chunk;
}
