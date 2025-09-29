
┏━━━┓┏┓╋╋╋┏┓
┃┏━┓┣┛┗┓╋╋┃┃
┃┗━━╋┓┏╋━━┫┃┏━┓
┗━━┓┃┃┃┃┏┓┃┃┃┏┛
┃┗━┛┃┃┗┫┗┛┃┗┫┃
┗━━━┛┗━┻━━┻━┻┛

proiectul foloseste flask pentru a face un magazin online de scaune. in server.py sunt definite toate rutele principale si logica pentru cosul de cumparaturi, checkout si afisarea produselor.

exista doua baze de date. una se ocupa de scaune (sqlite simplu) si alta e pentru comenzile plasate (foloseste sqlalchemy si o tabela order). datele din cos se salveaza in sesiune iar comenzile se salveaza si ca json in fisiere si si in baza de date.

exista functie care incarca toate scaunele intre doua preturi. scaunele vin dintr-o tabela chairs. userul poate adauga in cos, scoate din cos sau modifica cantitatea. cosul e un dictionar care se salveaza in sesiune flask.

cand se face checkout, se verifica daca cosul e gol si daca nu, se colecteaza datele personale din formular, se calculeaza totalul si se salveaza comanda. dupa aia cosul se goleste si apare un mesaj de succes.

in plus exista o pagina pentru fiecare produs si o pagina de contact. toate template-urile primesc automat cosul ca variabila ca sa poata fi afisat usor numarul de produse.

layout.html
asta e baza site ului toate celelalte pagini se incarca in layout cu {{ content }} aici am pus un header simplu cu bara de navigatie si un badge cu cate produse ai in cos plus un footer jos
am inclus bootstrap si un fisier css personalizat numit styles.css

index.html
pagina principala unde se vad toate scaunele ca niste carduri fiecare cu poza titlu pret
mai am si un mic filtru

product.html
aici e pagina individuala a unui produs cand dai click pe un scaun vezi poza mare descrierea completa pretul si un formular ca sa il adaugi in cos
poti sa alegi si cantitatea si totul se bazeaza pe id ul din url

cart.html
pagina de cos aici se afiseaza toate produsele pe care le ai in cos cu poza titlu pret cantitate si butoane ca sa le stergi sau sa schimbi cantitatea
in josul paginii apare totalul final si un buton ca sa mergi la checkout

checkout.html
aici e formularul de comanda cu nume adresa email si metoda de plata
sub formular apare un mic rezumat al produselor din cos si cand dai submit se salveaza tot si mergi mai departe la confirmare

confirmation.html
pagina simpla care iti zice ca s a trimis comanda cu succes
eventual afisez si un numar de comanda si un mesaj de multumire

contact.html
pagina statica cu un formular de contact doar cu nume email si mesaj
nu trimit nimic real ci doar simulez trimiterea unui mesaj gen apare un mesaj ca a fost trimis

BONUSURI:

pagina individuala pentru produs – fiecare scaun are pagina lui /product/id
filtru dupa pret – pe homepage poti seta interval de pret
layout comun – cu header navbar si footer inclus
design scandinav – minimalist curat aerisit
meniul activ – linkuri vizibile si pagina curenta marcata
validare simpla - pentru formulare
persistenta - folosind baze de date
pe langa persistenta - le si salvez in json ( salvare comanda pe server – json in folder local )
update cantitate - in cos
mesaje tip "Your cart is empty" - buton pentru reintoarcere la site