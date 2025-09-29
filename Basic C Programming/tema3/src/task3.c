#include "task3.h"
#include <string.h>

#define magic 53
#define magic2 40

char **split_into_blocks_and_pad(secretariat *s, int *p) {
  char **blocks = malloc(4 * sizeof(char *));
  int blocks_size = magic * s->nr_studenti;
  if (blocks_size % 4)
    blocks_size = blocks_size / 4 + 1;
  else
    blocks_size = blocks_size / 4;
  char *block_aux = calloc(blocks_size * 4, sizeof(char));
  for (int i = 0; i < 4; i++) {
    blocks[i] = calloc(blocks_size, sizeof(char));
  }
  int k = 0;
  for (int i = 0; i < s->nr_studenti; i++) {
    char *p = (char *)(&s->studenti[i].id);
    for (int j = 0; j < 4; j++) {
      block_aux[k++] = p[j];
    }
    for (int j = 0; j < magic2; j++) {
      block_aux[k++] = s->studenti[i].nume[j];
    }
    p = (char *)(&s->studenti[i].an_studiu);
    for (int j = 0; j < 4; j++) {
      block_aux[k++] = p[j];
    }
    block_aux[k++] = s->studenti[i].statut;
    p = (char *)(&s->studenti[i].medie_generala);
    for (int j = 0; j < 4; j++) {
      block_aux[k++] = p[j];
    }
  }
  k = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < blocks_size; j++) {
      blocks[i][j] = block_aux[k++];
    }
  }
  p[0] = blocks_size;
  return blocks;
}

char *XOR(char *blocks, char *IV, int len) {
  char *enc_blocks = malloc(len * sizeof(char));
  for (int i = 0; i < len; i++) {
    enc_blocks[i] = (char)(blocks[i] ^ IV[i]);
  }
  return enc_blocks;
}

void S_BOX(char *blocks_enc, char *IV, int len) {
  for (int i = 0; i < (int)strlen(IV); i++) {
    blocks_enc[i] = (char)(blocks_enc[i] ^ IV[i]);
  }
}

void P_BOX(char *block_enc, int len) {
  char *aux = malloc(len * sizeof(char));
  for (int i = 0; i < len; i++) {
    int new_pos = (i * (len - 1) + 2) % len;
    aux[new_pos] = block_enc[i];
  }
  for (int i = 0; i < len; i++) {
    block_enc[i] = aux[i];
  }
  free(aux);
}

void cripteaza_studenti(secretariat *secretariat, void *key, size_t key_len,
                        void *iv, size_t iv_len, char *cale_output) {
  int p[1];
  p[0] = 0;
  char **blocks = split_into_blocks_and_pad(secretariat, p);
  FILE *out = fopen(cale_output, "w");

  char *c_key = (char *)key;
  char *full_key = malloc(p[0] * sizeof(char));
  char *c_iv = (char *)iv;
  char *full_iv = malloc(p[0] * sizeof(char));
  for (int i = 0; i < p[0]; i++) {
    full_key[i] = c_key[i % key_len];
    full_iv[i] = c_iv[i % iv_len];
  }
  char **blocks_enc = malloc(4 * sizeof(char *));
  blocks_enc[0] = XOR(blocks[0], full_iv, p[0]);

  S_BOX(blocks_enc[0], full_key, p[0]);

  P_BOX(blocks_enc[0], p[0]);
  // Criptarea celor 3 blocuri ramase
  for (int i = 1; i < 4; i++) {
    blocks_enc[i] = XOR(blocks[i], blocks_enc[i - 1], p[0]);
    S_BOX(blocks_enc[i], full_key, p[0]);
    P_BOX(blocks_enc[i], p[0]);
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < p[0]; j++) {
      fprintf(out, "%c", blocks_enc[i][j]);
    }
  }
  fclose(out);
  free(full_key);
  free(full_iv);
  for (int i = 0; i < 4; i++) {
    free(blocks_enc[i]);
    free(blocks[i]);
  }
  free(blocks_enc);
  free(blocks);
}
