## Sistema di Gestione Anagrafe Nazionale Italiana

Un'applicazione gestionale scritta in **C** per l'amministrazione e la consultazione dei dati anagrafici dei cittadini. Il sistema è progettato con un'architettura rigorosamente modulare, garantendo persistenza dei dati tramite file system, gestione dinamica della memoria e rigidi controlli di validazione degli input.

---

## Panoramica del Progetto

Questo software simula il database dell'Anagrafe Nazionale, permettendo agli operatori autorizzati di gestire i record dei cittadini. Attraverso un'interfaccia a riga di comando (CLI) interattiva, è possibile effettuare operazioni di **CRUD** (Create, Read, Update), applicare filtri di ricerca avanzati e mantenere l'integrità dei dati grazie a validazioni incrociate (come il controllo di corrispondenza tra CAP e Provincia su un database reale di oltre 8000 record).

---

## Funzionalità Principali

* **Autenticazione Sicura:** Accesso protetto da username e password. Il sistema prevede un blocco di sicurezza automatico dopo 3 tentativi falliti.
* **Gestione Dinamica della Memoria:** I record dei cittadini sono caricati e gestiti in RAM tramite una **Lista Concatenata Singola** (`NodoCittadino`), permettendo un'allocazione efficiente senza limiti rigidi di dimensione.
* **Gestione Anagrafica:**
    * **Inserimento:** Aggiunta di nuovi cittadini con logica condizionale (es. chi risiede all'estero - AIRE - non necessita di CAP e Provincia italiana).
    * **Ricerca Avanzata:** Ricerca esatta tramite Codice Fiscale o ricerca parziale tramite combinazione di Nome e/o Cognome con gestione delle omonimie.
    * **Modifica:** Aggiornamento interattivo dei campi anagrafici con ricalcolo dei requisiti di input.
* **Filtri di Visualizzazione:** Estrazione di liste specifiche:
    * Tutti i cittadini
    * Cittadini Italiani residenti in Italia
    * Cittadini Italiani residenti all'Estero
    * Cittadini Stranieri residenti in Italia
    * Cittadini Stranieri residenti all'Estero
* **Persistenza dei Dati:** Lettura e salvataggio automatico all'interno di file testuali utilizzando una formattazione strutturata (campi separati da punto e virgola `;`).

---

## Sicurezza e Validazione dei Dati

Il software implementa una libreria dedicata (`Controlli.c`) per garantire la validità formale e sostanziale dei dati:
* **Codice Fiscale:** Verifica della lunghezza esatta (16 caratteri) e del formato alfanumerico (accetta solo input validi e forza il controllo in maiuscolo).
* **Date di Nascita:** Parsing del formato `DD/MM/AAAA` con validazione del calendario (inclusa la corretta gestione degli anni bisestili).
* **Indirizzi:** Controllo stringa per garantire il formato coerente (presenza di lettere e numeri, es. "Via Roma, 1").
* **Congruenza CAP-Provincia:** Controllo in tempo reale scansionando il database di sistema `cap_prov.txt` per evitare inserimenti geograficamente impossibili.
* **Sanificazione Input:** Utilizzo di librerie custom (`Input.c`) per la pulizia del buffer (`stdin`) e l'uso esclusivo di `fgets` per prevenire buffer overflow tipici della funzione `scanf`.

---

## Architettura del Software e Moduli

Il codice sorgente è suddiviso in moduli funzionali (modello Header/Implementation), rendendo il progetto scalabile e facilmente manutenibile:

* 📄 `main.c`: Entry point del programma. Gestisce il workflow principale di inizializzazione e chiusura.
* 📄 `Dati.h` / `Dati.c`: Core data structures (`Cittadino`, `Operatore`, `CAPProvincia`) e implementazione della Linked List (creazione nodi, inserimento in testa, memory free).
* 📄 `Funzioni.h` / `Funzioni.c`: Logica di business (caricamento/salvataggio file, menu interattivo, algoritmi di ricerca, iterazione liste).
* 📄 `Controlli.h` / `Controlli.c`: Motore di validazione.
* 📄 `Input.h` / `Input.c`: Wrapper sicuri per l'I/O dell'utente.

### 🔄 Diagramma del Flusso di Esecuzione (Workflow)

```text
[Avvio Programma]
       │
       ▼
[Accettazione T&C (Disclaimer Dati Sensibili)] ──(Rifiuto)──> [Chiusura]
       │
       ▼
[Login Operatore (Max 3 Tentativi)] ──(Fallito)──> [Chiusura di Sicurezza]
       │
       ▼
[Caricamento in RAM: cap_prov.txt & cittadini.txt (Lista Concatenata)]
       │
       ▼
[ MENU INTERATTIVO PRINCIPALE ] <──────────────────────┐
       │                                               │
       ├─> 1. Inserisci nuovo cittadino ───────────────┤
       ├─> 2-6. Visualizza cittadini (con filtri) ─────┤
       ├─> 7-8. Cerca (per CF o Nome/Cognome) ─────────┤
       ├─> 9. Modifica anagrafica ─────────────────────┤
       │                                               │
       └─> 10. Esci ───────────────────────────────────┘
       │
       ▼
[Salvataggio (Dump) della Lista su cittadini.txt]
       │
       ▼
[Garbage Collection (liberaLista)]
       │
       ▼
[Chiusura Programma]

```

Installazione e Compilazione
Per compilare ed eseguire il progetto, è necessario un ambiente con compilatore C (es. GCC).

1. Clona il repository:

Bash
git clone https://github.com/TuoUsername/Anagrafe-Nazionale-C.git
cd Anagrafe-Nazionale-C
2. Compila i file sorgente creando l'eseguibile:

Bash
gcc main.c Dati.c Funzioni.c Controlli.c Input.c -o anagrafe
3. Esegui il programma:

Bash
# Su Linux/macOS
./anagrafe

# Su Windows
anagrafe.exe
Struttura File Richiesta
Assicurati che nella root del progetto siano presenti i seguenti file di database testuale (forniti nel repo):

cittadini.txt: Database principale dei record anagrafici.

cap_prov.txt: Dizionario con i codici postali e le province italiane.

dati_login.txt: Credenziali degli operatori autorizzati.

Disclaimer e Termini d'Uso

Attenzione: Il programma avvia un disclaimer all'esecuzione. Poiché il sistema utilizza e valida dati geografici e codici fiscali simulando un ambiente reale, l'utente deve confermare la presa visione delle responsabilità prima di poter effettuare il login. L'inserimento di dati sensibili reali non autorizzati all'interno di questo progetto didattico è sconsigliato e a rischio esclusivo dell'utente.

Copyright: Tutti i diritti riservati
