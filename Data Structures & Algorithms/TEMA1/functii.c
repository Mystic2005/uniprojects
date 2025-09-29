/* Bostangiu Luca-Nicolae - 311CB */

#include "tema1.h"

struct browser *init() {
  struct browser *b = malloc(sizeof(struct browser)); // browser
  if (!b)
    return NULL;
  b->list = malloc(sizeof(struct tabsList)); // santinela
  if (!b->list)
    return NULL;
  b->current = malloc(sizeof(struct tab)); // tab initial
  if (!b->current)
    return NULL;
  b->current->currentPage = malloc(sizeof(struct page)); // page initial
  if (!b->current->currentPage)
    return NULL;

  // initializare page
  b->current->currentPage->id = 0;
  strcpy(b->current->currentPage->url, "https://acs.pub.ro/");
  b->current->currentPage->description =
      malloc(strlen("Computer Science\n") + 1);
  if (!b->current->currentPage->description)
    return NULL;
  strcpy(b->current->currentPage->description, "Computer Science\n");

  // initializare tab
  b->current->id = 0;
  b->current->backwardStack = NULL;
  b->current->forwardStack = NULL;

  // initializare santinela
  b->list->currentTab = NULL;
  struct tabsList *new = malloc(sizeof(struct tabsList));
  if (!new)
    return NULL;
  new->currentTab = b->current;
  new->next = b->list;
  new->prev = b->list;
  b->list->next = new;
  b->list->prev = new;

  return b;
}

void new_tab(struct browser *b, int *lastid) {
  struct tab *newTab = malloc(sizeof(struct tab));

  // init page
  newTab->currentPage = malloc(sizeof(struct page));
  if (!newTab->currentPage)
    return;
  newTab->currentPage->id = 0;
  strcpy(newTab->currentPage->url, "https://acs.pub.ro/");
  newTab->currentPage->description = malloc(strlen("Computer Science\n") + 1);
  if (!newTab->currentPage->description)
    return;
  strcpy(newTab->currentPage->description, "Computer Science\n");

  // init tab
  newTab->backwardStack = NULL;
  newTab->forwardStack = NULL;

  // adaugare in browser(+lista)
  b->current = newTab;
  struct tabsList *new = malloc(sizeof(struct tabsList));
  if (!new)
    return;
  new->currentTab = b->current;
  struct tabsList *last = b->list->prev;
  new->next = b->list;
  new->prev = last;
  last->next = new;
  b->list->prev = new;
  newTab->id = ++(*lastid);
}

void close(struct browser *b) {
  struct page *currentPage = b->current->currentPage;
  struct tab *currentTab = b->current;

  if (currentTab->id == 0) {
    printf("403 Forbidden\n"); // err
  } else {
    struct tabsList *currentCell = b->list;
    while (currentCell->currentTab != currentTab) {
      currentCell = currentCell->next;
    } // ma duc pe currentCell si dau free + schimb pe penultima
    b->current = currentCell->prev->currentTab;
    currentCell->prev->next = currentCell->next;
    currentCell->next->prev = currentCell->prev;

    // free la stive
    struct stack *bstack = currentTab->backwardStack;
    while (bstack) {
      struct stack *temp = bstack;
      bstack = bstack->nextPage;
      if (temp->current) {
        free(temp->current->description);
        free(temp->current);
      }
      free(temp);
    }
    struct stack *fstack = currentTab->forwardStack;
    while (fstack) {
      struct stack *temp = fstack;
      fstack = fstack->nextPage;
      if (temp->current) {
        free(temp->current->description);
        free(temp->current);
      }
      free(temp);
    }
    free(currentPage->description);
    free(currentPage);
    free(currentTab);
    free(currentCell);
  }
}

void open(struct browser *b, int id, int lastid) {
  struct tabsList *currentCell = b->list;
  lastid++;    // caz pt lastid = 0 nu intra in loop
  lastid *= 3; // prevent infinite loop
  while (lastid) {
    if (currentCell->currentTab != NULL && currentCell->currentTab->id == id)
      break;
    currentCell = currentCell->next; // ma duc pe celula cu id ul respectiv
    lastid--;
  }
  if (!currentCell || lastid == 0) {
    printf("403 Forbidden\n");
  } else {
    b->current = currentCell->currentTab; // o deschid
  }
}

void next(struct browser *b) {
  struct tab *currentTab = b->current;
  struct tabsList *currentCell = b->list;
  while (currentCell->currentTab != currentTab) {
    currentCell = currentCell->next;
  } // celula activa
  struct tabsList *nextCell = currentCell->next;
  while (nextCell->currentTab == NULL) {
    nextCell = nextCell->next;
  } // sar peste santinela
  b->current = nextCell->currentTab; // deschid tab celula next
}

void prev(struct browser *b) {
  struct tab *currentTab = b->current;
  struct tabsList *currentCell = b->list;
  while (currentCell->currentTab != currentTab) {
    currentCell = currentCell->prev;
  } // celula activa
  if (currentCell->prev == b->list) {
    currentCell = b->list->prev;
    b->current = currentCell->currentTab;       // deschid tab celula prev
  } else                                        // sar peste santinela
    b->current = currentCell->prev->currentTab; // deschid tab celula prev
}

void page(struct browser *b, int id, struct page *pages, int nrPage) {
  int i = 1;
  while (i < nrPage && pages[i].id != id)
    i++;

  if (i < nrPage) {
    Push(&b->current->backwardStack, b->current->currentPage);

    struct stack *fstack = b->current->forwardStack;
    while (fstack) {
      struct stack *temp = fstack;
      fstack = fstack->nextPage;
      if (temp->current) {
        free(temp->current->description);
        free(temp->current);
      }
      free(temp);
    }
    b->current->forwardStack = NULL;

    // init page
    struct page *new = malloc(sizeof(struct page));
    if (!new)
      return;
    new->id = id;
    strcpy(new->url, pages[i].url);
    new->description = malloc(strlen(pages[i].description) + 1);
    if (!new->description)
      return;
    strcpy(new->description, pages[i].description);
    b->current->currentPage = new;
  } else
    printf("403 Forbidden\n");
}

struct page *Pop(struct stack **vf) {
  if (*vf == NULL)
    return NULL;
  struct stack *aux;
  struct page *page;
  page = (*vf)->current; /* 1 */
  aux = *vf;             /* 2 */
  *vf = aux->nextPage;   /* 3 */
  free(aux);             /* 4 */
  return page;
}

void backward(struct browser *b) {
  if (!b->current->backwardStack) {
    printf("403 Forbidden\n");
  } else { // realizez operatia descrisa
    Push(&b->current->forwardStack, b->current->currentPage);
    b->current->currentPage = Pop(&b->current->backwardStack);
  }
}

void forward(struct browser *b) {
  if (!b->current->forwardStack) {
    printf("403 Forbidden\n");
  } else { // realizez operatia descrisa
    Push(&b->current->backwardStack, b->current->currentPage);
    b->current->currentPage = Pop(&b->current->forwardStack);
  }
}

void Push(struct stack **vf, struct page *page) {
  struct stack *aux = malloc(sizeof(struct stack)); /* 1 */
  if (!aux)
    return;
  aux->current = page;
  aux->nextPage = *vf; /* 2 */
  *vf = aux;           /* 3 */
}

void print(struct browser *b) {
  if (!b)
    return;

  struct tabsList *santinela = b->list;
  struct tabsList *curr = santinela->next;
  while (curr != santinela && curr->currentTab != b->current) {
    curr = curr->next;
  } // ma asez pe tab curent

  struct tabsList *currTab = curr; // salvez pt conditie
  printf("%d", curr->currentTab->id);
  curr = curr->next;
  while (curr != currTab) {
    if (curr != santinela)
      printf(" %d", curr->currentTab->id);
    curr = curr->next;
  }
  printf("\n");

  // description
  printf("%s", b->current->currentPage->description);
}

void print_history(struct browser *b, int id) {
  if (!b)
    return;

  struct tabsList *santinela = b->list;
  struct tabsList *curr = santinela->next;
  while (curr != santinela && curr->currentTab->id != id) {
    curr = curr->next;
  } // ma asez pe tab curent

  if (curr == santinela) {
    printf("403 Forbidden\n");
    return;
  }

  // pentru fstack fac o stiva aux pentru ordine inversa
  struct stack *aux = NULL;
  struct stack *fstack = curr->currentTab->forwardStack;
  while (fstack) {
    Push(&aux, fstack->current);
    fstack = fstack->nextPage;
  }
  while (aux) // afisare
    printf("%s\n", Pop(&aux)->url);

  if (curr->currentTab->currentPage) // pagina curr
    printf("%s\n", curr->currentTab->currentPage->url);

  struct stack *bstack = curr->currentTab->backwardStack;
  while (bstack) {
    printf("%s\n", bstack->current->url);
    bstack = bstack->nextPage;
  }
}

void freebrowser(struct browser **b) {
  if (!*b)
    return;

  struct tabsList *santinela = (*b)->list;
  struct tabsList *curr = santinela->next;
  while (curr != santinela) {
    struct tab *currtab = curr->currentTab;

    // free la stive
    struct stack *bstack = currtab->backwardStack;
    while (bstack) {
      struct stack *temp = bstack;
      bstack = bstack->nextPage;
      if (temp->current) {
        free(temp->current->description);
        free(temp->current);
      }
      free(temp);
    }
    struct stack *fstack = currtab->forwardStack;
    while (fstack) {
      struct stack *temp = fstack;
      fstack = fstack->nextPage;
      if (temp->current) {
        free(temp->current->description);
        free(temp->current);
      }
      free(temp);
    }

    // free la page
    free(currtab->currentPage->description);
    free(currtab->currentPage);

    // free restu
    free(currtab);
    struct tabsList *temp = curr;
    curr = curr->next;
    free(temp);
  }
  free(santinela);
  free(*b);
  *b = NULL;
}