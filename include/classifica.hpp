#include <fstream>
#include <ncurses.h>

#include "./my_list.hpp"

#define MENU_SIZE_Y n_punteggi + 2
#define MENU_SIZE_X 20



class classifica {
    protected:

        // attributi privati
        list punteggi;              // lista bidirezionale dei punteggi
        unsigned int n_punteggi;    // lunghezza della lista punteggi
        char* filename;             // nome del file su cui salvare la classifica

        // funzione usata per stampare il menu in caso di scorrimento della lista della classifica
        void print_menu(WINDOW *win, int start_line, list to_draw, int index);

        // funzione usata per disegnare l'intestazione della pagina della classifica
        void drawHeader(WINDOW *win);

    public:
        //Costruttore
        classifica(){};
        classifica(char* fileName);

        //distruttore
        ~classifica();

        //funzione che disegna la classifica a video
        void drawClassifica(WINDOW *win);

        // getter della lista punteggi
        list getPunteggi();

        // funzione che dealloca interamente la lista (viene richiamata prima della chiusura del gioco)
        void distruggiPunteggi();

        // apre in scrittura il file dei punteggi e salva tutti i file in ordine crescente 
        void salvaPunteggi();

        // inserisce in maniera ordinata decrescente un punteggio nella lista dei punteggi
        void inserisciPunteggio(int p);

        // getter del numero dei punteggi
        unsigned int getn_Punteggi();

        // getter del filename 
        char *getFilename();

};
