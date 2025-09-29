task 1: Markov is coming

parse_labyrinth: citeste un fisier care descrie labirintul si il transforma intr-o matrice. fiecare numar reprezinta zidurile existente in jurul unei celule.

get_adjacency_matrix: creeaza o matrice care arata unde se poate muta robotul. valoarea 1 inseamna ca exista o miscare valida intre doua celule (fara zid intre ele).

get_link_matrix: similar cu matricea de adiacenta, dar calculeaza si probabilitatile de miscare (ex: daca o celula are 2 miscari valide, fiecare are probabilitate 1/2).

get_jacobi_parameters: extrage matricea g si vectorul c din matricea legaturilor, necesare pentru rezolvarea sistemului de ecuatii.

perform_iterative: rezolva sistemul de ecuatii folosind metoda jacobi, verificand daca solutia converge.

heuristic_greedy: gaseste o cale in labirint alegand mereu celula vecina cu cea mai mare probabilitate de castig.

decode_path: transforma o lista de indecsi (ex: 5, 8, 11) in perechi de coordonate (linie, coloana) pe harta labirintului.

task 2: linear regression

parse_data_set_file: citeste date dintr-un fisier si le stocheaza intr-o matrice. prima coloana contine rezultatele reale (y), iar restul sunt caracteristici (ex: suprafata, camere).

prepare_for_regression: converteste datele text (ex: "da"/"nu") in valori numerice (1/0). pentru optiuni complexe (ex: "mobilat"), creeaza coloane separate.

linear_regression_cost_function: calculeaza eroarea dintre predictii si valorile reale folosind suma patratelor diferentelor.

gradient_descent: ajusteaza coeficientii theta pas cu pas, reducand eroarea prin actualizari repetitive.

normal_equation: calculeaza coeficientii theta optimi rezolvand o ecuatie matriceala, fara a inversa matricele direct.

lasso_regression_cost_function: adauga o penalizare bazata pe suma valorilor absolute ale coeficientilor theta pentru a evita modelul prea complex.

ridge_regression_cost_function: adauga o penalizare bazata pe patratul coeficientilor theta pentru a imbunatati stabilitatea modelului.

task 3: mnist 101

load_dataset: incarca imaginile de cifre scrise de mana si etichetele lor asociate dintr-un fisier mat.

split_dataset: amesteca datele si le imparte in seturi de antrenare si test (ex: 80% pentru antrenare, 20% pentru testare).

initialize_weights: genereaza valori initiale aleatoare pentru ponderile retelei neurale, evitand simetriile care ar strica invatarea.

cost_function: calculeaza cat de gresite sunt predictiile retelei folosind cross-entropy. calculeaza si gradientii pentru fiecare parametru folosind backpropagation.

predict_classes: foloseste reteaua antrenata pentru a prezice cifra din imagine. alege clasa cu cea mai mare probabilitate calculata de model.



observatii

toate matricele mari (ex: adiacenta) sunt stocate in format rar pentru a economisi memorie.

functiile de cost includ reguli de regularizare pentru a preveni overfitting-ul.

majoritatea calculelor sunt vectorizate pentru viteza, evitand buclele explicite.