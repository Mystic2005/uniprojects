#include "chunk.h"

char ***chunk_place_block(char ***chunk, int width, int height, int depth,
                          int x, int y, int z, char block) {
  if (x < width && x >= 0 && y < height && y >= 0 && z < depth && z >= 0) {
    chunk[x][y][z] = block;
  }
  return chunk;
}

char ***chunk_fill_cuboid(char ***chunk, int width, int height, int depth,
                          int x0, int y0, int z0, int x1, int y1, int z1,
                          char block) {
  int dx = (x0 < x1) ? 1 : -1;
  int dy = (y0 < y1) ? 1 : -1;
  int dz = (z0 < z1) ? 1 : -1;

  for (int x = x0; x != x1 + dx; x += dx) {
    for (int y = y0; y != y1 + dy; y += dy) {
      for (int z = z0; z != z1 + dz; z += dz) {
        chunk_place_block(chunk, width, height, depth, x, y, z, block);
      }
    }
  }

  return chunk;
}

char ***chunk_fill_sphere(char ***chunk, int width, int height, int depth,
                          int x, int y, int z, double radius, char block) {
  for (float dx = 0; dx < (float)width; dx++)
    for (float dy = 0; dy < (float)height; dy++)
      for (float dz = 0; dz < (float)depth; dz++)
        if (radius >= 0 && (dx - (float)x) * (dx - (float)x) +
                                   (dy - (float)y) * (dy - (float)y) +
                                   (dz - (float)z) * (dz - (float)z) <=
                               radius * radius)
          chunk_place_block(chunk, width, height, depth, (int)dx, (int)dy, (int)dz, block);
}
