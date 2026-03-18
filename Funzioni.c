#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Funzioni.h"
#include "Input.h"
#include "Dati.h"
#include "Controlli.h"

/**
 * @brief Carica i CAP e le province dal file "cap_prov.txt" nell'array globale ElencoCAP.
 * 
 * Raggiunge un massimo di CARICA_CAP_MAX elementi.
 */

void CaricaCAP_Prov()
{
    FILE *file = fopen("cap_prov.txt", "r");
    if (file == NULL)
    {
        printf("Errore nell'apertura del file");
        return;
    }

    while (fscanf(file, "%5s %2s", ElencoCAP[totaleCAP].codicePostale, ElencoCAP[totaleCAP].provincia) == 2) //per caricare i cap e privincie dal file //
    {
        totaleCAP++; 
        if (totaleCAP >= CARICA_CAP_MAX)
        {
            printf("Raggiunto il numero massimo di CAP.\n");
            break;
        }
    }

    fclose(file);
}

/**
 * @brief Carica i cittadini da un file e li inserisce nella lista.
 * 
 * @param File_cittadini Nome del file da cui leggere i cittadini.
 * @param testa Puntatore alla testa della lista dei cittadini.
 */

void caricaCittadini(const char *File_cittadini, NodoCittadino **testa)
{
    FILE *file = fopen(File_cittadini, "r");
    if (file == NULL)
    {
        printf("Errore nell'apertura del file.");
        return;
    }

    char linea[150]; //Riga di ogni cittadino presente nel file, messo 150 per sicurezza//
    while (fgets(linea, sizeof(linea), file))
    {
        Cittadino c;
        int gg, mm, a;
        char esteroChar;

        // Separiamo tutti i campi con sscanf
        int campiLetti = sscanf(linea, "%[^;];%[^;];%d/%d/%d;%[^;];%[^;];%c;%[^;];%[^;];%[^\n]", //Quando trova ; vuol dire che deve leggere un parametro nuovo //
                                c.nome,
                                c.cognome,
                                &gg, &mm, &a,
                                c.codiceFiscale,
                                c.cittadinanza,
                                &esteroChar,
                                c.indirizzo,
                                c.codicePostale,
                                c.provincia);

        c.data_nascita.giorno = gg;
        c.data_nascita.mese = mm;
        c.data_nascita.anno = a;
        c.estero = esteroChar;

        // Se la residenza è estera, non avrà indirizzo né CAP né Prov //
        if (c.estero == 'Y' || c.estero == 'y')
        {
            c.indirizzo[0] = '\0';
            c.codicePostale[0] = '\0';
            c.provincia[0] = '\0';
        }

        NodoCittadino *nuovoNodo = creaNodo(c);
        nuovoNodo->prossimo = *testa;
        *testa = nuovoNodo;
    }

    fclose(file);
}

/**
 * @brief Salva i dati dei cittadini presenti nella lista su un file.
 * 
 * @param File_cittadini Nome del file su cui salvare.
 * @param testa Puntatore alla testa della lista dei cittadini.
 */

void salvaCittadiniSuFile(const char *File_cittadini, NodoCittadino *testa)
{
    FILE *file = fopen(File_cittadini, "w");
    if (file == NULL)
    {
        printf("Impossibile aprire il file per scrittura.\n");
        return;
    }

    NodoCittadino *corrente = testa;
    while (corrente != NULL)
    {
        if (corrente->dati.estero == 'Y' || corrente->dati.estero == 'y')
        {
            //Se la residenza è estera, non si va a salvare né indirizzo né CAP né provincia perché non vengono richiesti//
            fprintf(file, "%s;%s;%02d/%02d/%04d;%s;%s;Y;;\n",
                    corrente->dati.nome,
                    corrente->dati.cognome,
                    corrente->dati.data_nascita.giorno,
                    corrente->dati.data_nascita.mese,
                    corrente->dati.data_nascita.anno,
                    corrente->dati.codiceFiscale,
                    corrente->dati.cittadinanza);
        }
        else
        {
            //Se la residenza ce l'ha in Italia, salva anche indirizzo, cap e prov//
            fprintf(file, "%s;%s;%02d/%02d/%04d;%s;%s;N;%s;%s;%s\n",
                    corrente->dati.nome,
                    corrente->dati.cognome,
                    corrente->dati.data_nascita.giorno,
                    corrente->dati.data_nascita.mese,
                    corrente->dati.data_nascita.anno,
                    corrente->dati.codiceFiscale,
                    corrente->dati.cittadinanza,
                    corrente->dati.indirizzo,
                    corrente->dati.codicePostale,
                    corrente->dati.provincia);
        }
        corrente = corrente->prossimo;
    }

    fclose(file);
    printf("Dati salvati con successo su file.\n");
}

/**
 * @brief Aggiunge un nuovo cittadino alla lista e salva la lista aggiornata sul file.
 * 
 * @param testa Puntatore alla testa della lista.
 * @param File_cittadini Nome del file in cui salvare la lista aggiornata.
 */

void aggiungiCittadino(NodoCittadino **testa, const char *File_cittadini)
{
    Cittadino nuovoCittadino;

    printf("\n--- Inserimento nuovo cittadino ---\n");

    inputNomi(nuovoCittadino.nome);
    inputCognomi(nuovoCittadino.cognome);

    char dataStr[11];
    do
    {
        inputDataNascita(dataStr, sizeof(dataStr));
        if (!verificaData(dataStr))
        {
            printf("Data non valida, riprova. Formato: gg/mm/aaaa\n");
        }
    } while (!verificaData(dataStr));

    sscanf(dataStr, "%2d/%2d/%4d", &nuovoCittadino.data_nascita.giorno,
           &nuovoCittadino.data_nascita.mese, &nuovoCittadino.data_nascita.anno);

    clearInputBuffer();

    do
    {
        inputCodiceFiscale(nuovoCittadino.codiceFiscale, LUNG_MAX_CF);
        if (!verificaCodiceFiscale(nuovoCittadino.codiceFiscale))
            printf("Codice Fiscale non valido, riprova. Devi scrivere tutto in maiuscolo.\n");
    } while (!verificaCodiceFiscale(nuovoCittadino.codiceFiscale));

    inputCittadinanza(nuovoCittadino.cittadinanza, LUNG_MAX_CITT);

    char estero = inputEstero();
    nuovoCittadino.estero = estero;

    if (nuovoCittadino.estero == 'N' || nuovoCittadino.estero == 'n')
    {
        inputIndirizzo(nuovoCittadino.indirizzo, LUNG_MAX_INDIRIZZO);
        inputCAPProvincia(nuovoCittadino.codicePostale, CAP_MAX, nuovoCittadino.provincia, PROV_MAX);
    }

    // Crea nuovo nodo e inserisci in testa lista
    NodoCittadino *nuovoNodo = malloc(sizeof(NodoCittadino));
    if (nuovoNodo == NULL)
    {
        printf("Errore allocazione memoria.\n");
        return;
    }
    nuovoNodo->dati = nuovoCittadino;
    nuovoNodo->prossimo = *testa;
    *testa = nuovoNodo;

    printf("Cittadino inserito correttamente.\n");

    salvaCittadiniSuFile(File_cittadini, *testa);
}

/**
 * @brief Visualizza i dati dei cittadini presenti nella lista, filtrando secondo il parametro.
 * 
 * @param testa Puntatore alla testa della lista.
 * @param filtro Codice che definisce il tipo di filtro da applicare (2-6).
 */

void visualizzaDati(NodoCittadino *testa, int filtro)
{
    NodoCittadino *corrente = testa;
    int count = 0;

    printf("\n--- Elenco Cittadini ---\n");

    while (corrente != NULL)
    {
        int include = 0;
        Cittadino c = corrente->dati;

        switch (filtro)
        {
        case 2:
            include = 1;
            break; // Tutti i cittadini
        case 3:
            if (strcmp(c.cittadinanza, "Italiana") == 0 && !(c.estero == 'Y' || c.estero == 'y'))
                include = 1; //Cittadini italiani residenti in Italia
            break;
        case 4:
            if (strcmp(c.cittadinanza, "Italiana") == 0 && (c.estero == 'Y' || c.estero == 'y'))
                include = 1; //Cittadini italiani residenti all'estero
            break;
        case 5:
            if (strcmp(c.cittadinanza, "Italiana") != 0 && !(c.estero == 'Y' || c.estero == 'y'))
                include = 1; //Cittadini stranieri residenti in Italia
            break;
        case 6:
            if (strcmp(c.cittadinanza, "Italiana") != 0 && (c.estero == 'Y' || c.estero == 'y'))
                include = 1; //Cittadini stranieri residenti all'estero
            break;
        }

        if (include)
        {
            count++;
            printf("\nCittadino %d:\n", count);
            printf("Nome: %s\n", c.nome);
            printf("Cognome: %s\n", c.cognome);
            printf("Data di nascita: %02d/%02d/%04d\n", c.data_nascita.giorno, c.data_nascita.mese, c.data_nascita.anno);
            printf("Codice fiscale: %s\n", c.codiceFiscale);
            printf("Cittadinanza: %s\n", c.cittadinanza);
            if (c.estero == 'Y' || c.estero == 'y')
            {
                printf("Residenza: Estera\n");
            }
            else
            {
                printf("Indirizzo: %s\n", c.indirizzo);
                printf("CAP: %s\n", c.codicePostale);
                printf("Provincia: %s\n", c.provincia);
            }
        }

        corrente = corrente->prossimo;
    }

    printf("\nTotale cittadini: %d\n", count);
}

/**
 * @brief Stampa in dettaglio i dati di un cittadino.
 * 
 * @param n Puntatore al nodo contenente il cittadino da visualizzare.
 */

void stampaCittadinoDettagliato(NodoCittadino *n)
{
    if (n == NULL)
        return;

    printf("\nCittadino trovato:\n");
    printf("Nome: %s\n", n->dati.nome);
    printf("Cognome: %s\n", n->dati.cognome);
    printf("Data di nascita: %02d/%02d/%04d\n",
           n->dati.data_nascita.giorno,
           n->dati.data_nascita.mese,
           n->dati.data_nascita.anno);
    printf("Codice fiscale: %s\n", n->dati.codiceFiscale);
    printf("Cittadinanza: %s\n", n->dati.cittadinanza);
    if (n->dati.estero == 'Y' || n->dati.estero == 'y')
    {
        printf("Residenza: Estera\n");
    }
    else
    {
        printf("Indirizzo: %s\n", n->dati.indirizzo);
        printf("CAP: %s\n", n->dati.codicePostale);
        printf("Provincia: %s\n", n->dati.provincia);
    }
}

/**
 * @brief Cerca un cittadino nella lista tramite il codice fiscale.
 * 
 * @param testa Puntatore alla testa della lista.
 * @param cf Codice fiscale da cercare.
 * @return NodoCittadino* Puntatore al nodo trovato, oppure NULL se non esiste.
 */

NodoCittadino *cercaPerCodiceFiscale(NodoCittadino *testa, const char *cf)
{
    while (testa != NULL)
    {
        if (strcmp(testa->dati.codiceFiscale, cf) == 0)
        {
            return testa;
        }
        testa = testa->prossimo;
    }
    return NULL;
}

/**

@brief Cerca un cittadino per nome e/o cognome.

@param testa Puntatore al primo nodo della lista dei cittadini.

@param annulla Puntatore a variabile booleana che diventa true se l'utente annulla.

@return Puntatore al nodo del cittadino selezionato, NULL se annullato o non trovato.
*/

NodoCittadino *cercaPerNomeECognome(NodoCittadino *testa, bool *annulla)
{
    *annulla = false;

    char nome[LUNG_MAX_NOME] = "";
    char cognome[LUNG_MAX_NOME] = "";

    printf("Inserisci nome, se vuoi fare la ricerca per cognome, premi enter (digita 0 per annullare): ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    if (strcmp(nome, "0") == 0)
    {
        *annulla = true;
        return NULL;
    }

    printf("Inserisci cognome, se hai inserito il nome e non vuoi inserire il cognome, premi enter (digita 0 per annullare): ");
    fgets(cognome, sizeof(cognome), stdin);
    cognome[strcspn(cognome, "\n")] = '\0';
    if (strcmp(cognome, "0") == 0)
    {
        *annulla = true;
        return NULL;
    }

    if (strlen(nome) == 0 && strlen(cognome) == 0) {
    printf("Nessun campo inserito, impossibile effettuare la ricerca.\n"); //In modo che se nn inserisci niente, stampi questo "errore"//
    return NULL;
}

    NodoCittadino *risultati[100];
    int count = 0;

    while (testa != NULL)
    {
        bool nome_ok = true;
        bool cognome_ok = true;

        if (strlen(nome) > 0)
        {
            nome_ok = strstr(testa->dati.nome, nome) != NULL;
        }
        if (strlen(cognome) > 0)
        {
            cognome_ok = strstr(testa->dati.cognome, cognome) != NULL;
        }

        if (nome_ok && cognome_ok)
        {
            if (count < 100)
            {
                risultati[count++] = testa;
            }
            else
            {
                printf("Attenzione: troppi risultati, alcuni potrebbero non essere mostrati.\n");
                break;
            }
        }

        testa = testa->prossimo;
    }

    if (count == 0)
    {
        printf("Nessun cittadino trovato con quel nome e/o cognome.\n");
        return NULL;
    }

    if (count == 1)
    {
        printf("Cittadino trovato: %s %s (CF: %s)\n",
               risultati[0]->dati.nome,
               risultati[0]->dati.cognome,
               risultati[0]->dati.codiceFiscale);
        return risultati[0];
    }

    printf("\nSono stati trovati %d cittadini:\n", count);
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s %s (CF: %s)\n", i + 1,
               risultati[i]->dati.nome,
               risultati[i]->dati.cognome,
               risultati[i]->dati.codiceFiscale);
    }

    int scelta = -1;
    do
    {
        printf("Seleziona il numero del cittadino desiderato (1-%d, oppure 0 per annullare): ", count);
        scanf("%d", &scelta);
        getchar(); // pulizia buffer
    } while (scelta < 0 || scelta > count);

    if (scelta == 0)
    {
        *annulla = true;
        printf("Operazione annullata dall’utente.\n");
        return NULL;
    }

    printf("Hai selezionato: %s %s (CF: %s)\n",
           risultati[scelta - 1]->dati.nome,
           risultati[scelta - 1]->dati.cognome,
           risultati[scelta - 1]->dati.codiceFiscale);

    return risultati[scelta - 1];
}

/**

@brief Permette la modifica interattiva dei dati di un cittadino.

@param cittadino Puntatore al nodo del cittadino da modificare.
*/

void modificaCittadino(NodoCittadino *cittadino)
{
    if (cittadino == NULL)
        return;

    int scelta;
    char buffer[LUNG_MAX_NOME];
    char dataStr[11]; // gg/mm/aaaa
    bool continua = true;

    while (continua)
    {
        printf("\n--- Modifica dati cittadino ---\n");
        printf("1. Nome attuale: %s\n", cittadino->dati.nome);
        printf("2. Cognome attuale: %s\n", cittadino->dati.cognome);
        printf("3. Codice Fiscale (NON MODIFICABILE): %s\n", cittadino->dati.codiceFiscale);
        printf("4. Data di nascita attuale: %02d/%02d/%04d\n",
               cittadino->dati.data_nascita.giorno,
               cittadino->dati.data_nascita.mese,
               cittadino->dati.data_nascita.anno);
        printf("5. Cittadinanza attuale: %s\n", cittadino->dati.cittadinanza);
        printf("6. Residenza estera attuale: %s\n",
               (cittadino->dati.estero == 'Y' || cittadino->dati.estero == 'y') ? "Sì" : "No");

        if (cittadino->dati.estero == 'N' || cittadino->dati.estero == 'n')
        {
            printf("7. Indirizzo attuale: %s\n", cittadino->dati.indirizzo);
            printf("8. CAP e provincia attuale: %s, %s\n", cittadino->dati.codicePostale, cittadino->dati.provincia);
        }

        printf("9. Esci dalla modifica\n");
        printf("Scegli il numero del campo da modificare (1-8, 3 non permesso): ");
        scanf("%d", &scelta);
        getchar(); // pulizia buffer

        switch (scelta)
        {
        case 1:
            inputNomi(cittadino->dati.nome);
            printf("Dati modificati correttamente\n");
            break;
        case 2:
            inputCognomi(cittadino->dati.cognome);
            printf("Dati modificati correttamente\n");
            break;
        case 4:
            do
            {
                inputDataNascita(dataStr, sizeof(dataStr));
                if (!verificaData(dataStr))
                {
                    printf("Data non valida, riprova.\n");
                }
            } while (!verificaData(dataStr));
            sscanf(dataStr, "%2d/%2d/%4d",
                   &cittadino->dati.data_nascita.giorno,
                   &cittadino->dati.data_nascita.mese,
                   &cittadino->dati.data_nascita.anno);
            printf("Dati modificati correttamente\n");
            break;
        case 5:
            inputCittadinanza(cittadino->dati.cittadinanza, LUNG_MAX_CITT);
            printf("Dati modificati correttamente\n");
            break;
        case 6:
        {
            char estero = inputEstero(); //Nel caso si voglia modificare la residenza estera//
            cittadino->dati.estero = estero;

            if (estero == 'N' || estero == 'n') //Se si passa a residenza non estera si va a richiedere i dati come indirizzo, cap e provincia// 
            {
                controllaResidenzaEstera(&cittadino->dati);
                printf("Dati modificati correttamente\n");
            }
            else
            {
                // Vengono annulati i dati se la residenza viene messa a estera//
                cittadino->dati.indirizzo[0] = '\0';
                cittadino->dati.codicePostale[0] = '\0';
                cittadino->dati.provincia[0] = '\0';
            }
            break;
        }
        case 7:
            if (cittadino->dati.estero == 'N' || cittadino->dati.estero == 'n')
            {
                inputIndirizzo(cittadino->dati.indirizzo, LUNG_MAX_INDIRIZZO);
                printf("Visto che hai cambiato la via, dovrai inserire il CAP e Provincia corrispondente.\n");
                cambioCAPPROV(&cittadino->dati);
                printf("Dati modificati correttamente\n");
            }
            else
            {
                printf("Campo non disponibile per residenti all'estero.\n"); //Nel caso per errore, si premesse il 7 anche se questo non viene mostrato se la residenza è estera, giusto in maniera di prevenzione//
            }
            break;
        case 8:
            if (cittadino->dati.estero == 'N' || cittadino->dati.estero == 'n')
            {
                cambioCAPPROV(&cittadino->dati);
                printf("Dati modificati correttamente\n");
            }
            else
            {
                printf("Modifica non permessa per residenti all'estero"); //Nel caso per errore, si premesse il 8 anche se questo non viene mostrato se la residenza è estera, giusto in maniera di prevenzione//
            }

            break;

        case 9:
            continua = false;
            break;
        default:
            printf("Scelta non valida, riprova.\n");
        }
    }

    printf("Modifiche completate. Di seguito, i dati dopo l'aggiornamento:\n");
    stampaCittadinoDettagliato(cittadino);
}

/**

@brief Menu principale interattivo per la gestione dell'anagrafe.

@param testa Puntatore al puntatore della testa della lista dei cittadini.

@param File_cittadini Nome del file contenente i dati dei cittadini.
*/

// Menu interattivo principale //
void menu(NodoCittadino **testa, const char *File_cittadini)
{
    int scelta;
    do
    {
        printf("\n--- Database Anagrafe Nazionale ---\n");
        printf("1. Inserisci un cittadino\n");
        printf("2. Visualizza tutti i cittadini\n");
        printf("3. Visualizza cittadini italiani residenti in Italia\n");
        printf("4. Visualizza cittadini italiani residenti all'estero\n");
        printf("5. Visualizza cittadini stranieri residenti in Italia\n");
        printf("6. Visualizza cittadini stranieri residenti all'estero\n");
        printf("7. Cerca un cittadino in base al codice fiscale\n");
        printf("8. Cerca un cittadino in base al nome e/o cognome\n");
        printf("9. Modifica i dati anagrafici di un cittadino\n");
        printf("10. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar(); // pulisce il buffer

        switch (scelta)
        {
        case 1:
            aggiungiCittadino(testa, File_cittadini);
            break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            visualizzaDati(*testa, scelta);
            break;

        case 7:
        {
            char cf[17];
            NodoCittadino *trovato = NULL;

            do
            {
                printf("Inserisci codice fiscale da cercare, LETTERE MAIUSCOLE (0 per annullare): ");
                fgets(cf, sizeof(cf), stdin);
                cf[strcspn(cf, "\n")] = '\0'; // Rimuove newline

                if (strcmp(cf, "0") == 0)
                {
                    printf("Operazione di ricerca annullata.\n");
                    break;
                }

                trovato = cercaPerCodiceFiscale(*testa, cf);
                if (!trovato)
                {
                    printf("Nessun cittadino trovato con quel codice fiscale. Ricontrolla e riprova.\n");
                }
            } while (!trovato);

            if (trovato)
            {
                stampaCittadinoDettagliato(trovato);
            }

            break;
        }

        case 8:
        {
            NodoCittadino *trovato = NULL;
            bool annulla = false;

            do
            {
                trovato = cercaPerNomeECognome(*testa, &annulla);

                if (!trovato && !annulla)
                {
                }

                if (annulla)
                {
                    printf("Operazione di ricerca annullata.\n");
                    break;
                }
            } while (!trovato);

            if (trovato)
            {
                printf("\nCittadino selezionato con successo:\n");
                stampaCittadinoDettagliato(trovato);
            }

            break;
        }

        case 9:
        {
            char cf[17];
            NodoCittadino *citt = NULL;

            do
            {
                printf("Inserisci codice fiscale del cittadino da modificare, LETTERE MAIUSCOLE (0 per annullare): ");
                fgets(cf, sizeof(cf), stdin);
                cf[strcspn(cf, "\n")] = '\0';

                if (strcmp(cf, "0") == 0)
                {
                    printf("Operazione di modifica annullata.\n");
                    break;
                }

                citt = cercaPerCodiceFiscale(*testa, cf);
                if (!citt)
                {
                    printf("Nessun cittadino trovato con quel codice fiscale. Riprova.\n");
                }
            } while (!citt);

            if (citt)
            {
                modificaCittadino(citt);
            }

            break;
        }

        case 10:
            printf("Uscita dal programma.\n");
            break;

        default:
            printf("Scelta non valida. Riprova.\n");
        }

    } while (scelta != 10);
}

/**

@brief Effettua il login di un operatore leggendo le credenziali da file.

@return 1 se il login ha successo, 0 in caso di fallimento o errore.
*/

int loginOperatore()
{
    FILE *file = fopen("dati_login.txt", "r");
    if (file == NULL)
    {
        printf("Errore nell'apertura del file di login.\n");
        return 0;
    }

    Operatore opDaFile;
    char usernameInserito[MAX_USERNAME];
    char passwordInserita[MAX_PASSWORD];
    int tentativi = 0;

    while (tentativi < MAX_TENTATIVI)
    {
        printf("\n--- LOGIN OPERATORE ---\n");
        printf("Inserisci username: ");
        fgets(usernameInserito, sizeof(usernameInserito), stdin);
        usernameInserito[strcspn(usernameInserito, "\n")] = '\0';

        printf("Inserisci password: ");
        fgets(passwordInserita, sizeof(passwordInserita), stdin);
        passwordInserita[strcspn(passwordInserita, "\n")] = '\0';

        rewind(file);
        int trovato = 0;

        while (fscanf(file, "%s %s %s %s", opDaFile.nome, opDaFile.cognome, opDaFile.username, opDaFile.password) == 4)
        {
            if (strcmp(usernameInserito, opDaFile.username) == 0 &&
                strcmp(passwordInserita, opDaFile.password) == 0)
            {
                trovato = 1;
                break;
            }
        }

        if (trovato)
        {
            fclose(file);
            printf("\nAccesso effettuato con successo. Benvenuto/a, %s %s.\n", opDaFile.nome, opDaFile.cognome);
            return 1;
        }

        tentativi++;
        if (!verificaTentativi(tentativi, MAX_TENTATIVI))
        {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 0;
}