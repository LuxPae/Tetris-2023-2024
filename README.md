# Tetris
Una implementazione del classico gioco Tetris in C++ usando ncurses per la TUI.

## Comandi di Gioco
- **Freccia SU**: Ruota il pezzo in senso orario
- **Freccia GIÙ**: Accelera la discesa del pezzo
- **Freccia SINISTRA**: Muove il pezzo a sinistra
- **Freccia DESTRA**: Muove il pezzo a destra
- **INVIO**: Conferma (nei menu e dopo Game Over)

## Dinamiche di Gioco
1. I tetramini cadono dall'alto del campo di gioco
2. Il giocatore può:
   - Ruotare i pezzi per farli incastrare
   - Accelerare la discesa
   - Muoverli lateralmente
3. Quando una riga è completa:
   - Viene eliminata
   - Le righe sopra scendono
   - Il punteggio aumenta di 100 punti
4. Il gioco termina quando un nuovo pezzo non può essere posizionato in cima

## Implementazione Tetramini
I tetramini sono implementati usando il **Factory Method Pattern**:
   - La classe `tetramino_factory.cpp` crea i diversi tipi di tetramini
   - Ogni tetramino è una classe derivata dalla classe base `tetramino.cpp`
   - I tetramini, essendo che hanno un colore e una logica di rotazione diversa, sono stati implementati in classi separate tramite ereditarietà e polimorfismo nel file `tetramini_specifici.cpp`


## Sistema di Collisioni
Le collisioni sono gestite controllando:
1. Bordi del campo:
   - Limiti laterali
   - Fondo del campo
2. Altri pezzi già piazzati
3. Durante le rotazioni: si tenta di spostare il pezzo in maniera atomica se la rotazione non collide, nel caso la rotazione collida si annulla la rotazione

## Classifica
Alla fine di ogni partita, il punteggio viene salvato nella classifica, e salvata in un file locale per garantire persistenza dei dati fra una sessione di gioco e l'altra. All'avvio del gioco, la classifica viene caricata in una bilista e vengono mostrati i punteggi in ordine decrescente.

La scelta della bilista è dovuto al fatto che nella grafica, se vengono mostrati troppi punteggi è necessario scorrere la lista per mostrare i punteggi, ma se si scorre verso l'alto bisogna mostrare i punteggi eliminati dalla visualizzazione in precedenza. Dunque una bilista è la struttura dati più adatta per questo problema.

## Istruzioni di Compilazione ed Esecuzione

```bash
mkdir build
cd build
cmake ..
```
Se sei su mac o linux:

```bash
make
./tetris
```

Se sei su windows:
```bash
mingw32-make
tetris.exe
```

