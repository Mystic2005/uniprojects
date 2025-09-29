/* Bostangiu Luca-Nicolae - 311CB */

#include "tema1.h"

int main() {
  FILE *f = fopen("tema1.in", "r");
  int nrPage;
  struct page *pages = parsing(f, &nrPage);
  struct browser *b = init();

  // parsing pentru comenzi
  int nrComenzi;
  fscanf(f, "%d", &nrComenzi);
  char newl;
  fscanf(f, "%c", &newl); // \n
  int lastid = 0;
  while (nrComenzi--) {
    char *buffer = malloc(100 * sizeof(char));
    fgets(buffer, 100, f);
    if (strchr(buffer, '\n')) {
      char *p = strchr(buffer, '\n');
      *p = '\0';
    }
    if (strstr(buffer, "NEW_TAB"))
      new_tab(b, &lastid);
    else if (strstr(buffer, "CLOSE"))
      close(b);
    else if (strstr(buffer, "NEXT"))
      next(b);
    else if (strstr(buffer, "PREV"))
      prev(b);
    else if (strstr(buffer, "OPEN")) {
      char *p = strtok(buffer, " ");
      p = strtok(NULL, " ");
      int id = atoi(p);
      open(b, id, lastid);
    } else if (strstr(buffer, "PRINT_HISTORY")) {
      char *p = strtok(buffer, " ");
      p = strtok(NULL, " ");
      int id = atoi(p);
      print_history(b, id);
    } else if (strstr(buffer, "PRINT"))
      print(b);
    else if (strstr(buffer, "PAGE")) {
      char *p = strtok(buffer, " ");
      p = strtok(NULL, " ");
      int id = atoi(p);
      page(b, id, pages, nrPage);
    } else if (strstr(buffer, "BACKWARD"))
      backward(b);
    else if (strstr(buffer, "FORWARD"))
      forward(b);
    free(buffer);
  }

  // free
  for (int i = 1; i < nrPage; i++) {
    free(pages[i].description);
  }
  if (pages) {
    free(pages[0].description);
    free(pages);
  }
  fclose(f);
  freebrowser(&b);
  return 0;
}

struct page *parsing(FILE *f, int *nrPage) {
  fscanf(f, "%d", nrPage);
  if (!nrPage)
    return NULL;
  (*nrPage)++;
  struct page *Pages = malloc(*nrPage * sizeof(struct page));
  if (!Pages)
    return NULL;
  Pages[0].description = malloc(strlen("Computer Science\n") + 1);
  strcpy(Pages[0].description, "Computer Science\n");
  for (int i = 1; i < *nrPage; i++) { // bagam in struct datele
    fscanf(f, "%d", &Pages[i].id);
    char *buffer = malloc(100 * sizeof(char));
    fscanf(f, "%c", buffer); // \n
    fgets(buffer, 100, f);
    if (strchr(buffer, '\n')) {
      char *p = strchr(buffer, '\n');
      *p = '\0';
    }
    strcpy(Pages[i].url, buffer);
    fgets(buffer, 100, f);
    Pages[i].description = malloc(strlen(buffer) + 1);
    strcpy(Pages[i].description, buffer);
    free(buffer);
  }
  return Pages;
}