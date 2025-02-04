#include "../include/gioco.hpp"


Gioco::Gioco() : tetraminoCorrente(nullptr), punteggio(0), gameOver(false) {
    
    for(int i = 0; i < ALTEZZA_CAMPO; i++) {
        for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
            campo[i][j] = false;    
            colori[i][j] = 0;       
        }
    }
}


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


void Gioco::inizializza() {
    
    noecho();
    curs_set(0);
    timeout(0);
    keypad(stdscr, TRUE);
    inizializzaColori();
    
    
    int startY = (LINES - (ALTEZZA_CAMPO + 2)) / 2;
    int startX = (COLS - (LARGHEZZA_CAMPO * 2 + 25)) / 2;
    
    
    campoWin = newwin(ALTEZZA_CAMPO + 2, LARGHEZZA_CAMPO * 2 + 2, startY, startX);
    punteggioWin = newwin(3, 20, startY, startX + LARGHEZZA_CAMPO * 2 + 4);
    
  
    wbkgd(campoWin, COLOR_PAIR(8));
    
    
    wattron(campoWin, COLOR_PAIR(8));
    box(campoWin, 0, 0);
    wattroff(campoWin, COLOR_PAIR(8));
    
    box(punteggioWin, 0, 0);
    
    
    tetraminoCorrente = new Tetramini(rand() % 2 );
}


bool Gioco::controllaCollisioni() {
    if (!tetraminoCorrente) return true;
    
    int tetrX = tetraminoCorrente->getX();
    int tetrY = tetraminoCorrente->getY();
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tetraminoCorrente->getBlocco(i, j)) {
                int campoX = tetrX + j;
                int campoY = tetrY + i;
                
            
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


void Gioco::disegnaCampo() {
    for(int i = 0; i < ALTEZZA_CAMPO; i++) {
        for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
            wmove(campoWin, i + 1, j * 2 + 1);
            if(campo[i][j]) {
                wattron(campoWin, COLOR_PAIR(colori[i][j]));
                wprintw(campoWin, "  "); 
                wattroff(campoWin, COLOR_PAIR(colori[i][j]));
            } else {
                wattron(campoWin, COLOR_PAIR(8));
                wprintw(campoWin, "  "); 
                wattroff(campoWin, COLOR_PAIR(8));
            }
        }
    }
    
    
    wattron(punteggioWin, COLOR_PAIR(8));
    mvwprintw(punteggioWin, 1, 1, "Punti: %d", punteggio);
    wattroff(punteggioWin, COLOR_PAIR(8));
    
    
    wrefresh(campoWin);
    wrefresh(punteggioWin);
}


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
                    wprintw(campoWin, "  "); 
                }
            }
        }
    }
    wattroff(campoWin, COLOR_PAIR(tetraminoCorrente->getColore() + 1));
    wrefresh(campoWin);
}


bool Gioco::muoviTetraminoGiu() {
    if (!tetraminoCorrente) return false;
    
    tetraminoCorrente->scendi();
    if(controllaCollisioni()) {
        tetraminoCorrente->setY(tetraminoCorrente->getY() - 1);
        bloccaTetramino();
        controllaLinee();
        delete tetraminoCorrente;
        tetraminoCorrente = new Tetramini(rand() % 2 );
        tetraminoCorrente->setX((LARGHEZZA_CAMPO / 2) - 2);
        tetraminoCorrente->setY(0);
        if(controllaCollisioni()) {
            gameOver = true;
        }
        return false;
    }
    return true;
}


void Gioco::esegui() {
    int tempoDiScesa = 0;
    int oldX, oldY;
    
    while(!gameOver) {
        int ch = getch();
        
        
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
                    
                    oldX = tetraminoCorrente->getX();
                    oldY = tetraminoCorrente->getY();
                    
                    
                    tetraminoCorrente->ruota_senso_orario();
                    
                    
                    if(controllaCollisioni()) {
                        tetraminoCorrente->sposta_sinistra();
                        if(controllaCollisioni()) {
                            tetraminoCorrente->sposta_destra();
                            tetraminoCorrente->sposta_destra();
                            if(controllaCollisioni()) {
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
        
        
        if(++tempoDiScesa > 30) {
            muoviTetraminoGiu();
            tempoDiScesa = 0;
        }
        
        
        disegnaCampo();
        disegnaTetramino();
        wrefresh(campoWin);
        
        usleep(10000); 
    }
    
    
    int startY = (LINES - (ALTEZZA_CAMPO + 2)) / 2;
    int startX = (COLS - (LARGHEZZA_CAMPO * 2 + 25)) / 2;
    
    WINDOW* gameOverWin = newwin(5, 30, startY + ALTEZZA_CAMPO/2 - 2, startX + LARGHEZZA_CAMPO - 5);
    box(gameOverWin, 0, 0);
    
    
    wattron(gameOverWin, COLOR_PAIR(8));
    mvwprintw(gameOverWin, 1, 2, "Game Over!");
    mvwprintw(gameOverWin, 2, 2, "Punti: %d", punteggio);
    mvwprintw(gameOverWin, 3, 2, "Premi INVIO per continuare");
    wattroff(gameOverWin, COLOR_PAIR(8));
    wrefresh(gameOverWin);
    

    
    timeout(-1);  
    while (getch()!= 10); 
    
    
    delwin(gameOverWin);
    
    
    clear();
    refresh();
}


void Gioco::controllaLinee() {
    for(int i = ALTEZZA_CAMPO - 1; i >= 0; i--) {
        bool lineaPiena = true;
        
        
        for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
            if(!campo[i][j]) {
                lineaPiena = false;
                break;
            }
        }
        
        if(lineaPiena) {
            punteggio += 100;  
            
            
            for(int k = i; k > 0; k--) {
                for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
                    campo[k][j] = campo[k-1][j];
                    colori[k][j] = colori[k-1][j];
                }
            }
            
            
            for(int j = 0; j < LARGHEZZA_CAMPO; j++) {
                campo[0][j] = false;
                colori[0][j] = 0;
            }
            
            
            i++;
        }
    }
} 