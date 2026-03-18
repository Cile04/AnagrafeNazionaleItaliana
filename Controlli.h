#ifndef CONTROLLI_H
#define CONTROLLI_H

#include <stdbool.h>
#include "Dati.h" ///< Necessario per il tipo Cittadino

/**
 * @brief Verifica che il codice fiscale rispetti il formato corretto (16 caratteri alfanumerici).
 * 
 * @param codiceFiscale Stringa contenente il codice fiscale da verificare.
 * @return true se il formato è corretto, false altrimenti.
 */
bool verificaCodiceFiscale(const char *codiceFiscale);

/**
 * @brief Verifica che l'indirizzo rispetti il formato "Via Nome, Numero".
 * 
 * @param indirizzo Stringa contenente l'indirizzo da verificare.
 * @return true se il formato è corretto, false altrimenti.
 */
bool verificaFormatoIndirizzo(const char *indirizzo);

/**
 * @brief Permette di aggiornare CAP e provincia di un cittadino verificando la loro correttezza.
 * 
 * Se i dati non corrispondono, richiede di reinserirli finché non sono validi.
 * 
 * @param c Puntatore alla struttura Cittadino da aggiornare.
 */
void cambioCAPPROV(Cittadino *c);

/**
 * @brief Verifica la corrispondenza tra CAP e provincia e la validità del file dati.
 * 
 * @param cap Codice di avviamento postale.
 * @param provincia Sigla della provincia (es. "BA").
 * @return true se CAP e provincia sono validi e compatibili, false altrimenti.
 */
bool controllaCAPProvincia(const char *cap, const char *provincia);

/**
 * @brief Verifica che una data sia nel formato corretto (DD/MM/AAAA).
 * 
 * @param data Stringa contenente la data.
 * @return true se la data è valida, false altrimenti.
 */
bool verificaData(const char *data);

/**
 * @brief Gestisce il passaggio della residenza da estera a italiana per un cittadino.
 * 
 * Richiede l'inserimento obbligatorio di indirizzo, CAP e provincia.
 * 
 * @param c Puntatore alla struttura Cittadino da aggiornare.
 */
void controllaResidenzaEstera(Cittadino *c);

/**
 * @brief Gestisce i tentativi di login e blocca l’accesso dopo un numero massimo di tentativi.
 * 
 * @param tentativi Numero di tentativi effettuati.
 * @param max Numero massimo di tentativi consentiti.
 * @return Il numero di tentativi aggiornato o -1 se si è superato il limite.
 */
int verificaTentativi(int tentativi, int max);

/**
 * @brief Verifica che l’utente accetti le condizioni d’uso prima di continuare.
 * 
 * Mostra una dichiarazione sulla responsabilità e sull’utilizzo corretto dei dati.
 * 
 * @return 1 se l’utente accetta, 0 o programma chiuso altrimenti.
 */
int verifica_t_c();

#endif