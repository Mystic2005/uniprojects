______________________   _____      _____    ________  
\__    ___/\_   _____/  /     \    /  _  \   \_____  \ 
  |    |    |    __)_  /  \ /  \  /  /_\  \   /  ____/ 
  |    |    |        \/    Y    \/    |    \ /       \ 
  |____|   /_______  /\____|__  /\____|__  / \_______ \
                   \/         \/         \/          \/


task 1:
am parcurs vectorul de intregi si pentru fiecare numar am verificat daca e impar (cu test eax, 1) si l-am sarit daca era.
apoi pentru numerele pare am verificat daca sunt puteri ale lui 2 prin shiftari succesive (shr ecx, 1) si verificat daca ramane 1.
daca nu era putere, am pus numarul in vectorul nou si am incrementat contorul de lungime. la final am salvat lungimea in adresa primita ca parametru.

task 2.1:
am parcurs vectorul de evenimente (fiecare avand 36 bytes), am extras ziua, luna si anul si am verificat fiecare camp daca e in intervalul corect. pentru zilele lunii am folosit un vector static zile in data.
daca toate verificarile treceau, puneam valid = 1, altfel valid = 0. am folosit movzx si cmp ca sa fac comparatiile pe tipuri diferite.

task 2.2:
am facut un bubble sort clasic pe vectorul de evenimente (din 36 in 36 bytes). am comparat mai intai flagul valid, apoi anul, luna, ziua si daca erau egale am trecut la strcmp pe nume.
pentru swap am folosit un loop care muta byte cu byte 36 de octeti intre cele 2 structuri.

task 3:
am facut codarea base64 pe grupuri de 3 bytes. am folosit shr si shl ca sa izolez grupurile de 6 biti si am mapat fiecare grup in alfabetul base64.
rezultatul l-am scris in vectorul de output si la final am calculat noua lungime (lungime * 4 / 3) si am scris-o in pointerul primit ca parametru.

task 4:
am implementat trei functii: check_row, check_column si check_box. in fiecare am folosit un vector de frecventa de 9 bytes ca sa verific daca cifrele 1-9 apar o singura data.
daca un numar era in afara intervalului 1-9 sau aparea de 2 ori, puneam eax = 2 (invalid), altfel eax = 1 (valid).
pentru box am calculat pozitia de start pe baza indexului (box/3 si box%3), si am folosit doua loopuri ca sa merg pe cele 9 pozitii.