#include <stdio.h>
#include <stdlib.h>

// ------------------------ Util p/u eliberarea memorie ------------------------ //
void eli_mem(int** array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

void afisare_rezultate(int nod, int muchie, int** matrice_incidenta, int** matrice_adiacenta, int** lista_adiacenta) {
    // Afisare matrice de adiacenta
    printf("Matrice de incidenta:\n");
    for (int i=0; i<muchie; i++) {
        printf("u%d: ", i+1);
        for (int j=0; j<nod; j++) {
            printf("%d ", matrice_incidenta[i][j]);
        }
        printf("\n");
    }

    // Afisare matrice de adiacenta
    printf("Matrice de adiacenta: \n");
    for (int i=0; i<nod; i++) {
        printf("x%d: ", i+1);
        for (int j=0; j<nod; j++) {
            printf("%d ", matrice_adiacenta[i][j]);
        }
        printf("\n");
    }

    printf("\nLista de adiacenta:\n");
    for (int i = 0; i < nod; i++) {
        printf("x%d: ", i + 1);
        int j = 0;
        while (lista_adiacenta[i][j] != 0) {
            printf("%d ", lista_adiacenta[i][j]);
            j++;
        }
        printf("0\n");
    }
}

// ------------------------- Functii de citire ------------------------ //
int** citire_incidenta(int nod, int muchie)   {
    int** matrice_incidenta = (int**)malloc(muchie * sizeof(int*));
    for (int i = 0; i < muchie; i++) {
        matrice_incidenta[i] = (int*)malloc(nod * sizeof(int));
        for (int j = 0; j < nod; j++) {
            matrice_incidenta[i][j] = 0;
        }
    }

    for (int i = 0; i < muchie; i++) {
        printf("Introduceti muchia %d: ", i + 1);
        int areUnu = 0, areMinusUnu = 0, areDoi = 0;
        for (int j = 0; j < nod; j++) {
            scanf("%d", &matrice_incidenta[i][j]);
            if (matrice_incidenta[i][j] == 1) areUnu = 1; /* 1 pentru nodul de sosire.*/
            if (matrice_incidenta[i][j] == -1) areMinusUnu = 1; /*-1 pentru nodul de plecare. */
            if (matrice_incidenta[i][j] == 2) areDoi = 1;/*2 dacă muchia este o buclă. */
        }
        if (!((areUnu && areMinusUnu) || areDoi)) {
            printf("Eroare: fiecare rand trebuie sa aiba fie 1 si -1, fie 2, iar restul sa fie 0.\n");
            i--; // Reîntoarcem la citirea aceleași muchii dacă sunt erori
        }
    }

    return matrice_incidenta;
}

int** citire_adiacenta(int nod)  /* Citește o matrice de incidență de la utilizator
și verifică dacă fiecare muchie are fie un (1, -1) 1, există o muchie între nodul
i și nodul j. */{
    int** matrice_adiacenta = (int**)malloc(nod *  sizeof(int*));
    for (int i = 0; i < nod; i++) {
        matrice_adiacenta[i] = (int*)malloc(nod * sizeof(int));
        for (int j = 0; j < nod; j++) {
            matrice_adiacenta[i][j] = 0; //initializam cu 0, fara  muchie intre noduri. //
        }
    }

    for (int i=0; i<nod; i++) {
        printf("Introduceti nod %d: ", i+1);
        for (int j=0; j<nod; j++) {
            scanf("%d", &matrice_adiacenta[i][j]);
        }
    }

    return matrice_adiacenta;
}

int** citire_lista(int nod) {
    int** lista_adiacenta = (int**)malloc(nod *  sizeof(int*));
    // Alocăm memorie pentru fiecare listă de adiacență a fiecărui nod
    for (int i = 0; i < nod; i++) {
        lista_adiacenta[i] = (int*)malloc(nod * sizeof(int));
    }

    for (int i = 0; i < nod; i++) {
        printf("x%d: ", i + 1); // Afișăm nodul curent pentru care se va citi lista de adiacență
        int j = 0;
        while (j < nod) {
            // Citim un element pentru lista de adiacență a nodului i
            scanf("%d", &lista_adiacenta[i][j]);
            // Dacă întâlnim valoarea 0, înseamnă că nu mai există alte noduri adiacente, deci terminăm citirea pentru acest nod
            if (lista_adiacenta[i][j] == 0) break;
            j++;  // Mergem la următorul element din lista de adiacență
        }
    }

    return lista_adiacenta;
}

/*                     Functii pentru transformare                  */
int** inc_to_adi(int** matrice_incidenta, int nod, int muchie) {
    int** matrice_adiacenta = (int**)malloc(nod * sizeof(int*));
    for (int i = 0; i < nod; i++) {
        matrice_adiacenta[i] = (int*)malloc(nod * sizeof(int));
        for (int j = 0; j < nod; j++) {
            matrice_adiacenta[i][j] = 0;
        }
    }

    int coordX = -2;
    int coordY = -2;

    for (int i=0; i<muchie; i++) {
        for (int j=0; j<nod; j++) {
            if (matrice_incidenta[i][j] == -1) { // -1 (nod sursă)
                coordX = j;
            }
            if (matrice_incidenta[i][j] == 1) { //1 (nod destinație)2
                coordY = j;
            }

            if (matrice_incidenta[i][j] == 2) { //2 (buclă)
                matrice_adiacenta[j][j] = 1;
                continue;
            }

            if (coordX != -2 && coordY != -2) {
                matrice_adiacenta[coordX][coordY] = 1;
            }
        }
        coordX = -2;
        coordY = -2;
    }

    return matrice_adiacenta;
}

int** inc_to_list(int** matrice_incidenta, int nod, int muchie) {
    int **lista_adiacenta = (int**)malloc(nod * sizeof(int*));
    for (int i = 0; i < nod; i++) {
        lista_adiacenta[i] = (int*)malloc(nod * sizeof(int));
        for (int j = 0; j < nod; j++) {
            lista_adiacenta[i][j] = 0;
        }
    }

    int coordX = -2;
    int coordY = -2;

    for (int i = 0; i < muchie; i++) {
        for (int j = 0; j < nod; j++) {
            if (matrice_incidenta[i][j] == -1) {
                coordX = j;
            }
            if (matrice_incidenta[i][j] == 1) {
                coordY = j;
            }

            if (matrice_incidenta[i][j] == 2) {
                lista_adiacenta[j][0] = j + 1;
                continue;
            }

            if (coordX != -2 && coordY != -2) {
                int k = 0;
                while (lista_adiacenta[coordX][k] != 0) {
                    k++;
                }
                lista_adiacenta[coordX][k] = coordY + 1;
                coordX = -2;
                coordY = -2;
            }
        }
    }

    return lista_adiacenta;
}

int** adi_to_inc(int** matrice_adiacenta, int nod, int muchie)/* Funcție care transformă o matrice de adiacență în matrice de incidență.
   Alocă memorie pentru matricea de incidență (muchie linii × nod coloane). */ {
    int** matrice_incidenta = (int**)malloc(muchie * sizeof(int*));
    for (int i = 0; i < muchie; i++) {
        matrice_incidenta[i] = (int*)malloc(nod * sizeof(int));
        for (int j = 0; j < nod; j++) {
            matrice_incidenta[i][j] = 0; //initializam cu 0
        }
    }

    int coordX = -1;
    int coordY = -1;

    int muchii = -1;  /* Contor pentru numărarea muchiilor */
    //Parcurgem matricea de adicenta
    for (int i=0; i<nod; i++) {
        for (int j=0; j<nod; j++) {
            if (matrice_adiacenta[i][j] == 1) {
                muchii++;// citim indexul muchiei
                if (i==j) /* Dacă e o buclă */ {
                    matrice_incidenta[muchii][j] = 2;
                } else /* Dacă este o muchie normală între două noduri */
                    {
                    matrice_incidenta[muchii][i] = -1;
                    matrice_incidenta[muchii][j] = 1;
                }
            }
        }
    }
//După ce toate muchiile sunt procesate, funcția returnează matricea de incidență.
    return matrice_incidenta;
}

int** list_to_adi(int** lista_adiacenta, int nod, int muchie) {
    int** matrice_adiacenta = (int**)malloc(nod * sizeof(int*));
    for (int i = 0; i < nod; i++) {
        matrice_adiacenta[i] = (int*)malloc(nod * sizeof(int));
         // Convertim lista de adiacență într-o matrice de adiacență.
        // Pentru fiecare nod, adăugăm conexiunile sale în matrice.

        for (int j = 0; j < nod; j++) {
            matrice_adiacenta[i][j] = 0;
        }
    }

    for (int i=0; i<nod; i++) {
        int j = 0;
        while (lista_adiacenta[i][j] != 0) {
            matrice_adiacenta[i][lista_adiacenta[i][j]-1] = 1;
            j++;
        }
    }

    return matrice_adiacenta;
}

// ------------------------ Functii principale pentru fiecare conversie------------------------ //
void inc_to_result() {
    int nod, muchie;
    printf("Introduceti numarul de noduri: ");
    scanf("%d", &nod);
    printf("Introduceti numarul de muchii: ");
    scanf("%d", &muchie);

    int **matrice_incidenta = citire_incidenta(nod, muchie);

    int **matrice_adiacenta = inc_to_adi(matrice_incidenta, nod, muchie);

    int **lista_adiacenta = inc_to_list(matrice_incidenta, nod, muchie);

    system("clear");

    afisare_rezultate(nod, muchie, matrice_incidenta, matrice_adiacenta, lista_adiacenta);

    eli_mem(matrice_incidenta, muchie);
    eli_mem(matrice_adiacenta, nod);
    eli_mem(lista_adiacenta, muchie);
}

void adi_to_result() {
    int nod;
    printf("Introduceti numarul de noduri: ");
    scanf("%d", &nod);

    int **matrice_adiacenta = citire_adiacenta(nod);

    int muchie = 0;
    for (int i=0; i<nod; i++) {
        for (int j=0; j<nod; j++) {
            if (matrice_adiacenta[i][j] == 1) {
                muchie++;
            }
        }
    }

    int **matrice_incidenta = adi_to_inc(matrice_adiacenta, nod, muchie);

    int **lista_adiacenta = inc_to_list(matrice_incidenta, nod, muchie);

    system("clear");

    afisare_rezultate(nod, muchie, matrice_incidenta, matrice_adiacenta, lista_adiacenta); /*Afișează matricea de
    incidență, matricea de adiacență și lista de adiacență.*/

    eli_mem(matrice_incidenta, muchie);
    eli_mem(matrice_adiacenta, nod);
    eli_mem(lista_adiacenta, muchie);
}

void list_to_result() {
    int nod;
    printf("Introduceti numarul de noduri: ");
    scanf("%d", &nod);

    int **lista_adiacenta = citire_lista(nod);

    int muchie = 0;
    for (int i = 0; i < nod; i++) {
        int j = 0;
        while (lista_adiacenta[i][j] != 0) {
            muchie++;
            j++;
        }
    }

    int **matrice_adiacenta = list_to_adi(lista_adiacenta, nod, muchie);

    int **matrice_incidenta = adi_to_inc(matrice_adiacenta, nod, muchie);

    system("clear");

    afisare_rezultate(nod, muchie, matrice_incidenta, matrice_adiacenta, lista_adiacenta);

    eli_mem(matrice_incidenta, muchie);
    eli_mem(matrice_adiacenta, nod);
    eli_mem(lista_adiacenta, muchie);
}

int main() { /* Cere utilizatorului să introducă tipul de matrice inițială (1, 2 sau 3).
Apelează funcția corespunzătoare pentru conversie*/

    // Introdu modul : incidenta, adiacenta, lista)citire (si
    int tip_matrice = 0;
    printf("Introduceti tipul de matrice (1: --> incidenta, 2: --> adiacenta, 3: --> lista): ");
    scanf("%d", &tip_matrice);

    switch (tip_matrice) {
        case 1:
            inc_to_result();/* Citește o matrice de incidență, o transformă și afișează rezultatele. */
            break;
        case 2:
            adi_to_result();/* Citește o matrice de adiacență, o transformă și afișează rezultatele.*/
            break;
        case 3:
            list_to_result(); /* Citește o listă de adiacență, o transformă și afișează rezultatele.*/
            break;
        default: printf("Eroare: acest tip de matrice nu exista.\n");
    }

    return 0;
}
