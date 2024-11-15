#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> // Para std::istringstream
#include <climits>  // Para INT_MAX
#include <chrono>   // Para medir el tiempo
#include <sys/resource.h>  // Para medir el uso de memoria (solo en sistemas compatibles)

using namespace std;
using namespace chrono;

// Declaración de funciones de costo (implementación detallada de cada función va aparte)
int costo_insert(char b);
int costo_delete(char a);
int costo_sub(char a, char b);
int costo_transpose(char a, char b);

// Declaración de algoritmos de distancia de edición (implementación detallada va aparte)
int distanciaEdicionFuerzaBruta(const string &S1, const string &S2, int i, int j, ofstream &operaciones);
int distanciaEdicionProgDinamica(const string &S1, const string &S2, ofstream &operaciones);

// Función para cargar la tabla de costos desde un archivo
vector<vector<int>> cargarTablaCostos(const string &nombreArchivo, int filas, int columnas) {
    ifstream archivo(nombreArchivo);
    vector<vector<int>> tabla(filas, vector<int>(columnas));
    
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivo >> tabla[i][j];
        }
    }
    archivo.close();
    return tabla;
}

// Variables globales para las tablas de costos
vector<int> costosInsert;
vector<int> costosDelete;
vector<vector<int>> costosReplace;
vector<vector<int>> costosTranspose;

// Función para obtener el uso de memoria (sólo en sistemas compatibles)
long getMemoriaUsada() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // Retorna la memoria máxima usada en kilobytes (dependiendo del sistema puede variar)
}

void runTest(const string &S1, const string &S2, ofstream &outputFile, ofstream &operacionesFile) {
    cout << "  Iniciando Fuerza Bruta..." << endl;
    operacionesFile << "Caso " << S1 << " vs " << S2 << "\n";
    operacionesFile << "Fuerza Bruta\n";
    auto startFB = high_resolution_clock::now();
    long memoriaFBInicio = getMemoriaUsada();
    int distanciaFB = distanciaEdicionFuerzaBruta(S1, S2, 0, 0, operacionesFile);
    long memoriaFBFin = getMemoriaUsada();
    auto stopFB = high_resolution_clock::now();
    auto durationFB = duration_cast<microseconds>(stopFB - startFB);
    cout << "  Fuerza Bruta completada." << endl;

    operacionesFile << "\nProgramación Dinámica\n";
    cout << "  Iniciando Programación Dinámica..." << endl;
    auto startDP = high_resolution_clock::now();
    long memoriaDPInicio = getMemoriaUsada();
    int distanciaDP = distanciaEdicionProgDinamica(S1, S2, operacionesFile);
    long memoriaDPFin = getMemoriaUsada();
    auto stopDP = high_resolution_clock::now();
    auto durationDP = duration_cast<microseconds>(stopDP - startDP);
    cout << "  Programación Dinámica completada." << endl;

    outputFile << "Caso: " << S1 << " vs " << S2 << "\n"
               << "Distancia (FB): " << distanciaFB << ", Tiempo (FB): " << durationFB.count() << " us, Memoria (FB): " << (memoriaFBFin - memoriaFBInicio) << " KB\n"
               << "Distancia (DP): " << distanciaDP << ", Tiempo (DP): " << durationDP.count() << " us, Memoria (DP): " << (memoriaDPFin - memoriaDPInicio) << " KB\n";

    operacionesFile << "--------\n";
}

int main() {
    // Cargar tablas de costos desde los archivos correspondientes
    costosInsert = cargarTablaCostos("cost_insert.txt", 1, 26)[0];
    cout << "Tabla de costos de inserción cargada correctamente." << endl;
    
    costosDelete = cargarTablaCostos("cost_delete.txt", 1, 26)[0];
    cout << "Tabla de costos de eliminación cargada correctamente." << endl;

    costosReplace = cargarTablaCostos("cost_replace.txt", 26, 26);
    cout << "Tabla de costos de sustitución cargada correctamente." << endl;

    costosTranspose = cargarTablaCostos("cost_transpose.txt", 26, 26);
    cout << "Tabla de costos de transposición cargada correctamente." << endl;

    ofstream outputFile("resultados.txt");
    ofstream operacionesFile("operaciones.txt");
    if (!outputFile || !operacionesFile) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return 1;
    }
    cout << "Archivo de salida abierto correctamente." << endl;

    ifstream casosFile("casos_prueba.txt");
    if (!casosFile) {
        cerr << "Error al abrir el archivo de casos de prueba." << endl;
        return 1;
    }

    string S1, S2;
    while (casosFile >> S1 >> S2) {  // Leer pares de cadenas
        // Si se detecta el marcador de string vacío `""`, asignar un string vacío
        if (S1 == "\"\"") S1 = "";
        if (S2 == "\"\"") S2 = "";

        cout << "Ejecutando prueba para: '" << S1 << "' vs '" << S2 << "'" << endl;
        runTest(S1, S2, outputFile, operacionesFile);
        cout << "Prueba completada para: '" << S1 << "' vs '" << S2 << "'" << endl;
    }

    outputFile.close();
    operacionesFile.close();
    casosFile.close();
    cout << "Archivo de salida cerrado correctamente." << endl;
    return 0;
}

// Inserción
int costo_insert(char b) {
    return costosInsert[b - 'a'];
}

// Eliminación
int costo_delete(char a) {
    return costosDelete[a - 'a'];
}

// Sustitución
int costo_sub(char a, char b) {
    return costosReplace[a - 'a'][b - 'a'];
}

// Transposición
int costo_transpose(char a, char b) {
    return costosTranspose[a - 'a'][b - 'a'];
}


int distanciaEdicionFuerzaBruta(const string &S1, const string &S2, int i, int j, ofstream &operaciones) {
    if (i == S1.length()) {
        int costo = 0;
        for (int k = j; k < S2.length(); ++k) {
            operaciones << "inserción " << S2[k] << "\n";
            costo += costo_insert(S2[k]);
        }
        return costo;
    }
    
    if (j == S2.length()) {
        int costo = 0;
        for (int k = i; k < S1.length(); ++k) {
            operaciones << "eliminación " << S1[k] << "\n";
            costo += costo_delete(S1[k]);
        }
        return costo;
    }
    
    // Calcular costos de cada operación sin escribir aún en el archivo
    int costoSustitucion = costo_sub(S1[i], S2[j]) + distanciaEdicionFuerzaBruta(S1, S2, i + 1, j + 1, operaciones);
    int costoInsercion = costo_insert(S2[j]) + distanciaEdicionFuerzaBruta(S1, S2, i, j + 1, operaciones);
    int costoEliminacion = costo_delete(S1[i]) + distanciaEdicionFuerzaBruta(S1, S2, i + 1, j, operaciones);

    int costoTransposicion = INT_MAX;
    if (i + 1 < S1.length() && j + 1 < S2.length() && S1[i] == S2[j + 1] && S1[i + 1] == S2[j]) {
        costoTransposicion = costo_transpose(S1[i], S1[i + 1]) + distanciaEdicionFuerzaBruta(S1, S2, i + 2, j + 2, operaciones);
    }

    // Determinar el costo mínimo y escribir solo la operación correspondiente
    int costoMinimo = min({costoSustitucion, costoInsercion, costoEliminacion, costoTransposicion});
    if (costoMinimo == costoSustitucion) {
        operaciones << "sustitución " << S1[i] << "->" << S2[j] << "\n";
    } else if (costoMinimo == costoInsercion) {
        operaciones << "inserción " << S2[j] << "\n";
    } else if (costoMinimo == costoEliminacion) {
        operaciones << "eliminación " << S1[i] << "\n";
    } else if (costoMinimo == costoTransposicion) {
        operaciones << "transposición " << S1[i] << S1[i + 1] << "\n";
    }

    return costoMinimo;
}

int distanciaEdicionProgDinamica(const string &S1, const string &S2, ofstream &operaciones) {
    int m = S1.length();
    int n = S2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Inicializar los casos base
    for (int i = 1; i <= m; ++i) {
        dp[i][0] = dp[i - 1][0] + costo_delete(S1[i - 1]);
        operaciones << "eliminación " << S1[i - 1] << "\n";
    }
    for (int j = 1; j <= n; ++j) {
        dp[0][j] = dp[0][j - 1] + costo_insert(S2[j - 1]);
        operaciones << "inserción " << S2[j - 1] << "\n";
    }

    // Llenar la matriz dp
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int costoSustitucion = dp[i - 1][j - 1] + costo_sub(S1[i - 1], S2[j - 1]);
            int costoInsercion = dp[i][j - 1] + costo_insert(S2[j - 1]);
            int costoEliminacion = dp[i - 1][j] + costo_delete(S1[i - 1]);
            
            dp[i][j] = min({costoSustitucion, costoInsercion, costoEliminacion});

            if (dp[i][j] == costoSustitucion) {
                operaciones << "sustitución " << S1[i - 1] << "->" << S2[j - 1] << "\n";
            } else if (dp[i][j] == costoInsercion) {
                operaciones << "inserción " << S2[j - 1] << "\n";
            } else if (dp[i][j] == costoEliminacion) {
                operaciones << "eliminación " << S1[i - 1] << "\n";
            }

            // Verificar la posibilidad de una transposición
            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                int costoTransposicion = dp[i - 2][j - 2] + costo_transpose(S1[i - 2], S1[i - 1]);
                if (dp[i][j] > costoTransposicion) {
                    dp[i][j] = costoTransposicion;
                    operaciones << "transposición " << S1[i - 2] << S1[i - 1] << "\n";
                }
            }
        }
    }

    return dp[m][n];
}
