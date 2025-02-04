#ifndef GIOCO_HPP
#define GIOCO_HPP

#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>

#include"Tetramini.hpp"



#define ALTEZZA_CAMPO 20    
#define LARGHEZZA_CAMPO 10  


class Gioco {
private:
    bool campo[ALTEZZA_CAMPO][LARGHEZZA_CAMPO];  
    int colori[ALTEZZA_CAMPO][LARGHEZZA_CAMPO];  
    Tetramini* tetraminoCorrente;                
    int punteggio;                               
    bool gameOver;                               
    
    
    WINDOW* campoWin;      
    WINDOW* punteggioWin;  
    
    
    void inizializzaColori();     
    bool controllaCollisioni();    
    void bloccaTetramino();       
    void controllaLinee();        
    void disegnaCampo();          
    void disegnaTetramino();      
    bool muoviTetraminoGiu();     

public:
    Gioco();    
    ~Gioco();   

    void inizializza();  
    void esegui();      
    int getPunteggio() const { return punteggio; }  
};

#endif 