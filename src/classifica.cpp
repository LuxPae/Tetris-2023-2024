#include "../include/classifica.hpp"
#define HEADER_SIZE_X 25


classifica::classifica(char *fileName)
{
    
    this->punteggi = new node;
    this->n_punteggi = 0;

   
    this->filename = fileName;

    
    ifstream file_punteggi(this->filename);
    
   
    int iter;

    
    while (file_punteggi >> iter) {     
        
        
        punteggi = insert_ordered(punteggi, iter);
       
       
       ++n_punteggi;
    }

    
    file_punteggi.close();
}


classifica::~classifica() {}

void classifica::drawClassifica(WINDOW *win){
	int choice = 0;
	int start_line = 28;

    WINDOW *header_win = newwin(8, 66 , LINES/2 -25, COLS/2 - 33);
    WINDOW *inner_win = newwin(30, 20 , LINES/2 -10, COLS/2 - 12);

    wrefresh(inner_win);
    
    
    keypad(inner_win, TRUE);
    scrollok(inner_win, TRUE);
    curs_set(FALSE);
    list tmp = punteggi;
    int index = 0;
    
    do
    {   print_menu(inner_win, start_line, tmp, index);
        drawHeader(header_win);
        
        wrefresh(inner_win);

        switch (choice = wgetch(inner_win)) {
            case KEY_UP:
                if (start_line > 28) {
                    --start_line;
                    tmp = tmp->prev;
                    --index;
                }
                break;
            case KEY_DOWN:
                if (start_line < n_punteggi) {
                    ++start_line;
                    ++index;
                    tmp=tmp->next;
                }
                break;
            default:
                break;
        }
    }while (choice != KEY_LEFT);
}

void classifica::print_menu(WINDOW *win, int start_line, list to_draw, int index) {
    int starty = 1;
    list tmp = to_draw;

    for(int i = index; i < start_line && i < n_punteggi; i++)
	{	mvwprintw(win, starty, 1, "    %d. %d    ", i+1, tmp->val);
        ++starty; 
        tmp = tmp->next;
	}
    wrefresh(win);
}

void classifica::drawHeader(WINDOW *win){
    mvwprintw(win, 2, 2, "   ____   _                       _    __   _                ");
    mvwprintw(win, 3, 2, "  / ___| | |   __ _   ___   ___  (_)  / _| (_)   ___    __ _ ");
    mvwprintw(win, 4, 2, " | |     | |  / _` | / __| / __| | | | |_  | |  / __|  / _` |");
    mvwprintw(win, 5, 2, " | |___  | | | (_| | \\__ \\ \\__ \\ | | |  _| | | | (__  | (_| |");
    mvwprintw(win, 6, 2, "  \\____| |_|  \\__,_| |___/ |___/ |_| |_|   |_|  \\___|  \\__,_|");
    wrefresh(win);
}

list classifica::getPunteggi(){
    return punteggi;
}

void classifica::distruggiPunteggi(){
    delete_list(this->punteggi);
}


void classifica::salvaPunteggi(){
    print_reverse(this->punteggi, this->filename);
}

void classifica::inserisciPunteggio(int p) { 
    this->punteggi = insert_ordered(this->punteggi, p);
    this->n_punteggi++;  
}

unsigned int classifica::getn_Punteggi(){
    return n_punteggi;
}

char *classifica::getFilename(){
    return filename;
}




