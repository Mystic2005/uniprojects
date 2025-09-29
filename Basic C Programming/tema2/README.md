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


Functiile folosite:

chunk_place_block: adauga un bloc la coordonatele specificate in chunk, daca sunt valide.

chunk_fill_cuboid: umple un paralelipiped dreptunghic cu un bloc, asigurandu-se ca coordonatele sunt in limitele chunk-ului.

chunk_fill_sphere: umple o zona sferica cu un bloc, respectand raza si asigurandu-se ca coordonatele sunt in limitele chunk-ului.

bfs: Cauta in latime 2D si umple blocuri adiacente cu un bloc specific.

bfs3d: Cauta in latime 3D pe chunk si umple blocuri conexe.

chunk_shell: Creeaza o coaja de blocuri in jurul blocurilor tinta din chunk.

chunk_fill_xz: Umple zona XZ 2D a chunk-ului cu blocuri folosind BFS.

chunk_fill: Umple un chunk 3D cu blocuri conectate folosind BFS.

chunk_rotate_y: roteste chunk-ul pe axa Y, schimband dimensiunile.

corp_apply_gravity: aplica gravitatea unui bloc, mutandu-l jos in chunk.

merge_apply_gravity: aplica gravitatea unui bloc si altora adiacente, actualizand pozitia.

chunk_apply_gravity: aplica gravitatea pe toata structura chunk, eliminand aerul sus.

chunk_encode: comprima un chunk 3d intr-un vector de bytes folosind encoding prin run-length.

chunk_decode: decodeaza un vector de bytes pentru a reconstrui un chunk 3d original din datele comprimate.