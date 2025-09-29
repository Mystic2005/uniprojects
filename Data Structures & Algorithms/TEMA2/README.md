/* Bostangiu Luca-Nicolae - 311CB */
 .----------------.  .----------------.  .----------------.  .----------------.   .----------------. 
| .--------------. || .--------------. || .--------------. || .--------------. | | .--------------. |
| |  _________   | || |  _________   | || | ____    ____ | || |      __      | | | |    _____     | |
| | |  _   _  |  | || | |_   ___  |  | || ||_   \  /   _|| || |     /  \     | | | |   / ___ `.   | |
| | |_/ | | \_|  | || |   | |_  \_|  | || |  |   \/   |  | || |    / /\ \    | | | |  |_/___| |   | |
| |     | |      | || |   |  _|  _   | || |  | |\  /| |  | || |   / ____ \   | | | |   .'____.'   | |
| |    _| |_     | || |  _| |___/ |  | || | _| |_\/_| |_ | || | _/ /    \ \_ | | | |  / /____     | |
| |   |_____|    | || | |_________|  | || ||_____||_____|| || ||____|  |____|| | | |  |_______|   | |
| |              | || |              | || |              | || |              | | | |              | |
| '--------------' || '--------------' || '--------------' || '--------------' | | '--------------' |
 '----------------'  '----------------'  '----------------'  '----------------'   '----------------' 


main
deschid fisierele de intrare si iesire si, folosind functia parse, citesc datele si construiesc heap ul. din heap ul asta, functia arbore imi construieste arborele.

parse
functia asta citeste din fisier si imi construieste un min heap. prima linie din fisier imi zice cate elemente (sateliti) o sa fie. apoi, pentru fiecare satelit, ii citesc frecventa si numele, dupa care il adaug in heap. ideea e ca heap ul asta tine elementele ordonate dupa frecventa, ca sa pot extrage mereu satelitul cu frecventa cea mai mica.

exercitiul 1 afisare arbore: daca e exercitiul 1, pur si simplu afisez structura arborelui.

exercitiul 2 decodificare: pentru exercitiul 2, citesc mai multe coduri si pentru fiecare, folosesc arborele ca sa le decodific inapoi in nume de sateliti.

exercitiul 3 codificare: la exercitiul 3, fac invers: citesc nume de sateliti si ii codific folosind arborele. toate codurile astea le lipesc intr un sir mare, pe care il scriu la final in fisier.

exercitiul 4 cel mai lung prefix comun. citesc mai multe nume de sateliti, le codific, apoi gasesc cel mai lung prefix comun al codurilor. asta imi zice practic cel mai "apropiat" nod parinte din arbore care este comun pentru toti satelitii respectivi. daca nu gasesc un prefix comun mai lung decat radacina, afisez numele radacinii.
la final, eliberez toata memoria alocata pentru arbore si pentru heap.

alocaheap, distrugeheap, relminheap sunt adaptate de la lab6.

inserareheap
functia asta adauga un satelit nou in heap. il pune la final si apoi il "urca" prin heap, schimbandu l cu parintii lui, pana cand ajunge la pozitia corecta, respectand proprietatea de min heap.

extragereheap
imi scoate elementul cu frecventa cea mai mica din heap (adica radacina). dupa ce il scoate, muta ultimul element in locul radacinii si apoi il "coboara", schimbandu l cu copiii lui, pana cand heap ul e din nou ordonat corect.

arbore
asta e functia care construieste arborele. cat timp in heap mai sunt mai mult de un element, extrag cei doi sateliti cu frecventa cea mai mica, ii combin intr un nod nou (cu frecventa egala cu suma frecventelor lor si numele concatenat) si apoi inserez nodul nou inapoi in heap. la final, ramane un singur nod in heap, care e radacina.

inaltimearbore
imi calculeaza inaltimea arborelui. practic, verifica pe fiecare ramura cat de lunga e si returneaza cea mai lunga.

printnivel
functia asta e ajutatoare pentru printarbore. imi printeaza toti satelitii de la un anumit nivel din arbore.

printarbore
afiseaza intregul arbore, nivel cu nivel.

decodificare
pentru un cod dat, functia asta il parcurge bit cu bit si, folosind arborele, imi zice ce nume de satelit reprezinta codul respectiv.

codificare
pentru un nume de satelit, functia asta cauta satelitul in arbore si imi construieste codul lui.

freearbore
se cam intelege ce face asta.