/* Bostangiu Luca-Nicolae - 311CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct page {
    int id;
    char url[50];
    char *description;
};

struct tab {
    int id;
    struct page *currentPage;
    struct stack *backwardStack;
    struct stack *forwardStack;
};

struct browser {
    struct tab *current;
    struct tabsList *list;
};

struct tabsList {
    struct tab *currentTab;
    struct tabsList *prev;
    struct tabsList *next;
};

struct stack {
    struct page *current;
    struct stack *nextPage;
};

struct browser* init();
void new_tab(struct browser *b, int *lastid);
void close(struct browser *b);
void open(struct browser *b, int id, int lastid);
void next(struct browser *b);
void prev(struct browser *b);
void freebrowser(struct browser **b);
void page(struct browser *b, int id, struct page *pages, int nrPage);

struct page* Pop(struct stack **vf);
void Push(struct stack **vf, struct page *page);
void backward(struct browser *b);
void forward(struct browser *b);

struct page* parsing(FILE *f, int *nrPage);
void print(struct browser *b);
void print_history (struct browser *b, int id);
