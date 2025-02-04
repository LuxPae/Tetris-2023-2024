#include <fstream>
#include <ncurses.h>

#include "./my_list.hpp"

#define MENU_SIZE_Y n_punteggi + 2
#define MENU_SIZE_X 20



class classifica {
    protected:

        
        list punteggi;              
        unsigned int n_punteggi;    
        char* filename;             

       
        void print_menu(WINDOW *win, int start_line, list to_draw, int index);

        
        void drawHeader(WINDOW *win);

    public:
        
        classifica(){};
        classifica(char* fileName);

        
        ~classifica();


        void drawClassifica(WINDOW *win);

        
        list getPunteggi();

        
        void distruggiPunteggi();

        
        void salvaPunteggi();

        
        void inserisciPunteggio(int p);

        
        unsigned int getn_Punteggi();

        
        char *getFilename();

};
