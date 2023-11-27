// Materia: Programación I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 8

/* Problema planteado: Escribir un programa que genere a partir de un fichero de entrada que contiene una tabla de
números reales otro fichero de salida <nombre>.BIN grabado en formato binario. */

#include <iostream>
#include <fstream>

using namespace std;

void generarArchivoReales(const string& );
void convertirABinario(const string& , const string& );

int main()
{
    const string nombreArchivoReales = "reales.txt";
    const string nombreArchivoBinarios = "binarios.bin";

    // Generar el archivo "reales.txt" con números del 1 al 20
    generarArchivoReales(nombreArchivoReales);

    // Convertir los números a binario y guardar en "binarios.BIN"
    convertirABinario(nombreArchivoReales, nombreArchivoBinarios);

    return 0;
}

void generarArchivoReales(const string& nombreArchivo)
{
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida.is_open()) {
        cerr << "No se pudo abrir el archivo de salida." << endl;
        return;
    }

    for (int i = 0; i < 3; ++i) {
        for(int j=0; j<3;j++)
        {
            double numero;
            cout<<"Ingrese el valor de la fila "<<i+1<<" y de la columna "<<j+1<<": ";
            cin>>numero;
            archivoSalida << numero << " ";
        }
        archivoSalida<<"\n";
    }

    archivoSalida.close();
}

void convertirABinario(const string& nombreArchivoEntrada, const string& nombreArchivoSalida)
{
    ifstream archivoEntrada(nombreArchivoEntrada);

    if (!archivoEntrada.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        return;
    }

    ofstream archivoSalida(nombreArchivoSalida, ios::binary);

    if (!archivoSalida.is_open()) {
        cerr << "No se pudo abrir el archivo de salida." << endl;
        return;
    }

    double numero;
    while (archivoEntrada >> numero) {
        archivoSalida.write(reinterpret_cast<const char*>(&numero), sizeof(double));
    }

    archivoEntrada.close();
    archivoSalida.close();
}


