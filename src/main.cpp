#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include "../include/classifica.hpp"
#include "../include/gioco.hpp" 


#define NUM_COLORS 8
using namespace std;

int choice_menu(WINDOW *menu) {
    int choice = 0, highlights = 0;
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);

    keypad(menu, true);

    char txt1[97] = "      _______          _            _          ";
    char txt2[48] = "     |__   __|        | |          (_)         ";
    char txt3[48] = "        | |      ___  | |_   _ __   _   ___    ";
    char txt4[48] = "        | |     / _ \\ | __| | '__| | | / __|   ";
    char txt5[48] = "        | |    |  __/ | |_  | |    | | \\__ \\   ";
    char txt6[48] = "        |_|     \\___|  \\__| |_|    |_| |___/   ";
   
    for (int i = 0; i < 48 - 1; i++) {
        mvwprintw(menu, 4, 30 + i, "%c", txt1[i]);
        mvwprintw(menu, 5, 30 + i, "%c", txt2[i]);
        mvwprintw(menu, 6, 30 + i, "%c", txt3[i]);
        mvwprintw(menu, 7, 30 + i, "%c", txt4[i]);
        mvwprintw(menu, 8, 30 + i, "%c", txt5[i]);
        mvwprintw(menu, 9, 30 + i, "%c", txt6[i]);
        wrefresh(menu);
        usleep(30000);
    }


    while (choice != 10){   

        if(highlights == 0) wattron(menu, A_REVERSE);

        mvwprintw(menu, 16, 38, "   _____   _                        ");
        mvwprintw(menu, 17, 38, "  / ____| (_)                       ");
        mvwprintw(menu, 18, 38, " | |  __   _    ___     ___    __ _ ");
        mvwprintw(menu, 19, 38, " | | |_ | | |  / _ \\   / __|  / _` |");
        mvwprintw(menu, 20, 38, " | |__| | | | | (_) | | (__  | (_| |");
        mvwprintw(menu, 21, 38, "  \\_____| |_|  \\___/   \\___|  \\__,_|");

        if(highlights == 0) wattroff(menu, A_REVERSE);
        if(highlights == 1) wattron(menu, A_REVERSE);


        mvwprintw(menu, 24, 38, "   ____                             ");
        mvwprintw(menu, 25, 38, " / ____|                            ");
        mvwprintw(menu, 26, 38, " | (___     ___    ___    _ __    ___ ");
        mvwprintw(menu, 27, 38, "  \\___ \\   / __|  / _ \\  | '__|  / _ \\");
        mvwprintw(menu, 28, 38, "  ____) | | (__  | (_) | | |    |  __/");
        mvwprintw(menu, 29, 38, " |_____/   \\___|  \\___/  |_|     \\___|");
        

        if(highlights == 1) wattroff(menu, A_REVERSE);
        if(highlights ==2)  wattron(menu, A_REVERSE);

        mvwprintw(menu, 32, 38, " _____      _ _   ");
        mvwprintw(menu, 33, 38, "| ____|_  _(_) |_ ");
        mvwprintw(menu, 34, 38, "|  _| \\ \\/ / | __|");
        mvwprintw(menu, 35, 38, "| |___ >  <| | |_ ");
        mvwprintw(menu, 36, 38, "|_____/_/\\_\\_|\\__|");

        if(highlights ==2)  wattroff(menu, A_REVERSE);

        choice = wgetch(menu);

        switch (choice)
        {
        case KEY_UP:
            highlights--;
            if(highlights == -1)
                highlights = 0;
            break;
        case KEY_DOWN:
            highlights++;
            if(highlights == 3)
                highlights = 2;
            break;

        default:
            break;
        }
    }

    return highlights;
}

int main() {
    
    initscr();cbreak();noecho();

    
    WINDOW *TUI = newwin(50, 110 , LINES/2 -25, COLS/2 -55);
    
    
    char filename[] = "./file.txt";  
    classifica my_classifica(filename);
    
    int choice; 
    do {   
        
        choice = choice_menu(TUI);
        switch(choice) {
            case 0: {
                
                wclear(TUI);
                wrefresh(TUI);
                
                
                srand(time(nullptr));
                
                
                Gioco gioco;
                gioco.inizializza();
                gioco.esegui();
                
                
                int nuovo_punteggio = gioco.getPunteggio();
                if(nuovo_punteggio > 0) {
                    my_classifica.inserisciPunteggio(nuovo_punteggio);
                    my_classifica.salvaPunteggi();
                }
                
               
                wclear(TUI);
                wrefresh(TUI);
                break;
            }
            case 1:
                
                wclear(TUI);    
                wrefresh(TUI);  
                my_classifica.drawClassifica(TUI);  
                refresh();  
                break;
                
            default: break;
        }
    } while (choice != 2);
    
    
    my_classifica.salvaPunteggi();
    my_classifica.distruggiPunteggi();
    
    
    clear();
    endwin();

    return EXIT_SUCCESS;
}
