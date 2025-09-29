        ,----,                                                                
      ,/   .`|                   ____                           .--,-``-.     
    ,`   .'  :   ,---,.        ,'  , `.   ,---,                /   /     '.   
  ;    ;     / ,'  .' |     ,-+-,.' _ |  '  .' \              / ../        ;  
.'___,/    ,',---.'   |  ,-+-. ;   , || /  ;    '.            \ ``\  .`-    ' 
|    :     | |   |   .' ,--.'|'   |  ;|:  :       \            \___\/   \   : 
;    |.';  ; :   :  |-,|   |  ,', |  '::  |   /\   \                \   :   | 
`----'  |  | :   |  ;/||   | /  | |  |||  :  ' ;.   :               /  /   /  
    '   :  ; |   :   .''   | :  | :  |,|  |  ;/  \   \              \  \   \  
    |   |  ' |   |  |-,;   . |  ; |--' '  :  | \  \ ,'          ___ /   :   | 
    '   :  | '   :  ;/||   : |  | ,    |  |  '  '--'           /   /\   /   : 
    ;   |.'  |   |    \|   : '  |/     |  :  :                / ,,/  ',-    . 
    '---'    |   :   .';   | |`-'      |  | ,'                \ ''\        ;  
             |   | ,'  |   ;/          `--''                   \   \     .'   
             `----'    '---'                                    `--`-,,-'     
                                                                              



task 1

    functia sort primeste un vector de noduri si il leaga intr o lista simplu inlantuita in ordine crescatoare dupa valoarea fiecarui nod.
        creeaza un vector temporar pe stiva unde pune adresele nodurilor
        foloseste valorile ca indesci pentru a pune adresele in ordine
        apoi leaga fiecare nod la urmatorul
        la final seteaza next la ultimul nod ca fiind null si returneaza adresa primului nod


task 2

get_words
    extrage cuvintele dintr un string si le pune intr un vector de pointeri la cuvinte
        sare peste delimitatori ca spatii virgule puncte newline
        marcheaza sfarsitul fiecarui cuvant cu caracterul null 0
        salveaza adresa inceputului fiecarui cuvant in vector

    comentarii - detectare delimitatori si cum se parcurge stringul caracter cu caracter

sort
    sorteaza vectorul de cuvinte cu qsort folosind o functie de comparare personalizata
        sorteaza mai intai dupa lungimea cuvintelor
        daca au aceeasi lungime, le compara lexicografic

compare
    functie de comparare pentru qsort
        foloseste strlen ca sa compare lungimile cuvintelor
        daca sunt egale, foloseste strcmp pentru sortare alfabetica
        intoarce 1, -1 sau 0 in functie de rezultat



task 3

kfib
    calculeaza o varianta generalizata de fibonacci unde fiecare element este suma precedentelor k elemente
        daca n < k returneaza 0
        daca n = k returneaza 1
        altfel face apeluri recursive pentru n-1 pana la n-k si le aduna

    se bazeaza pe o bucla care face apeluri recursive si aduna rezultatele pentru a obtine valoarea curenta.



task 4

check_palindrome
    verifica daca un string este palindrom
        compara caracterele de la inceput si sfarsit pana se intalnesc
        daca toate sunt egale, returneaza 1
        altfel, returneaza 0

composite_palindrome
    gaseste cel mai lung palindrom care poate fi format prin concatenarea unui subsir de cuvinte
        genereaza toate combinatiile posibile de cuvinte folosind o masca binara
        concateneaza cuvintele selectate si verifica daca e palindrom
        pastreaza varianta cea mai lunga si cea mai mare lexicografic
        foloseste malloc, strcat, strcpy, free si check_palindrome
        
    am scris comentarii care descriu cum se parcurg combinatiile si cum se salveaza rezultatul optim