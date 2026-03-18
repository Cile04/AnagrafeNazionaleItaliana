#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "Controlli.h"
#include "Funzioni.h"

/**
 * @brief Verifica che il codice fiscale abbia 16 caratteri alfanumerici (maiuscoli).
 * 
 * @param codiceFiscale Stringa del codice fiscale da controllare.
 * @return true se il formato è valido, false altrimenti.
 */
bool verificaCodiceFiscale(const char *codiceFiscale)
{
    if (strlen(codiceFiscale) != 16)
    {
        return false;
    }
    for (int i = 0; i < 16; i++)
    {
        char c = toupper((unsigned char)codiceFiscale[i]);
        if (!((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Verifica che l'indirizzo sia nel formato "Via ..., Numero".
 * 
 * @param indirizzo Stringa da validare.
 * @return true se il formato è corretto, false altrimenti.
 */
bool verificaFormatoIndirizzo(const char *indirizzo)
{
    if (strlen(indirizzo) == 0 || strlen(indirizzo) > LUNG_MAX_INDIRIZZO)
    {
        return false;
    }

    const char *virgola = strchr(indirizzo, ',');
    if (virgola == NULL || virgola == indirizzo || *(virgola + 1) == '\0')
    {
        return false;
    }

    bool contieneLettera = false;
    bool contieneNumero = false;

    for (int i = 0; indirizzo[i] != '\0'; i++)
    {
        if (isalpha(indirizzo[i]))
            contieneLettera = true;
        if (isdigit(indirizzo[i]))
            contieneNumero = true;
    }

    if (!contieneLettera || !contieneNumero)
    {
        return false;
    }

    return true;
}

/**
 * @brief Controlla che CAP e provincia corrispondano a una coppia valida nel file cap_prov.txt.
 * 
 * @param cap Codice di avviamento postale da controllare.
 * @param provincia Provincia corrispondente.
 * @return true se la combinazione esiste nel file, false altrimenti.
 */
bool controllaCAPProvincia(const char *cap, const char *provincia)
{
    FILE *file = fopen("cap_prov.txt", "r");
    if (file == NULL)
    {
        printf("Errore nell'apertura del file cap_prov.txt");
        return false;
    }

    char riga[10];
    char capFile[CAP_MAX], provinciaFile[PROV_MAX];
    while (fgets(riga, sizeof(riga), file))
    {
        if (sscanf(riga, "%s %s", capFile, provinciaFile) == 2)
        {
            if (strcmp(cap, capFile) == 0 && strcmp(provincia, provinciaFile) == 0)
            {
                fclose(file);
                return true;
            }
        }
    }

    fclose(file);
    return false;
}

/**
 * @brief Verifica che una data sia valida e nel formato corretto (GG/MM/AAAA).
 * 
 * @param data Stringa da validare.
 * @return true se la data è valida, false altrimenti.
 */
bool verificaData(const char *data)
{
    int giorno, mese, anno;

    if (sscanf(data, "%2d/%2d/%4d", &giorno, &mese, &anno) != 3)
    {
        return false;
    }

    if (giorno < 1 || giorno > 31 || mese < 1 || mese > 12 || anno < 1900 || anno > 2025)
    {
        return false;
    }

    int giorni_Mese[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0))
    {
        giorni_Mese[1] = 29;
    }

    if (giorno > giorni_Mese[mese - 1])
    {
        return false;
    }

    return true;
}

/**
 * @brief Se la residenza non è estera, richiede l'inserimento di indirizzo, CAP e provincia.
 * 
 * @param c Puntatore al cittadino di cui aggiornare la residenza.
 */
void controllaResidenzaEstera(Cittadino *c)
{
    if (c == NULL)
        return;

    if (c->estero == 'N' || c->estero == 'n')
    {
        printf("Hai indicato residenza NON estera, devi inserire indirizzo, CAP e provincia.\n");
        inputIndirizzo(c->indirizzo, LUNG_MAX_INDIRIZZO);
        inputCAPProvincia(c->codicePostale, CAP_MAX, c->provincia, PROV_MAX);
    }
}

/**
 * @brief Richiede di aggiornare CAP e provincia se la residenza non è estera.
 * 
 * @param c Puntatore al cittadino da aggiornare.
 */
void cambioCAPPROV(Cittadino *c)
{
    if (c == NULL)
        return;

    if (c->estero == 'N' || c->estero == 'n')
    {
        inputCAPProvincia(c->codicePostale, CAP_MAX, c->provincia, PROV_MAX);
    }
}

/**
 * @brief Gestisce il numero di tentativi di login e blocca il programma dopo troppi tentativi errati.
 * 
 * @param tentativi Numero di tentativi già effettuati.
 * @param max Numero massimo di tentativi consentiti.
 * @return 1 se si può continuare, 0 se si devono bloccare ulteriori accessi.
 */
int verificaTentativi(int tentativi, int max)
{
    int rimanenti = max - tentativi;
    if (rimanenti > 0)
    {
        printf("\nCredenziali errate. Tentativi rimasti: %d\n", rimanenti);
        return 1;
    }
    else
    {
        printf("\nIl massimo dei tentativi permessi è stato superato. Per sicurezza, il programma si sta chiudendo per prevenire ingressi non autorizzati.\n");
        return 0;
    }
}

/**
 * @brief Mostra un avviso legale e richiede conferma dell’utente prima di procedere.
 * 
 * Se l’utente rifiuta, il programma si chiude.
 * 
 * @return 1 se l’utente accetta, 0 altrimenti.
 */
int verifica_t_c(void)
{
    char risposta_t_c;

    printf("ATTENZIONE: ALCUNI DEI DATI UTILIZZATI PER QUESTO PROGETTO POTREBBERO ESSERE VERI!\n");
    printf("QUALSIASI MAL UTILIZZO POTREBBE ESSERE SEVERAMENTE PUNITO!\n\n");
    printf("Confermi di aver completamente letto e compreso quanto sopra? (y/n): ");

    risposta_t_c = getchar();

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    if (risposta_t_c == 'n' || risposta_t_c == 'N')
    {
        printf("Il programma si chiuderà per mantenere la sicurezza dei dati utilizzati all'interno del progetto.\n");
        return 0;
    }

    return 1;
}