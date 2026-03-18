#include <stdlib.h>
#include <string.h>
#include "Dati.h"

/**
 * @brief Array contenente l'elenco dei CAP e relative province.
 */
CAPProvincia ElencoCAP[CARICA_CAP_MAX];

/**
 * @brief Numero totale di CAP caricati nel sistema.
 */
int totaleCAP = 0;

// Crea un nuovo nodo con i dati di un nuovo cittadino//

/**
 * @brief Crea un nuovo nodo cittadino.
 * 
 * @param c Struttura Cittadino da inserire nel nodo.
 * @return Puntatore al nodo creato, o NULL in caso di errore.
 */
NodoCittadino *creaNodo(Cittadino c) {
    NodoCittadino *nuovo = malloc(sizeof(NodoCittadino));
    if (nuovo != NULL) {
        nuovo->dati = c;
        nuovo->prossimo = NULL;
    }
    return nuovo;
}

// Inserisce un Citadino in testa alla lista//

/**
 * @brief Inserisce un cittadino in testa alla lista collegata.
 * 
 * @param lista Puntatore alla testa della lista esistente.
 * @param c Dati del cittadino da inserire.
 * @return Puntatore alla nuova testa della lista.
 */
NodoCittadino *inserisciinTesta(NodoCittadino *lista, Cittadino c) {
    NodoCittadino *nuovo = creaNodo(c);
    if (nuovo != NULL) {
        nuovo->prossimo = lista;
    }
    return nuovo;
}

// Libera tutta la lista, come buona pratica soltanto, spiegato meglio in dati.h//

/**
 * @brief Libera tutta la memoria occupata dalla lista dei cittadini.
 * 
 * @param lista Puntatore alla testa della lista da liberare.
 */
void liberaLista(NodoCittadino *lista) {
    NodoCittadino *corrente;
    while (lista != NULL) {
        corrente = lista;
        lista = lista->prossimo;
        free(corrente);
    }
}