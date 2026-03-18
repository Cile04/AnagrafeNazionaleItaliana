#ifndef DATI_H
#define DATI_H

#include <stdbool.h>

/**
 * @def MAX_CITTADINI
 * Numero massimo di cittadini gestibili.
 */
#define MAX_CITTADINI 120      // Per sicurezza, mettiamo un po' di più, per evitare errori critici//

/**
 * @def LUNG_MAX_NOME
 * Lunghezza massima per nome o cognome.
 */
#define LUNG_MAX_NOME 60       // Per sicurezza, mettiamo un po' di più, per evitare errori critici//

/**
 * @def LUNG_MAX_CITT
 * Lunghezza massima per il campo cittadinanza.
 */
#define LUNG_MAX_CITT 40       // Per sicurezza, mettiamo un po' di più, per evitare errori critici//

/**
 * @def LUNG_MAX_INDIRIZZO
 * Lunghezza massima per l'indirizzo.
 */
#define LUNG_MAX_INDIRIZZO 100 // Per sicurezza, mettiamo di più, per evitare errori critici//

/**
 * @def LUNG_MAX_CF
 * Lunghezza massima del codice fiscale.
 */
#define LUNG_MAX_CF 17         // 16 + \n//

/**
 * @def MAX_USERNAME
 * Lunghezza massima per lo username dell'operatore.
 */
#define MAX_USERNAME 50        // Per sicurezza, mettiamo un po' di più, per evitare errori critici//

/**
 * @def MAX_PASSWORD
 * Lunghezza massima per la password dell'operatore.
 */
#define MAX_PASSWORD 30        // Per sicurezza, mettiamo un po' di più, per evitare errori critici//

/**
 * @def CARICA_CAP_MAX
 * Numero massimo di record CAP-provincia caricabili.
 */
#define CARICA_CAP_MAX 8458    // Quantità quasi esatta, con un piccolo margine, si può verificare in .txt di Cap_prov//

/**
 * @def CAP_MAX
 * Lunghezza massima per il codice postale (CAP).
 */
#define CAP_MAX 6              // Codice + \n//

/**
 * @def PROV_MAX
 * Lunghezza massima per la provincia.
 */
#define PROV_MAX 3             // Codice + \n//

/**
 * @struct CAPProvincia
 * @brief Associa un codice postale a una provincia.
 */
typedef struct
{
    char codicePostale[CAP_MAX];  /**< Codice postale */
    char provincia[PROV_MAX];     /**< Sigla provincia */
} CAPProvincia;

/**
 * @brief Elenco dei CAP e province caricati.
 */
extern CAPProvincia ElencoCAP[CARICA_CAP_MAX];

/**
 * @brief Numero totale di CAP caricati.
 * 
 * Utilizzato per evitare ricaricamenti ripetuti.
 */
extern int totaleCAP; // In modo di poter utilizzare questo anche oltre, ci servirà per la ricerca di CAP e provincia, in modo da non doverlo ricaricare ogni volta che si usa la funzione//

/**
 * @struct Data
 * @brief Rappresenta una data nel formato giorno/mese/anno.
 */
typedef struct
{
    int giorno;  /**< Giorno */
    int mese;    /**< Mese */
    int anno;    /**< Anno */
} Data;

/**
 * @struct Cittadino
 * @brief Rappresenta i dati di un cittadino.
 */
typedef struct
{
    char nome[LUNG_MAX_NOME];    /**< MAX 2 nomi */
    char cognome[LUNG_MAX_NOME]; /**< MAX 2 cognomi */
    Data data_nascita;           /**< Data di nascita nel formato gg/mm/aaaa */
    char codiceFiscale[LUNG_MAX_CF];  /**< Codice fiscale */
    char cittadinanza[LUNG_MAX_CITT]; /**< Cittadinanza */
    char indirizzo[LUNG_MAX_INDIRIZZO]; /**< Indirizzo, es. Via Gino Strada, 5 */
    char codicePostale[CAP_MAX];       /**< Codice postale, es. 70126 */
    char provincia[PROV_MAX];          /**< Provincia, es. BA */
    char estero;                       /**< 'S' per estero, 'N' per Italia */
} Cittadino;

/**
 * @struct Operatore
 * @brief Dati dell'operatore per il login e il benvenuto.
 */
typedef struct
{
    char nome[LUNG_MAX_NOME];       /**< Nome dell'operatore */
    char cognome[LUNG_MAX_NOME];    /**< Cognome dell'operatore */
    char username[MAX_USERNAME];    /**< Username */
    char password[MAX_PASSWORD];    /**< Password */
} Operatore;

/**
 * @struct nodoCittadino
 * @brief Nodo della lista concatenata dei cittadini.
 */
typedef struct nodoCittadino
{
    Cittadino dati;                   /**< Dati del cittadino */
    struct nodoCittadino *prossimo;  /**< Puntatore al nodo successivo */
} NodoCittadino;

/**
 * @brief Crea un nuovo nodo cittadino.
 * 
 * @param c Dati del cittadino da inserire nel nodo.
 * @return Puntatore al nuovo nodo creato.
 */
NodoCittadino *creaNodo(Cittadino c); // PER CREARE UN NUOVO CITTADINO//

/**
 * @brief Inserisce un cittadino in testa alla lista.
 * 
 * @param lista Puntatore alla lista esistente.
 * @param c Dati del nuovo cittadino.
 * @return Puntatore alla nuova testa della lista.
 */
NodoCittadino *inserisciinTesta(NodoCittadino *lista, Cittadino c); // PER INSERIRE UN NUOVO CITTADINO IN TESTA//

/**
 * @brief Libera la memoria occupata dalla lista.
 * 
 * @param lista Puntatore alla lista da liberare.
 */
void liberaLista(NodoCittadino *lista); // PER LIBERARE LA MEMORIA DELLA LISTA COME BUONA PRATICA, IN PROGETTI COME QUESTO NON FANNO LA DIFFERENZA MA IN PROGETTI PIù GRANDI SI, SPCIALMENTE SU SIAMO UN SERVER ATTIVO PER TANTE ORE//

#endif