/* Bostangiu Luca-Nicolae - 311CB */

.___________. _______ .___  ___.      ___          __  
|           ||   ____||   \/   |     /   \        /_ | 
`---|  |----`|  |__   |  \  /  |    /  ^  \        | | 
    |  |     |   __|  |  |\/|  |   /  /_\  \       | | 
    |  |     |  |____ |  |  |  |  /  _____  \      | | 
    |__|     |_______||__|  |__| /__/     \__\     |_|


Scurta descriere pentru fiecare functie:
-implementarile pentru functii standard au fost luate de la cursuri/laburi

init()
    creeaza browserul initial
    initializeaza primul tab cu pagina principala
    seteaza santinela listei de tab-uri

new_tab()
    adauga un tab nou
    initializeaza cu pagina principala
    actualizeaza lista de tab-uri

close()
    inchide tab-ul curent
    sterge din lista
    elibereaza memoria
    seteaza noul tab curent

open()
    deschide un tab dupa id
    il face tab curent

next()
    trece la urmatorul tab
    sare peste santinela

prev()
    trece la tab-ul anterior
    sare peste santinela

page()
    incarca o pagina noua
    salveaza vechea pagina in istoric
    sterge forward stack
    aloca memorie pentru noua pagina

Pop()
    scoate o pagina din stiva
    returneaza pagina
    elibereaza nodul stivei

backward()
    navigheaza inapoi in istoric
    muta pagina curenta in forward stack

forward()
    navigheaza inainte in istoric
    muta pagina curenta in backward stack

Push()
    adauga o pagina in stiva
    aloca memorie pentru nod

print()
    afiseaza tab-urile deschise
    afiseaza descrierea paginii curente

print_history()
    afiseaza istoricul unui tab
    afiseaza url-urile in ordine

freebrowser()
    elibereaza toata memoria
    parcurge si elibereaza toate tab-urile
    elibereaza listele si stivele

main()
    citeste comenzile
    apeleaza functiile corespunzatoare
    elibereaza memoria la final

parsing()
    citeste paginile din fisier
    aloca memorie pentru ele
    returneaza vectorul de pagini