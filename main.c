#include <stdio.h>
#include <stdlib.h>
#include "Dati.h"
#include "Funzioni.h"
#include "Input.h"
#include "Controlli.h"

#define FILE_DATI_CITT "cittadini.txt"

/**
 * @file main.c
 * @brief Punto di ingresso del programma anagrafe nazionale italiana.
 *
 * Questa funzione gestisce il flusso principale del programma:
 * - verifica prerequisiti (verifica_t_c)
 * - login operatore
 * - caricamento dati cittadini da file
 * - esecuzione del menu interattivo
 * - salvataggio dati su file
 * - rilascio memoria
 *
 * @return 0 se l'esecuzione termina con successo, 1 in caso di errore o login fallito.
 */

int main()
{

    if (!verifica_t_c())
    {
        return 1;
    }
    printf("\nBenvenuto/a al sistema dell'anagrafe nazionale Italiana\n\n");

    if (!loginOperatore())
    {
        return 1;
    }

    NodoCittadino *listaCittadini = NULL;

    // Carica dati dei cittadini già esisteni dal file
    caricaCittadini(FILE_DATI_CITT, &listaCittadini);

    // inizializza il menù principale
    menu(&listaCittadini, FILE_DATI_CITT);

    // Salva dati aggiornati su file
    salvaCittadiniSuFile(FILE_DATI_CITT, listaCittadini);

    // Libera memoria della lista
    liberaLista(listaCittadini);

    return 0;
}
