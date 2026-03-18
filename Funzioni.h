#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <stdbool.h>
#include "Dati.h"

/**
 * @def MAX_TENTATIVI
 * Numero massimo di tentativi per il login.
 */
#define MAX_TENTATIVI 3

/**
 * @brief Carica da file tutti i CAP e le province.
 * 
 * Legge i dati dal file cap_prov.txt e popola l'array ElencoCAP.
 */
void CaricaCAP_Prov(); //PER LA CARICA DEL FILE CON TUTTI I CAP E PROV//

/**
 * @brief Carica i cittadini da file nella lista.
 * 
 * @param File_cittadini Nome del file da cui leggere i dati.
 * @param testa Puntatore al puntatore della testa della lista.
 */
void caricaCittadini(const char *File_cittadini, NodoCittadino **testa); //PER LA CARICA DEL FILE CONTENTENTE I CITADINI//

/**
 * @brief Menu principale del programma.
 * 
 * @param testa Puntatore al puntatore della lista dei cittadini.
 * @param File_cittadini Nome del file da cui caricare e su cui salvare.
 */
void menu(NodoCittadino **testa, const char *File_cittadini); //PER MENU NORMALE CON TUTTE LE FUNZIONALITà//

/**
 * @brief Aggiunge un nuovo cittadino alla lista e salva su file.
 * 
 * @param testa Puntatore al puntatore della lista.
 * @param File_cittadini Nome del file su cui salvare i dati.
 */
void aggiungiCittadino(NodoCittadino **testa, const char *File_cittadini); //PER AGGIUNGER EUN NUOVO CITTADINO//

/**
 * @brief Visualizza i dati dei cittadini applicando filtri.
 * 
 * @param testa Puntatore alla lista.
 * @param filtro Intero che rappresenta il filtro applicato.
 */
void visualizzaDati(NodoCittadino *testa, int filtro); //VISUALIZZAZIONE GENERALE DEI DATI CON I CORRESPONDENTI FILTRI//

/**
 * @brief Stampa dettagliata di un singolo cittadino.
 * 
 * @param n Puntatore al nodo contenente i dati del cittadino.
 */
void stampaCittadinoDettagliato(NodoCittadino *n); //PER VEDERE TUTTI I DATI, IN MODO DI AVERE UN ORDINE MIGLIORE, SI è CREATA QUESTA PER STAMPARE TUTTI I DATI DEL CITTADINO E COSì DA NON MISCHIARLA CON LA STAMPA CON FILTRI, SI UTILIZZA PER ESEMPIO, QUANDO SI MODIFICA/CERCA UN CITTADINO//

/**
 * @brief Ricerca di un cittadino tramite codice fiscale.
 * 
 * @param testa Puntatore alla testa della lista.
 * @param cf Codice fiscale da cercare.
 * @return Puntatore al nodo trovato o NULL se non esiste.
 */
NodoCittadino *cercaPerCodiceFiscale(NodoCittadino *testa, const char *cf); //RICERCA TRAMITE CF//

/**
 * @brief Ricerca per nome e/o cognome.
 * 
 * @param testa Puntatore alla testa della lista.
 * @param annulla Puntatore a booleano per gestire l'annullamento da parte dell'utente.
 * @return Puntatore al nodo selezionato o NULL.
 */
NodoCittadino *cercaPerNomeECognome(NodoCittadino *testa, bool *annulla); //RICERCA TRAMITE NOME E/O COGNOME, IN CASO DI PIù CORRISPONDENZE, FA VEDERE TUTTE E POI FA SCEGLIERE//

/**
 * @brief Modifica i dati di un cittadino (eccetto il codice fiscale).
 * 
 * @param cittadino Puntatore al cittadino da modificare.
 */
void modificaCittadino(NodoCittadino *cittadino); //PER TUTTE LE MODIFICHE DEI DATI, TRANNE CF PER TRATTARSI DI UN CODICE UNICO E CHE IN TEORIA, NON DOVREBBE CAMBIARE, COSì è STATO PENSATO//

/**
 * @brief Salva tutti i cittadini della lista su file.
 * 
 * @param File_cittadini Nome del file su cui salvare.
 * @param testa Puntatore alla testa della lista da salvare.
 */
void salvaCittadiniSuFile(const char *File_cittadini, NodoCittadino *testa); //PER SALVARE I DATI DEI CITTADINI QUANDO VENGONO MODIFICATI O QUANDO VENGONO CREATI//

/**
 * @brief Esegue il login dell’operatore.
 * 
 * @return 1 se login riuscito, 0 altrimenti.
 */
int loginOperatore(); //PER LOGIN INIZIALE//

#endif