#include <stdio.h>
#include <string.h>
#include "Input.h"

/**
 * @brief Pulisce il buffer di input standard da eventuali caratteri residui.
 */
void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * @brief Richiede e acquisisce il nome o i nomi di una persona.
 * 
 * @param nome Array di caratteri dove memorizzare il nome.
 */
void inputNomi(char nome[LUNG_MAX_NOME]) 
{
    printf("Inserisci nome/i (massimo 2): ");
    fgets(nome, LUNG_MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Rimuove \n
}

/**
 * @brief Richiede e acquisisce il cognome o i cognomi di una persona.
 * 
 * @param cognome Array di caratteri dove memorizzare il cognome.
 */
void inputCognomi(char cognome[LUNG_MAX_NOME])
{
    printf("Inserisci cognome/i (massimo 2): ");
    fgets(cognome, LUNG_MAX_NOME, stdin);
    cognome[strcspn(cognome, "\n")] = '\0'; // Rimuove \n
}

/**
 * @brief Richiede e acquisisce la data di nascita nel formato gg/mm/aaaa.
 * 
 * @param dataNascita Buffer dove salvare la data.
 * @param dim Dimensione massima del buffer.
 */
void inputDataNascita(char *dataNascita, int dim)
{
    printf("Inserisci data di nascita (gg/mm/aaaa): ");
    fgets(dataNascita, dim, stdin);
    dataNascita[strcspn(dataNascita, "\n")] = '\0';
}

/**
 * @brief Richiede e acquisisce il codice fiscale (in lettere maiuscole).
 * 
 * @param codiceFiscale Buffer dove salvare il codice fiscale.
 * @param dim Dimensione del buffer.
 */
void inputCodiceFiscale(char *codiceFiscale, int dim)
{
    printf("Inserisci codice fiscale (LETTERE MAIUSCOLE): ");
    if (fgets(codiceFiscale, dim, stdin) != NULL)
    {
        codiceFiscale[strcspn(codiceFiscale, "\n")] = '\0';
    }
}

/**
 * @brief Richiede e acquisisce la cittadinanza.
 * 
 * @param cittadinanza Buffer dove salvare la cittadinanza.
 * @param dim Dimensione del buffer.
 */
void inputCittadinanza(char *cittadinanza, int dim)
{
    clearInputBuffer();
    printf("Inserisci cittadinanza: ");
    fgets(cittadinanza, dim, stdin);
    cittadinanza[strcspn(cittadinanza, "\n")] = '\0';
}

/**
 * @brief Chiede all'utente se la residenza è all'estero.
 * 
 * @return 'y' se estera, 'n' altrimenti.
 */
char inputEstero(void)
{
    char estero;
    printf("L'indirizzo di residenza è estero? (y/n): ");
    scanf(" %c", &estero);
    clearInputBuffer();
    return estero;
}

/**
 * @brief Richiede e acquisisce l'indirizzo di residenza (via e numero civico).
 * Effettua un controllo di formato con verificaFormatoIndirizzo().
 * 
 * @param indirizzo Buffer dove salvare l'indirizzo.
 * @param dim Dimensione del buffer.
 */
void inputIndirizzo(char *indirizzo, int dim)
{
    do
    {
        printf("Inserisci indirizzo di residenza (Esempio: Via Gino Strada, 5): ");
        fgets(indirizzo, dim, stdin);
        indirizzo[strcspn(indirizzo, "\n")] = '\0';

        if (!verificaFormatoIndirizzo(indirizzo))
        {
            printf("L'indirizzo inserito non compie con i requisiti, assicurati di usare il formato: Via Gino Strada, 5\n\n");
        }
    } while (!verificaFormatoIndirizzo(indirizzo));
}

/**
 * @brief Richiede e acquisisce CAP e provincia (sigla a 2 lettere). 
 * Verifica la correttezza della combinazione usando controllaCAPProvincia().
 * 
 * @param cap Buffer per il CAP.
 * @param capDim Dimensione del buffer CAP.
 * @param provincia Buffer per la sigla della provincia.
 * @param provDim Dimensione del buffer provincia.
 */
void inputCAPProvincia(char *cap, int capDim, char *provincia, int provDim)
{
    bool valido = false;

    while (!valido)
    {
        printf("Inserisci codice postale (CAP): ");
        fgets(cap, capDim, stdin);
        cap[strcspn(cap, "\n")] = '\0';

        clearInputBuffer(); 

        printf("Inserisci provincia (sigla di 2 lettere, es. BA): ");
        fgets(provincia, provDim, stdin);
        provincia[strcspn(provincia, "\n")] = '\0';

        clearInputBuffer();

        if (controllaCAPProvincia(cap, provincia))
        {
            valido = true;
        }
        else
        {
            printf("CAP e provincia non corrispondono o non esistono. Riprova.\n");
        }
    }
}