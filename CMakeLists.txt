cmake_minimum_required(VERSION 3.10)
project(Tetris)

# Funzione per installare le dipendenze su sistemi Unix-like
function(install_unix_dependencies)
    if(APPLE)
        execute_process(
            COMMAND brew install ncurses
            RESULT_VARIABLE BREW_RESULT
        )
        if(NOT BREW_RESULT EQUAL 0)
            message(WARNING "Errore nell'installazione di ncurses. Assicurati di avere Homebrew installato.")
        endif()
    elseif(UNIX)
        execute_process(
            COMMAND sudo apt-get update
            COMMAND sudo apt-get install -y libncurses5-dev
            RESULT_VARIABLE APT_RESULT
        )
        if(NOT APT_RESULT EQUAL 0)
            message(WARNING "Errore nell'installazione di ncurses. Prova a installarla manualmente.")
        endif()
    endif()
endfunction()

# Funzione per installare PDCurses su Windows
function(install_windows_dependencies)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/PDCurses")
        message(STATUS "Scaricando e installando PDCurses...")
        execute_process(
            COMMAND git clone https://github.com/wmcbrine/PDCurses.git
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            RESULT_VARIABLE GIT_RESULT
        )
        if(NOT GIT_RESULT EQUAL 0)
            message(FATAL_ERROR "Errore nel download di PDCurses. Assicurati di avere git installato.")
        endif()
        
        if(MINGW)
            execute_process(
                COMMAND mingw32-make -f mingw32.mak
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/PDCurses/wincon
                RESULT_VARIABLE MAKE_RESULT
            )
        else()
            execute_process(
                COMMAND nmake -f vcwin32.mak
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/PDCurses/wincon
                RESULT_VARIABLE MAKE_RESULT
            )
        endif()
        
        if(NOT MAKE_RESULT EQUAL 0)
            message(FATAL_ERROR "Errore nella compilazione di PDCurses")
        endif()
    endif()
endfunction()

# Verifica e installa le dipendenze in base al sistema operativo
if(WIN32)
    install_windows_dependencies()
    set(PDCURSES_INCLUDE_DIR "${CMAKE_BINARY_DIR}/PDCurses")
    set(PDCURSES_LIBRARY "${CMAKE_BINARY_DIR}/PDCurses/wincon/pdcurses.a")
    set(CURSES_LIBRARIES ${PDCURSES_LIBRARY})
    set(CURSES_INCLUDE_DIR ${PDCURSES_INCLUDE_DIR})
else()
    # Prova a trovare ncurses
    find_package(Curses QUIET)
    if(NOT CURSES_FOUND)
        message(STATUS "ncurses non trovato. Tentativo di installazione...")
        install_unix_dependencies()
        find_package(Curses REQUIRED)
    endif()
endif()

# Imposta lo standard C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Raccogli tutti i file sorgente
file(GLOB SOURCES 
    "src/*.cpp"
    "main.cpp"
)

# Crea l'eseguibile
add_executable(tetris ${SOURCES})

# Aggiungi le directory degli include
target_include_directories(tetris PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CURSES_INCLUDE_DIR}
)

# Collega le librerie
target_link_libraries(tetris PRIVATE ${CURSES_LIBRARIES})

# Copia il file di configurazione nella directory di build
configure_file(${CMAKE_SOURCE_DIR}/file.txt ${CMAKE_BINARY_DIR}/file.txt COPYONLY)

# Aggiungi script di configurazione
if(WIN32)
    configure_file(
        ${CMAKE_SOURCE_DIR}/scripts/setup_windows.bat.in
        ${CMAKE_BINARY_DIR}/setup_windows.bat
        @ONLY
    )
else()
    configure_file(
        ${CMAKE_SOURCE_DIR}/scripts/setup_unix.sh.in
        ${CMAKE_BINARY_DIR}/setup_unix.sh
        @ONLY
    )
    execute_process(COMMAND chmod +x ${CMAKE_BINARY_DIR}/setup_unix.sh)
endif()

# Messaggio informativo
message(STATUS "
Per compilare il progetto:
1. mkdir build
2. cd build
3. cmake ..
4. make (Linux/macOS) o mingw32-make (Windows con MinGW) o apri la soluzione in Visual Studio

Per eseguire:
./tetris (Linux/macOS) o tetris.exe (Windows)
")