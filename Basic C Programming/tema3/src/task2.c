#define sutica 100
#define precizie 1000
#define aproximare 10
#define size 200
#define cinci 5
#define sase 6
#define sapte 7
#define noua 9

#include "task2.h"

void print_student(student s, int *select_q, int select_length) {
  for (int i = 0; i < select_length; i++) {
    if (i >= 1)
      printf(" ");
    switch (select_q[i]) {
    case 1:
      printf("%d", s.id);
      break;
    case 2:
      printf("%s", s.nume);
      break;
    case 3:
      printf("%d", s.an_studiu);
      break;
    case 4:
      printf("%c", s.statut);
      break;
    case cinci:
      printf("%.2f", s.medie_generala);
      break;
    case sase:
      printf("%d %s %d %c %.2f", s.id, s.nume, s.an_studiu, s.statut,
             s.medie_generala);
      break;
    }
  }
  printf("\n");
}

void print_materie(materie s, int *select_q, int select_length) {
  for (int i = 0; i < select_length; i++) {
    if (i >= 1)
      printf(" ");
    switch (select_q[i]) {
    case 1:
      printf("%d", s.id);
      break;
    case 2:
      printf("%s", s.nume);
      break;
    case 3:
      printf("%s", s.nume_titular);
      break;
    case 4:
      printf("%d %s %s", s.id, s.nume, s.nume_titular);
      break;
    }
  }
  printf("\n");
}

void print_inrolare(inrolare s, int *select_q, int select_length) {
  for (int i = 0; i < select_length; i++) {
    if (i >= 1)
      printf(" ");
    switch (select_q[i]) {
    case 1:
      printf("%d", s.id_student);
      break;
    case 2:
      printf("%d", s.id_materie);
      break;
    case 3:
      for (int j = 0; j < 3; j++) {
        if (j >= 1)
          printf(" ");
        printf("%.2f", s.note[j]);
      }
      break;
    case 4:
      printf("%d %d", s.id_student, s.id_materie);
      for (int j = 0; j < 3; j++) {
        printf(" ");
        printf("%.2f", s.note[j]);
      }
      break;
    }
  }
  printf("\n");
}

int check_studenti(char *p) {
  if (strcmp(p, "id") == 0)
    return 1;
  if (strcmp(p, "nume") == 0)
    return 2;
  if (strcmp(p, "an_studiu") == 0)
    return 3;
  if (strcmp(p, "statut") == 0)
    return 4;
  if (strcmp(p, "medie_generala") == 0)
    return cinci;
  if (strcmp(p, "*") == 0)
    return sase;
}

int check_materii(char *p) {
  if (strcmp(p, "id") == 0)
    return 1;
  if (strcmp(p, "nume") == 0)
    return 2;
  if (strcmp(p, "nume_titular") == 0)
    return 3;
  if (strcmp(p, "*") == 0)
    return 4;
}

int check_inrolari(char *p) {
  if (strcmp(p, "id_student") == 0)
    return 1;
  if (strcmp(p, "id_materie") == 0)
    return 2;
  if (strcmp(p, "note") == 0)
    return 3;
  if (strcmp(p, "*") == 0)
    return 4;
}

int check_operator(char *p) {
  if (strcmp(p, "=") == 0)
    return 1;
  if (strcmp(p, "<") == 0)
    return 2;
  if (strcmp(p, ">") == 0)
    return 3;
  if (strcmp(p, "<=") == 0)
    return 4;
  if (strcmp(p, ">=") == 0)
    return cinci;
  if (strcmp(p, "!=") == 0)
    return sase;
}

int check_condition_student(student s, int condition[2], int operator[2],
                            float value[2]) {
  int i = 0;
  float val[2];
  int conditie = 1;
  while (i < 2 && condition[i] != 0) {
    switch (condition[i]) {
    case 1:
      val[i] = (float)s.id;
      break;
    case 3:
      val[i] = (float)s.an_studiu;
      break;
    case 4:
      val[i] = (float)s.statut;
      break;
    case cinci:
      val[i] = s.medie_generala;
      break;
    default:
      break;
    }
    switch (operator[i]) {
    case 1:
      if (!(val[i] == value[i]))
        conditie = 0;
      break;
    case 2:
      if (!(val[i] < value[i]))
        conditie = 0;
      break;
    case 3:
      if (!(val[i] > value[i]))
        conditie = 0;
      break;
    case 4:
      if (!(val[i] <= value[i]))
        conditie = 0;
      break;
    case cinci:
      if (!(val[i] >= value[i]))
        conditie = 0;
      break;
    case sase:
      if (!(val[i] != value[i]))
        conditie = 0;
      break;
    }
    i++;
  }
  if (conditie == 0)
    return 0;
  else
    return 1;
}

int check_condition_materie(materie s, int condition[2], int operator[2],
                            float value[2]) {
  int i = 0;
  float val[2];
  int conditie = 1;
  while (i < 2 && condition[i] != 0) {
    val[i] = (float)s.id;
    switch (operator[i]) {
    case 1:
      if (!(val[i] == value[i]))
        conditie = 0;
      break;
    case 2:
      if (!(val[i] < value[i]))
        conditie = 0;
      break;
    case 3:
      if (!(val[i] > value[i]))
        conditie = 0;
      break;
    case 4:
      if (!(val[i] <= value[i]))
        conditie = 0;
      break;
    case cinci:
      if (!(val[i] >= value[i]))
        conditie = 0;
      break;
    case sase:
      if (!(val[i] != value[i]))
        conditie = 0;
      break;
    }
    i++;
  }
  if (conditie == 0)
    return 0;
  else
    return 1;
}

int check_condition_inrolare(inrolare s, int condition[2], int operator[2],
                             float value[2]) {
  int i = 0;
  float val[2];
  int conditie = 1;
  while (i < 2 && condition[i] != 0) {
    switch (condition[i]) {
    case 1:
      val[i] = (float)s.id_student;
      break;
    case 2:
      val[i] = (float)s.id_materie;
      break;
    default:
      break;
    }
    switch (operator[i]) {
    case 1:
      if (!(val[i] == value[i]))
        conditie = 0;
      break;
    case 2:
      if (!(val[i] < value[i]))
        conditie = 0;
      break;
    case 3:
      if (!(val[i] > value[i]))
        conditie = 0;
      break;
    case 4:
      if (!(val[i] <= value[i]))
        conditie = 0;
      break;
    case cinci:
      if (!(val[i] >= value[i]))
        conditie = 0;
      break;
    case sase:
      if (!(val[i] != value[i]))
        conditie = 0;
      break;
    }
    i++;
  }
  if (conditie == 0)
    return 0;
  else
    return 1;
}

void update_student(student *s, int select_q, float val, char *nume_val) {
  if (select_q == 2) {
    snprintf(s->nume, sutica, "%s", nume_val);
  } else if (select_q == 4) {
    s->statut = (char)val;
  } else if (select_q == 3) {
    s->an_studiu = (int)val;
  } else if (select_q == cinci) {
    s->medie_generala = val;
  }
}

void update_materie(materie *s, int select_q, char *nume_val) {
  if (select_q == 2) {
    snprintf(s->nume, sutica, "%s", nume_val);
  }
}

void update_inrolare(inrolare *s, int select_q, float val, float vect[3]) {
  if (select_q == 1) {
    s->id_student = (int)val;
  } else if (select_q == 2) {
    s->id_materie = (int)val;
  } else {
    s->note[0] = vect[0];
    s->note[1] = vect[1];
    s->note[2] = vect[2];
  }
}

void delete_student(student *s, int start, int end) {
  for (start; start <= end - 2; start++) {
    snprintf(s[start].nume, sutica, "%s", s[start + 1].nume);
    s[start].id = s[start + 1].id;
    s[start].an_studiu = s[start + 1].an_studiu;
    s[start].statut = s[start + 1].statut;
    s[start].medie_generala = s[start + 1].medie_generala;
  }
}

void delete_materie(materie *s, int start, int end) {
  for (start; start <= end - 2; start++) {
    snprintf(s[start].nume, sutica, "%s", s[start + 1].nume);
    snprintf(s[start].nume_titular, sutica, "%s", s[start + 1].nume_titular);
    s[start].id = s[start + 1].id;
  }
}

void delete_inrolare(inrolare *s, int start, int end) {
  for (start; start <= end - 2; start++) {
    s[start].id_student = s[start + 1].id_student;
    s[start].id_materie = s[start + 1].id_materie;
    s[start].note[0] = s[start + 1].note[0];
    s[start].note[1] = s[start + 1].note[1];
    s[start].note[2] = s[start + 1].note[2];
  }
}

int main(int argc, char *argv[]) {
  secretariat *s = citeste_secretariat(argv[1]);
  int number = 0;
  scanf("%d", &number);
  getchar();
  char *buffer = malloc(size * sizeof(char));
  char *p = NULL;
  while (number) {
    if (!fgets(buffer, size, stdin)) {
      break;
    }
    char *newline = strchr(buffer, ';');
    if (newline)
      *newline = 0;
    char *table = malloc(size * sizeof(char));
    if (strstr(buffer, "FROM")) {
      p = strstr(buffer, "FROM");
      snprintf(table, size, "%s", p);
      char *aux = malloc(size * sizeof(char));
      snprintf(aux, size, "%s", table + cinci);
      snprintf(table, size, "%s", aux);
      free(aux);
      newline = strchr(table, ' ');
      if (newline)
        *newline = 0;
    }

    if (!strstr(buffer, "FROM") && strstr(buffer, "UPDATE")) {
      p = strstr(buffer, "UPDATE");
      snprintf(table, size, "%s", p);
      char *aux = malloc(size * sizeof(char));
      snprintf(aux, size, "%s", table + sapte);
      snprintf(table, size, "%s", aux);
      free(aux);
      newline = strchr(table, ' ');
      if (newline)
        *newline = 0;
    }

    int condition[2], operator[2];
    float value[2];
    condition[0] = 0;
    condition[1] = 0;
    char *copy = malloc(size * sizeof(char));
    if (strstr(buffer, "WHERE")) {
      if (strcmp(table, "studenti") == 0) {
        p = strstr(buffer, "WHERE");
        snprintf(copy, size, "%s", p);
        char *aux = malloc(size * sizeof(char));
        snprintf(aux, size, "%s", copy + sase);
        snprintf(copy, size, "%s", aux);
        free(aux);
        p = strtok(copy, " ");
        condition[0] = check_studenti(p);
        p = strtok(NULL, " ");
        operator[0] = check_operator(p);
        p = strtok(NULL, " ");
        if (p[0] <= '9' && p[0] >= '0')
          value[0] = (float)atof(p);
        else
          value[0] = p[0];
        if (strstr(buffer, "AND")) {
          p = strtok(NULL, " ");
          if (strcmp(p, "AND") == 0) {
            p = strtok(NULL, " ");
            condition[1] = check_studenti(p);
            p = strtok(NULL, " ");
            operator[1] = check_operator(p);
            p = strtok(NULL, " ");
            if (p[0] <= '9' && p[0] >= '0')
              value[1] = (float)atof(p);
            else
              value[1] = p[0];
          }
        }
      } else if (strcmp(table, "materii") == 0) {
        p = strstr(buffer, "WHERE");
        snprintf(copy, size, "%s", p);
        char *aux = malloc(size * sizeof(char));
        snprintf(aux, size, "%s", copy + sase);
        snprintf(copy, size, "%s", aux);
        free(aux);
        p = strtok(copy, " ");
        condition[0] = check_materii(p);
        p = strtok(NULL, " ");
        operator[0] = check_operator(p);
        p = strtok(NULL, " ");
        if (p[0] <= '9' && p[0] >= '0')
          value[0] = (float)atof(p);
        else
          value[0] = p[0];
        if (strstr(buffer, "AND")) {
          p = strtok(NULL, " ");
          if (strcmp(p, "AND") == 0) {
            p = strtok(NULL, " ");
            condition[1] = check_materii(p);
            p = strtok(NULL, " ");
            operator[1] = check_operator(p);
            p = strtok(NULL, " ");
            if (p[0] <= '9' && p[0] >= '0')
              value[1] = (float)atof(p);
            else
              value[1] = p[0];
          }
        }
      } else if (strcmp(table, "inrolari") == 0) {
        p = strstr(buffer, "WHERE");
        snprintf(copy, size, "%s", p);
        char *aux = malloc(size * sizeof(char));
        snprintf(aux, size, "%s", copy + sase);
        snprintf(copy, size, "%s", aux);
        free(aux);
        p = strtok(copy, " ");
        condition[0] = check_inrolari(p);
        p = strtok(NULL, " ");
        operator[0] = check_operator(p);
        p = strtok(NULL, " ");
        if (p[0] <= '9' && p[0] >= '0')
          value[0] = (float)atof(p);
        else
          value[0] = p[0];
        if (strstr(buffer, "AND")) {
          p = strtok(NULL, " ");
          if (strcmp(p, "AND") == 0) {
            p = strtok(NULL, " ");
            condition[1] = check_inrolari(p);
            p = strtok(NULL, " ");
            operator[1] = check_operator(p);
            p = strtok(NULL, " ");
            if (p[0] <= '9' && p[0] >= '0')
              value[1] = (float)atof(p);
            else
              value[1] = p[0];
          }
        }
      }
    }

    if (strstr(buffer, "SELECT")) {
      if (strcmp(table, "studenti") == 0) {
        p = strtok(buffer, " ");
        p = strtok(NULL, " ");
        int *select_q = malloc(cinci * sizeof(int));
        int select_length = 0;
        while (p[strlen(p) - 1] == ',') {
          p[strlen(p) - 1] = '\0';
          select_q[select_length] = check_studenti(p);
          select_length++;
          p = strtok(NULL, " ");
        }
        select_q[select_length] = check_studenti(p);
        select_length++;
        for (int i = 0; i < s->nr_studenti; i++) {
          if (check_condition_student(s->studenti[i], condition, operator,
                                      value))
            print_student(s->studenti[i], select_q, select_length);
          else if (!condition[0])
            print_student(s->studenti[i], select_q, select_length);
        }
        free(select_q);
      } else if (strcmp(table, "materii") == 0) {
        p = strtok(buffer, " ");
        p = strtok(NULL, " ");
        int *select_q = malloc(cinci * sizeof(int));
        int select_length = 0;
        while (p[strlen(p) - 1] == ',') {
          p[strlen(p) - 1] = '\0';
          select_q[select_length] = check_materii(p);
          select_length++;
          p = strtok(NULL, " ");
        }
        select_q[select_length] = check_materii(p);
        select_length++;
        for (int i = 0; i < s->nr_materii; i++) {
          if (check_condition_materie(s->materii[i], condition, operator,
                                      value))
            print_materie(s->materii[i], select_q, select_length);
          else if (!condition[0])
            print_materie(s->materii[i], select_q, select_length);
        }
        free(select_q);
      } else if (strcmp(table, "inrolari") == 0) {
        p = strtok(buffer, " ");
        p = strtok(NULL, " ");
        int *select_q = malloc(cinci * sizeof(int));
        int select_length = 0;
        while (p[strlen(p) - 1] == ',') {
          p[strlen(p) - 1] = '\0';
          select_q[select_length] = check_inrolari(p);
          select_length++;
          p = strtok(NULL, " ");
        }
        select_q[select_length] = check_inrolari(p);
        select_length++;
        for (int i = 0; i < s->nr_inrolari; i++) {
          if (check_condition_inrolare(s->inrolari[i], condition, operator,
                                       value))
            print_inrolare(s->inrolari[i], select_q, select_length);
          else if (!condition[0])
            print_inrolare(s->inrolari[i], select_q, select_length);
        }
        free(select_q);
      }
    } else if (strstr(buffer, "UPDATE")) {
      if (strcmp(table, "studenti") == 0) {
        p = strstr(buffer, "SET");
        int update_q = 0;
        char *aux = malloc(size * sizeof(char));
        char *name_val = malloc(size * sizeof(char));
        float val = 0;
        snprintf(name_val, size, "%s", "table");
        snprintf(aux, size, "%s", p + 4);
        p = strtok(aux, " ");
        update_q = check_studenti(p);
        p = strtok(NULL, " ");
        if (update_q == 2) {
          p = strtok(NULL, "\"");
          snprintf(name_val, size, "%s", p);
        } else {
          p = strtok(NULL, " ");
          if (update_q != 4) {
            val = (float)atof(p);
          } else {
            val = p[0];
          }
        }
        for (int i = 0; i < s->nr_studenti; i++) {
          if (check_condition_student(s->studenti[i], condition, operator,
                                      value))
            update_student(&s->studenti[i], update_q, val, name_val);
          else if (!condition[0])
            update_student(&s->studenti[i], update_q, val, name_val);
        }
        free(aux);
        free(name_val);
      } else if (strcmp(table, "materii") == 0) {
        p = strstr(buffer, "SET");
        int update_q = 0;
        char *aux = malloc(size * sizeof(char));
        char *name_val = malloc(size * sizeof(char));
        float val = 0;
        snprintf(aux, size, "%s", p + 4);
        p = strtok(aux, " ");
        update_q = check_materii(p);
        p = strtok(NULL, " ");
        if (update_q == 2) {
          p = strtok(NULL, "\"");
          snprintf(name_val, size, "%s", p);
        } else {
          p = strtok(NULL, " ");
          if (p[0] <= '9' && p[0] >= '0') {
            val = (float)atof(p);
          } else {
            val = p[0];
          }
        }
        for (int i = 0; i < s->nr_materii; i++) {
          if (check_condition_materie(s->materii[i], condition, operator,
                                      value))
            update_materie(&s->materii[i], update_q, name_val);
          else if (!condition[0])
            update_materie(&s->materii[i], update_q, name_val);
        }
        free(aux);
        free(name_val);
      } else if (strcmp(table, "inrolari") == 0) {
        p = strstr(buffer, "SET");
        int update_q = 0;
        char *aux = malloc(size * sizeof(char));
        float val = 0, vector[3];
        snprintf(aux, size, "%s", p + 4);
        p = strtok(aux, " ");
        update_q = check_inrolari(p);
        p = strtok(NULL, " ");
        if (update_q == 3) {
          p = strtok(NULL, " ");
          vector[0] = (float)atof(p);
          p = strtok(NULL, " ");
          vector[1] = (float)atof(p);
          p = strtok(NULL, " ");
          vector[2] = (float)atof(p);
        } else {
          p = strtok(NULL, " ");
          if (update_q != 3) {
            val = (float)atof(p);
          }
        }
        for (int i = 0; i < s->nr_inrolari; i++) {
          if (check_condition_inrolare(s->inrolari[i], condition, operator,
                                       value))
            update_inrolare(&s->inrolari[i], update_q, val, vector);
          else if (!condition[0])
            update_inrolare(&s->inrolari[i], update_q, val, vector);
        }
        free(aux);
        for (int j = 0; j < s->nr_studenti; j++) {
          float media = 0, k = 0;
          for (int i = 0; i < s->nr_inrolari; i++) {
            if (s->inrolari[i].id_student == s->studenti[j].id) {
              for (int d = 0; d < 3; d++) {
                media += s->inrolari[i].note[d];
              }
              k++;
            }
          }
          s->studenti[j].medie_generala = media / k;
          int media_aprox = (int)(s->studenti[j].medie_generala * precizie);
          if (media_aprox % aproximare > 4)
            s->studenti[j].medie_generala =
                (float)((media_aprox / aproximare) + 1) / sutica;
          else
            s->studenti[j].medie_generala =
                (float)(media_aprox / aproximare) / sutica;
          if (s->studenti[j].medie_generala < 0)
            s->studenti[j].medie_generala = 0;
        }
      }
    } else if (strstr(buffer, "DELETE")) {
      if (strcmp(table, "studenti") == 0) {
        for (int i = 0; i <= s->nr_studenti - 1; i++) {
          if (check_condition_student(s->studenti[i], condition, operator,
                                      value)) {
            delete_student(s->studenti, i, s->nr_studenti);
            s->nr_studenti--;
            i--;
          }
        }
      } else if (strcmp(table, "materii") == 0) {
        int schimbatura = 0;
        for (int i = 0; i <= s->nr_materii - 1; i++)
          if (check_condition_materie(s->materii[i], condition, operator,
                                      value)) {
            delete_materie(s->materii, i, s->nr_materii);
            s->nr_materii--;
            i--;
            schimbatura++;
          }
        for (int i = s->nr_materii; i < s->nr_materii + schimbatura; i++) {
          free(s->materii[i].nume);
          free(s->materii[i].nume_titular);
        }
      } else {
        for (int i = 0; i <= s->nr_inrolari - 1; i++)
          if (check_condition_inrolare(s->inrolari[i], condition, operator,
                                       value)) {
            delete_inrolare(s->inrolari, i, s->nr_inrolari);
            s->nr_inrolari--;
            i--;
          }
        for (int j = 0; j < s->nr_studenti; j++) {
          float media = 0, k = 0;
          for (int i = 0; i < s->nr_inrolari; i++) {
            if (s->inrolari[i].id_student == s->studenti[j].id) {
              for (int d = 0; d < 3; d++) {
                media += s->inrolari[i].note[d];
              }
              k++;
            }
          }
          s->studenti[j].medie_generala = media / k;
          int media_aprox = (int)(s->studenti[j].medie_generala * precizie);
          if (media_aprox % aproximare > 4)
            s->studenti[j].medie_generala =
                (float)((media_aprox / aproximare) + 1) / sutica;
          else
            s->studenti[j].medie_generala =
                (float)(media_aprox / aproximare) / sutica;
        }
      }
    }
    number--;
    free(copy);
    free(table);
  }
  free(buffer);
  elibereaza_secretariat(&s);
  return 0;
}
