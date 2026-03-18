#ifndef INPUT_H
#define INPUT_H

#include "Dati.h" ///< Include per la definizione della struct Cittadino e relative dimensioni

/**
 * @brief Pulisce il buffer di input standard.
 */
void clearInputBuffer(void);

/**
 * @brief Acquisisce il nome o i nomi di una persona.
 * 
 * @param nome Array di caratteri in cui verrà memorizzato il nome.
 */
void inputNomi(char nome[LUNG_MAX_NOME]);

/**
 * @brief Acquisisce il cognome o i cognomi di una persona.
 * 
 * @param cognome Array di caratteri in cui verrà memorizzato il cognome.
 */
void inputCognomi(char cognome[LUNG_MAX_NOME]);

/**
 * @brief Acquisisce la data di nascita nel formato DD/MM/AAAA.
 * 
 * @param dataNascita Puntatore al buffer dove verrà memorizzata la data.
 * @param dim Dimensione del buffer.
 */
void inputDataNascita(char *dataNascita, int dim);

/**
 * @brief Acquisisce il codice fiscale (16 caratteri).
 * 
 * @param codiceFiscale Puntatore al buffer dove verrà memorizzato il codice fiscale.
 * @param dim Dimensione del buffer.
 */
void inputCodiceFiscale(char *codiceFiscale, int dim);

/**
 * @brief Acquisisce la cittadinanza.
 * 
 * @param cittadinanza Puntatore al buffer dove verrà memorizzata la cittadinanza.
 * @param dim Dimensione del buffer.
 */
void inputCittadinanza(char *cittadinanza, int dim);

/**
 * @brief Chiede all'utente se la residenza è estera.
 * 
 * @return 'S' per sì, 'N' per no.
 */
char inputEstero(void);

/**
 * @brief Acquisisce l'indirizzo (via).
 * 
 * @param indirizzo Puntatore al buffer dove verrà memorizzato l'indirizzo.
 * @param dim Dimensione del buffer.
 */
void inputIndirizzo(char *indirizzo, int dim);

/**
 * @brief Acquisisce CAP e provincia.
 * 
 * @param cap Puntatore al buffer dove verrà memorizzato il CAP.
 * @param capDim Dimensione del buffer CAP.
 * @param provincia Puntatore al buffer dove verrà memorizzata la provincia.
 * @param provDim Dimensione del buffer provincia.
 */
void inputCAPProvincia(char *cap, int capDim, char *provincia, int provDim);

#endif