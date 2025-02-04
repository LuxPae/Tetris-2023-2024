#include "../include/gioco.hpp"

/* Costruttore: inizializza il campo vuoto e le variabili di gioco
 * - Imposta il campo e i colori a zero
 * - Inizializza punteggio e gameOver
 * - Imposta il tetramino corrente a nullptr
 */
Gioco::Gioco() : tetraminoCorrente(nullptr), punteggio(0), gameOver(false) {
    // Inizializza il campo vuoto
    for(int i = 0; i < ALTEZZA_CAMPO; i++) {
        for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
            campo[i][j] = false;    // Nessun blocco
            colori[i][j] = 0;       // Nessun colore
        }
    }
}

/* Distruttore: libera la memoria allocata
 * - Elimina il tetramino corrente
 * - Distrugge le finestre ncurses
 */
Gioco::~Gioco() {
    delete tetraminoCorrente;
    delwin(campoWin);
    delwin(punteggioWin);
}


void Gioco::inizializzaColori() {
    start_color();
    use_default_colors();

    init_pair(1, COLOR_BLACK, COLOR_CYAN);    
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);  
    init_pair(8, COLOR_WHITE, COLOR_BLACK);  
}

/* Inizializza il gioco:
 * - Configura ncurses
 * - Crea le finestre centrate
 * - Imposta i colori
 * - Crea il primo tetramino
 */
void Gioco::inizializza() {
    // Inizializza ncurses
    noecho();
    curs_set(0);
    timeout(0);
    keypad(stdscr, TRUE);
    inizializzaColori();
    
    // Calcola le posizioni centrali
    int startY = (LINES - (ALTEZZA_CAMPO + 2)) / 2;
    int startX = (COLS - (LARGHEZZA_CAMPO * 2 + 25)) / 2;
    
    // Crea finestre centrate
    campoWin = newwin(ALTEZZA_CAMPO + 2, LARGHEZZA_CAMPO * 2 + 2, startY, startX);
    punteggioWin = newwin(3, 20, startY, startX + LARGHEZZA_CAMPO * 2 + 4);
    
    // Imposta lo sfondo nero per il campo di gioco
    wbkgd(campoWin, COLOR_PAIR(8));
    
    // Disegna i bordi
    wattron(campoWin, COLOR_PAIR(8));
    box(campoWin, 0, 0);
    wattroff(campoWin, COLOR_PAIR(8));
    
    box(punteggioWin, 0, 0);
    
    // Crea primo tetramino
    //int colore = (rand() % 2 == QUADRATO) ? YELLOW : CYAN;
    tetraminoCorrente = new Tetramini(rand() % 2 /*, colore*/);
}

/* Controlla se il tetramino corrente collide con:
 * - I bordi del campo
 * - Altri blocchi già presenti
 * @return true se c'è collisione, false altrimenti
 */
bool Gioco::controllaCollisioni() {
    if (!tetraminoCorrente) return true;
    
    int tetrX = tetraminoCorrente->getX();
    int tetrY = tetraminoCorrente->getY();
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tetraminoCorrente->getBlocco(i, j)) {
                int campoX = tetrX + j;
                int campoY = tetrY + i;
                
                // Controlla collisioni con i bordi e altri pezzi
                if(campoX < 0 || campoX >= LARGHEZZA_CAMPO || 
                   campoY >= ALTEZZA_CAMPO ||
                   (campoY >= 0 && campo[campoY][campoX])) {
                    return true;
                }
            }
        }
    }
    return false;
}

/* Blocca il tetramino corrente nella sua posizione:
 * - Copia i blocchi nella matrice del campo
 * - Imposta i colori corrispondenti
 */
void Gioco::bloccaTetramino() {
    if (!tetraminoCorrente) return;
    
    int tetrX = tetraminoCorrente->getX();
    int tetrY = tetraminoCorrente->getY();
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tetraminoCorrente->getBlocco(i, j)) {
                int campoY = tetrY + i;
                int campoX = tetrX + j;
                if(campoY >= 0 && campoY < ALTEZZA_CAMPO && 
                   campoX >= 0 && campoX < LARGHEZZA_CAMPO) {
                    campo[campoY][campoX] = true;
                    colori[campoY][campoX] = tetraminoCorrente->getColore() + 1;
                }
            }
        }
    }
}

/* Disegna il campo di gioco:
 * - Disegna i blocchi fissi con i loro colori
 * - Aggiorna il display del punteggio
 * - Refresha le finestre
 */
void Gioco::disegnaCampo() {
    // Disegna il campo
    for(int i = 0; i < ALTEZZA_CAMPO; i++) {
        for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
            wmove(campoWin, i + 1, j * 2 + 1);
            if(campo[i][j]) {
                wattron(campoWin, COLOR_PAIR(colori[i][j]));
                wprintw(campoWin, "  "); // Due spazi con sfondo colorato
                wattroff(campoWin, COLOR_PAIR(colori[i][j]));
            } else {
                wattron(campoWin, COLOR_PAIR(8));
                wprintw(campoWin, "  "); // Due spazi con sfondo nero
                wattroff(campoWin, COLOR_PAIR(8));
            }
        }
    }
    
    // Aggiorna punteggio
    wattron(punteggioWin, COLOR_PAIR(8));
    mvwprintw(punteggioWin, 1, 1, "Punti: %d", punteggio);
    wattroff(punteggioWin, COLOR_PAIR(8));
    
    // Refresh delle finestre
    wrefresh(campoWin);
    wrefresh(punteggioWin);
}

/* Disegna il tetramino corrente:
 * - Usa il colore specifico del tetramino
 * - Disegna solo i blocchi visibili (y >= 0)
 */
void Gioco::disegnaTetramino() {
    if (!tetraminoCorrente) return;
    
    int tetrX = tetraminoCorrente->getX();
    int tetrY = tetraminoCorrente->getY();
    wattron(campoWin, COLOR_PAIR(tetraminoCorrente->getColore() + 1));
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tetraminoCorrente->getBlocco(i, j)) {
                int campoY = tetrY + i;
                int campoX = tetrX + j;
                if(campoY >= 0 && campoY < ALTEZZA_CAMPO) {
                    wmove(campoWin, campoY + 1, campoX * 2 + 1);
                    wprintw(campoWin, "  "); // Due spazi con sfondo colorato
                }
            }
        }
    }
    wattroff(campoWin, COLOR_PAIR(tetraminoCorrente->getColore() + 1));
    wrefresh(campoWin);
}

/* Muove il tetramino corrente verso il basso:
 * - Controlla le collisioni
 * - Se collide, blocca il tetramino e ne crea uno nuovo
 * - Controlla il game over
 * @return true se il movimento è riuscito, false altrimenti
 */
bool Gioco::muoviTetraminoGiu() {
    if (!tetraminoCorrente) return false;
    
    tetraminoCorrente->scendi();
    if(controllaCollisioni()) {
        tetraminoCorrente->setY(tetraminoCorrente->getY() - 1);
        bloccaTetramino();
        controllaLinee();
        delete tetraminoCorrente;
        //Color colore = (rand() % 2 == QUADRATO) ? YELLOW : CYAN;
        tetraminoCorrente = new Tetramini(rand() % 2 /*, colore*/);
        // Posiziona il nuovo tetramino al centro in alto
        tetraminoCorrente->setX((LARGHEZZA_CAMPO / 2) - 2);
        tetraminoCorrente->setY(0);
        if(controllaCollisioni()) {
            gameOver = true;
        }
        return false;
    }
    return true;
}

/* Loop principale del gioco:
 * - Gestisce l'input dell'utente
 * - Aggiorna la posizione del tetramino
 * - Disegna il campo e il tetramino
 * - Gestisce il game over
 */
void Gioco::esegui() {
    int tempoDiScesa = 0;
    int oldX, oldY;
    
    while(!gameOver) {
        int ch = getch();
        
        // Gestione input
        if(ch != ERR) {
            switch(ch) {
                case KEY_LEFT:
                    tetraminoCorrente->sposta_sinistra();
                    if(controllaCollisioni()) 
                        tetraminoCorrente->sposta_destra();
                    break;
                    
                case KEY_RIGHT:
                    tetraminoCorrente->sposta_destra();
                    if(controllaCollisioni()) 
                        tetraminoCorrente->sposta_sinistra();
                    break;
                    
                case KEY_UP:
                    // Salva la posizione corrente
                    oldX = tetraminoCorrente->getX();
                    oldY = tetraminoCorrente->getY();
                    
                    // Prova a ruotare
                    tetraminoCorrente->ruota_senso_orario();
                    
                    // Se c'è collisione, prova a spostare il pezzo
                    if(controllaCollisioni()) {
                        // Prova a spostare a sinistra
                        tetraminoCorrente->sposta_sinistra();
                        if(controllaCollisioni()) {
                            // Prova a spostare a destra
                            tetraminoCorrente->sposta_destra();
                            tetraminoCorrente->sposta_destra();
                            if(controllaCollisioni()) {
                                // Se nessuno spostamento funziona, annulla la rotazione
                                tetraminoCorrente->setX(oldX);
                                tetraminoCorrente->setY(oldY);
                                tetraminoCorrente->ruota_senso_antiorario();
                            }
                        }
                    }
                    break;
                    
                case KEY_DOWN:
                    muoviTetraminoGiu();
                    break;
            }
        }
        
        // Aggiorna posizione tetramino
        if(++tempoDiScesa > 30) {
            muoviTetraminoGiu();
            tempoDiScesa = 0;
        }
        
        // Disegna
        disegnaCampo();
        disegnaTetramino();
        wrefresh(campoWin);
        
        usleep(10000); // 10ms delay
    }
    
    // Gestione Game Over migliorata
    int startY = (LINES - (ALTEZZA_CAMPO + 2)) / 2;
    int startX = (COLS - (LARGHEZZA_CAMPO * 2 + 25)) / 2;
    
    // Crea finestra Game Over
    WINDOW* gameOverWin = newwin(5, 30, startY + ALTEZZA_CAMPO/2 - 2, startX + LARGHEZZA_CAMPO - 5);
    box(gameOverWin, 0, 0);
    
    // Mostra messaggio Game Over
    wattron(gameOverWin, COLOR_PAIR(8));
    mvwprintw(gameOverWin, 1, 2, "Game Over!");
    mvwprintw(gameOverWin, 2, 2, "Punti: %d", punteggio);
    mvwprintw(gameOverWin, 3, 2, "Premi INVIO per continuare");
    wattroff(gameOverWin, COLOR_PAIR(8));
    wrefresh(gameOverWin);
    

    // timeout(-1): Imposta la modalità "bloccante". Il programma si fermerà ad aspettare 
    // l'input dell'utente quando viene chiamato getch().
    timeout(-1);  // Disabilita il timeout per l'input
    while (getch()!= 10); // Aspetta che l'utente prema invio
    
    // Pulisci la finestra di Game Over
    delwin(gameOverWin);
    
    // Pulisci lo schermo per tornare al menu
    clear();
    refresh();
}

/* Controlla e rimuove le linee complete:
 * - Identifica le linee piene
 * - Incrementa il punteggio
 * - Sposta le linee superiori verso il basso
 * - Gestisce linee multiple
 */
void Gioco::controllaLinee() {
    for(int i = ALTEZZA_CAMPO - 1; i >= 0; i--) {
        bool lineaPiena = true;
        
        // Controlla se la linea è piena
        for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
            if(!campo[i][j]) {
                lineaPiena = false;
                break;
            }
        }
        
        if(lineaPiena) {
            punteggio += 100;  // Incrementa il punteggio
            
            // Sposta tutte le linee sopra verso il basso
            for(int k = i; k > 0; k--) {
                for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
                    campo[k][j] = campo[k-1][j];
                    colori[k][j] = colori[k-1][j];
                }
            }
            
            // Pulisci la prima riga
            for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
                campo[0][j] = false;
                colori[0][j] = 0;
            }
            
            // Ricontrolla la stessa riga perché potrebbe esserci un'altra linea completa
            i++;
        }
    }
} 