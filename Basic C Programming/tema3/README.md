 .----------------.  .----------------.  .----------------.  .----------------.   .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. | | .--------------. |
| |  _________   | || |  _________   | || | ____    ____ | || |      __      | | | |    ______    | |
| | |  _   _  |  | || | |_   ___  |  | || ||_   \  /   _|| || |     /  \     | | | |   / ____ `.  | |
| | |_/ | | \_|  | || |   | |_  \_|  | || |  |   \/   |  | || |    / /\ \    | | | |   `'  __) |  | |
| |     | |      | || |   |  _|  _   | || |  | |\  /| |  | || |   / ____ \   | | | |   _  |__ '.  | |
| |    _| |_     | || |  _| |___/ |  | || | _| |_\/_| |_ | || | _/ /    \ \_ | | | |  | \____) |  | |
| |   |_____|    | || | |_________|  | || ||_____||_____|| || ||____|  |____|| | | |   \______.'  | |
| |              | || |              | || |              | || |              | | | |              | |
| '--------------' || '--------------' || '--------------' || '--------------' | | '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------'   '----------------' 

Task 1:
- se aloca secretariatul si se foloseste strtok pentru manipularea datelor, calculeaza media conform cerintei.
- adauga student..
- se dezaloca secretariatul si se atribuie NULL.

 Task 2:
 - se scot toate datele din ce se primeste: ex pt WHERE: se scoate intr un vector operatorul, intr-altul valoarea de comparat si in altul valoarea care trebuie luata din table.
- se proceseaza fiecare student,materie,inrolare individual astfel incat se verifica pentru fiecare conditia si dupa daca se respecta se da update,select whatever.

 Se folosesc urmatoarele functii pentru rezolvarea task-ului:

void print_student(student s, int *select_q, int select_length)
afiseaza campurile unui student conform criteriilor din array-ul select_q.

void print_materie(materie s, int *select_q, int select_length)
afiseaza campurile unei materii conform criteriilor din array-ul select_q.

void print_inrolare(inrolare s, int *select_q, int select_length)
afiseaza campurile unei inrolari conform criteriilor din array-ul select_q.

int check_studenti(char *p)
mapeaza un string (de exemplu, "id", "nume") la indexul corespunzator unui camp din student.

int check_materii(char *p)
mapeaza un string (de exemplu, "id", "nume") la indexul corespunzator unui camp din materie.

int check_inrolari(char *p)
mapeaza un string (de exemplu, "id_student", "note") la indexul corespunzator unui camp din inrolare.

int check_operator(char *p)
mapeaza un string operator (de exemplu, "=", "<") la un cod numeric corespunzator.

int check_condition_student(student s, int condition[2], int operator[2], float value[2])
verifica daca un student respecta conditiile date prin operatori si valori specifice.

int check_condition_materie(materie s, int condition[2], int operator[2], float value[2])
verifica daca o materie respecta conditiile date prin operatori si valori specifice.

int check_condition_inrolare(inrolare s, int condition[2], int operator[2], float value[2])
verifica daca o inrolare respecta conditiile date prin operatori si valori specifice.

void update_student(student *s, int select_q, float val, char *nume_val)
actualizeaza un camp specific al unui student conform query-ului select_q.

void update_materie(materie *s, int select_q, char *nume_val)
actualizeaza un camp specific al unei materii conform query-ului select_q.

void update_inrolare(inrolare *s, int select_q, float val, float vect[3])
actualizeaza campuri ale unei inrolari, inclusiv note, conform query-ului select_q.

void delete_student(student *s, int start, int end)
sterge o gama de studenti din lista prin mutarea elementelor ramase.

void delete_materie(materie *s, int start, int end)
sterge o gama de materii din lista prin mutarea elementelor ramase.

void delete_inrolare(inrolare *s, int start, int end)
sterge o gama de inrolari din lista prin mutarea elementelor ramase.

Task3:

functia split_into_blocks_and_pad(secretariat *s, int *p):
imparte datele studentilor in blocuri si adauga padding pentru aliniere
returneaza un tablou de blocuri alocate dinamic
actualizeaza valoarea lui p[0] cu dimensiunea blocurilor

functia XOR(char *blocks, char *IV, int len):
aplica operatia XOR intre un bloc de date si un vector de initializare (IV) / sau pentru block 2,3,4 se foloseste block ul anterior
returneaza un bloc criptat rezultat si alocat dinamic

functia S_BOX(char *blocks_enc, char *IV, int len):
aplica transformari aditionale pe blocul criptat utilizand key

functia P_BOX(char *block_enc, int len):
permutari asupra unui bloc criptat