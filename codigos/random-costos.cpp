#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Función para generar una fila de costos (para inserciones o eliminaciones)
void generarFilaDeCostos(const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int i = 0; i < 26; ++i) {
        archivo << rand() % 10 + 1;  // Costos entre 1 y 10
        if (i < 25) archivo << " ";
    }
    archivo << endl;
    archivo.close();
    cout << "Archivo " << nombreArchivo << " generado exitosamente." << endl;
}

// Función para generar una matriz de costos (para sustituciones o transposiciones)
void generarMatrizDeCostos(const string &nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (i == j) {
                archivo << 0;  // Costo 0 si es el mismo carácter
            } else {
                archivo << rand() % 10 + 1;  // Costos entre 1 y 10
            }
            if (j < 25) archivo << " ";
        }
        archivo << endl;
    }
    archivo.close();
    cout << "Archivo " << nombreArchivo << " generado exitosamente." << endl;
}

int main() {
    // Inicializar la semilla para la generación de números aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // Generar archivos para cada tipo de operación
    generarFilaDeCostos("cost_insert.txt");       // Costos de inserción
    generarFilaDeCostos("cost_delete.txt");       // Costos de eliminación
    generarMatrizDeCostos("cost_replace.txt");    // Costos de sustitución
    generarMatrizDeCostos("cost_transpose.txt");  // Costos de transposición

    return 0;
}