#ifndef GIOCO_HPP
#define GIOCO_HPP

#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>

#include"Tetramini.hpp"
//#include "tetramino.hpp"
//#include "tetramino_factory.hpp"

// Dimensioni del campo di gioco
#define ALTEZZA_CAMPO 20    // Numero di righe del campo
#define LARGHEZZA_CAMPO 10  // Numero di colonne del campo

/* Classe principale che gestisce la logica del gioco Tetris
 * Si occupa di:
 * - Gestire il campo di gioco
 * - Controllare i movimenti dei tetramini
 * - Gestire l'input dell'utente
 * - Disegnare l'interfaccia grafica
 * - Calcolare il punteggio
 */
class Gioco {
private:
    bool campo[ALTEZZA_CAMPO][LARGHEZZA_CAMPO];  // Matrice che rappresenta il campo (true = occupato)
    int colori[ALTEZZA_CAMPO][LARGHEZZA_CAMPO];  // Matrice dei colori dei blocchi
    Tetramini* tetraminoCorrente;                // Puntatore al tetramino in movimento
    int punteggio;                               // Punteggio corrente
    bool gameOver;                               // Flag di fine gioco
    
    // Finestre ncurses per l'interfaccia grafica
    WINDOW* campoWin;      // Finestra del campo di gioco
    WINDOW* punteggioWin;  // Finestra del punteggio
    
    // Metodi privati per la logica di gioco
    void inizializzaColori();     // Inizializza le coppie di colori ncurses
    bool controllaCollisioni();    // Verifica collisioni del tetramino corrente
    void bloccaTetramino();       // Blocca il tetramino nella posizione corrente
    void controllaLinee();        // Controlla e rimuove le linee complete
    void disegnaCampo();          // Disegna il campo di gioco
    void disegnaTetramino();      // Disegna il tetramino corrente
    bool muoviTetraminoGiu();     // Muove il tetramino verso il basso

public:
    Gioco();    // Costruttore: inizializza il campo vuoto
    ~Gioco();   // Distruttore: libera la memoria e le finestre

    void inizializza();  // Inizializza ncurses e crea le finestre
    void esegui();      // Loop principale del gioco
    int getPunteggio() const { return punteggio; }  // Restituisce il punteggio
};

#endif 