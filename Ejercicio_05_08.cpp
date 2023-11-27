// Materia: Programación I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 5

/* Problema planteado: Escriba un programa que dados dos ficheros generados por el programa anterior y ordenados
genere un tercer fichero que sea el resultado de mezclar de formar ordenada los dos primeros. */

#include <iostream>
#include <fstream>

using namespace std;

struct Articulo {
    int codigo;
    string nombre;
    int existencias;
    double precio;
};

// Función para comparar dos artículos por su código
bool compararPorCodigo(const Articulo &a, const Articulo &b) {
    return a.codigo < b.codigo;
}

// Función para fusionar dos archivos ordenados y escribir el resultado en un tercer archivo
void fusionarArchivos(const string &nombreArchivo1, const string &nombreArchivo2, const string &nombreArchivoResultado) {
    ifstream archivo1(nombreArchivo1, ios::binary);
    ifstream archivo2(nombreArchivo2, ios::binary);
    ofstream archivoResultado(nombreArchivoResultado, ios::binary | ios::trunc);

    if (!archivo1 || !archivo2 || !archivoResultado) {
        cerr << "Error al abrir los archivos." << endl;
        return;
    }

    Articulo articulo1, articulo2;

    // Leer el primer artículo de cada archivo
    archivo1.read(reinterpret_cast<char*>(&articulo1), sizeof(Articulo));
    archivo2.read(reinterpret_cast<char*>(&articulo2), sizeof(Articulo));

    while (!archivo1.eof() && !archivo2.eof()) {
        // Comparar los códigos y escribir el artículo más pequeño en el archivo resultado
        if (compararPorCodigo(articulo1, articulo2)) {
            archivoResultado.write(reinterpret_cast<const char*>(&articulo1), sizeof(Articulo));
            archivo1.read(reinterpret_cast<char*>(&articulo1), sizeof(Articulo));
        } else {
            archivoResultado.write(reinterpret_cast<const char*>(&articulo2), sizeof(Articulo));
            archivo2.read(reinterpret_cast<char*>(&articulo2), sizeof(Articulo));
        }
    }

    // Escribir el resto de los artículos que quedan en el archivo 1
    while (!archivo1.eof()) {
        archivoResultado.write(reinterpret_cast<const char*>(&articulo1), sizeof(Articulo));
        archivo1.read(reinterpret_cast<char*>(&articulo1), sizeof(Articulo));
    }

    // Escribir el resto de los artículos que quedan en el archivo 2
    while (!archivo2.eof()) {
        archivoResultado.write(reinterpret_cast<const char*>(&articulo2), sizeof(Articulo));
        archivo2.read(reinterpret_cast<char*>(&articulo2), sizeof(Articulo));
    }

    // Cerrar los archivos
    archivo1.close();
    archivo2.close();
    archivoResultado.close();

    cout << "Fusion de archivos completada. Resultado almacenado en " << nombreArchivoResultado << endl;
}

int main() {
    // Nombre de los archivos de entrada y salida
    string archivo1 = "ALMACEN1.DAT";
    string archivo2 = "ALMACEN2.DAT";
    string archivoResultado = "ALMACEN_FUSION.DAT";

    // Llamar a la función para fusionar los archivos
    fusionarArchivos(archivo1, archivo2, archivoResultado);

    return 0;
}
