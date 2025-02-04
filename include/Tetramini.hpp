#ifndef TETRAMINI_HPP
#define TETRAMINI_HPP
#define QUADRATO 0
#define RETTANGOLO 1
#define CYAN 0
#define YELLOW 1

/*enum Color {
    CYAN,    // I - Pezzo lungo
    YELLOW,  // O - Quadrato
};*/

class Tetramini{
protected: 
    int forma;
    //Color colore;
    int colore;
    char matrice[4][4]; 
    int x; 
    int y; 

    void generaMatrice(); 

public:
    Tetramini(int tipo_forma /*, Color c*/);

    char (&getMatrice())[4][4];
    void ruota_senso_orario();
    void ruota_senso_antiorario();
    bool getBlocco(int i, int j) const;
    //Color getColore() const; 
    int getColore() const; 

    const int getX();
    const int getY();
    void setX(int newX);
    void setY(int newY);
    void sposta_sinistra();
    void sposta_destra();
    void scendi(); 
};

#endif 