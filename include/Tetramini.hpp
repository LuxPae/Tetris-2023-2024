#ifndef TETRAMINI_HPP
#define TETRAMINI_HPP

#define QUADRATO 0
#define RETTANGOLO 1
#define CYAN 0
#define YELLOW 1

class Tetramini{
protected: 
    int forma;
    int colore;
    char matrice[4][4]; 
    int x; 
    int y; 

    void generaMatrice(); 

public:
    Tetramini(int tipo_forma);

    char (&getMatrice())[4][4];
    void ruota_senso_orario();
    void ruota_senso_antiorario();
    bool getBlocco(int i, int j) const; 
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