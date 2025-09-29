#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>

enum {
patrumii = 4096,
treijdoi = 32,
siete = 6,
dousute = 256
};


unsigned char *chunk_encode(char ***chunk, int width, int height, int depth,
                            int *length) {
  unsigned char *encoded =
      malloc(width * height * depth * sizeof(unsigned char));
  char last = chunk[0][0][0];
  int count = 0;
  int k = 0;
  for (int y = 0; y < height; y++)
    for (int z = 0; z < depth; z++)
      for (int x = 0; x < width; x++) {
        if (last == chunk[x][y][z] &&
            x * y * z != (height - 1) * (depth - 1) * (width - 1)) {
          count++;
        } else {
          if (x * y * z == (height - 1) * (depth - 1) * (width - 1) &&
              last == chunk[x][y][z]) {
            count++;
            if (count >= patrumii) {
              while (count > 0) {
                if (count >= patrumii) {
                  int x = patrumii-1;
                  if (count < treijdoi) {
                    encoded[k] = (last << siete);
                    encoded[k++] += x;
                  } else {
                    encoded[k] = (last << siete) + (1 << (siete-1));
                    encoded[k++] += (x >> (siete+2));
                    encoded[k++] = (x % dousute);
                  }
                } else {
                  if (count < treijdoi) {
                    encoded[k] = (last << siete);
                    encoded[k++] += count;
                  } else {
                    encoded[k] = (last << siete) + (1 << (siete-1));
                    encoded[k++] += (count >> (siete+2));
                    encoded[k++] = (count % dousute);
                  }
                }
                count -= (patrumii-1);
              }
            } else {
              if (count < treijdoi) {
                encoded[k] = (last << siete);
                encoded[k++] += count;
              } else {
                encoded[k] = (last << siete) + (1 << (siete-1));
                encoded[k++] += (count >> (siete+2));
                encoded[k++] = (count % dousute);
              }
            }
            last = chunk[x][y][z];
            count = 1;
          } else {
            if (count >= patrumii) {
              while (count > 0) {
                if (count >= patrumii) {
                  int x = (patrumii-1);
                  if (count < treijdoi) {
                    encoded[k] = (last << siete);
                    encoded[k++] += x;
                  } else {
                    encoded[k] = (last << siete) + (1 << (siete-1));
                    encoded[k++] += (x >> (siete+2));
                    encoded[k++] = (x % dousute);
                  }
                } else {
                  if (count < treijdoi) {
                    encoded[k] = (last << siete);
                    encoded[k++] += count;
                  } else {
                    encoded[k] = (last << siete) + (1 << (siete-1));
                    encoded[k++] += (count >> (siete+2));
                    encoded[k++] = (count % dousute);
                  }
                }
                count -= (patrumii-1);
              }
            } else {
              if (count < treijdoi) {
                encoded[k] = (last << siete);
                encoded[k++] += count;
              } else {
                encoded[k] = (last << siete) + (1 << (siete-1));
                encoded[k++] += (count >> (siete+2));
                encoded[k++] = (count % dousute);
              }
            }
            last = chunk[x][y][z];
            count = 1;
          }
        }
      }
  if (chunk[width - 1][height - 1][depth - 1] !=
          chunk[width - 2][height - 1][depth - 1] &&
      count == 1) {
    encoded[k] = (last << siete);
    encoded[k++] += count;
  }
  *length = k;
  return encoded;
}

char ***chunk_decode(unsigned char *code, int width, int height, int depth) {
  char ***chunk = malloc(width * sizeof *chunk);

  for (int x = 0; x < width; x++) {
    chunk[x] = malloc(height * sizeof **chunk);
    for (int y = height - 1; y >= 0; y--)
      chunk[x][y] = malloc(depth * sizeof ***chunk);
  }

  int i = 0, count = 0;
  int ok = 1;
  while (code[i] || (code[i] & (1 << (siete-1)))) {
    if (code[i] & (1 << (siete-1))) {  // 2 unsigned char
      int amount = (code[i] % treijdoi) * dousute;
      char block = (char)(code[i++] >> siete);
      amount += code[i++];
      ok = 1;
      int index = 0;
      for (int y = 0; y < height && ok && amount; y++)
        for (int z = 0; z < depth && ok; z++)
          for (int x = 0; x < width && ok; x++, index++) {
            if (index < count + amount && index >= count) {
              chunk[x][y][z] = block;
            }
          }
      count = count + amount;
    } else {  // 1 unsigned char
      int amount = code[i] % treijdoi;
      char block = (char)(code[i++] >> siete);
      ok = 1;
      int index = 0;
      for (int y = 0; y < height && ok && amount; y++)
        for (int z = 0; z < depth && ok; z++)
          for (int x = 0; x < width && ok; x++, index++) {
            if (index < count + amount && index >= count) {
              chunk[x][y][z] = block;
            }
          }
      count = count + amount;
    }
  }
  return chunk;
}
