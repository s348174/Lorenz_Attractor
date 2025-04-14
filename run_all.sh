#!/bin/bash

# Verifica che siano stati passati due argomenti
if [ $# -lt 2 ]; then
    echo "Errore: Numero insufficiente di argomenti!"
    echo "Uso: $0 <tempo_massimo> <passo_integrazione>"
    exit 1
fi

# Assegna gli argomenti a variabili
tempo_massimo=$1
passo_integrazione=$2

# Percorso file di output
output_file="data/Lorenz_attractor_trajectory.csv"

# Compilazione del codice C++
g++ Project/main.cpp Project/src/Utils.cpp -o solve -std=c++17 -Iinclude -Iexternals/Main_Install/eigen3/include/eigen3 -O2

# Verifica se la compilazione ha avuto successo
if [ $? -ne 0 ]; then
    echo "Errore durante la compilazione del codice C++."
    exit 2
fi

# Crea la cartella dei dati se non esiste
mkdir -p data

# Esegui il programma C++ con i due argomenti
./solve "$tempo_massimo" "$passo_integrazione"

# Verifica che il file CSV sia stato creato
if [ ! -f "$output_file" ]; then
    echo "Errore: il file $output_file non è stato generato."
    exit 3
fi

# Lancia MATLAB passando il file CSV come argomento
export GTK_MODULES="canberra-gtk-module"
matlab -softwareopengl -r "plot_lorenz('$output_file')"
