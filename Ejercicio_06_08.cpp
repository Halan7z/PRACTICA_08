// Materia: Programación I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 6

/* Problema planteado: Escriba un programa que tome como entrada el fichero del ejercicio 4 y una condición sobre el
campo Precio. La condición podrá ser:
Precio mayo o igual a 100 o cualquier otro dato ingresado por teclado.
Este programa debe generar como salida un fichero llamado "salida.dat" que contenga todos
aquellos artículos para los que se cumple la condición de entrada.
Mostrar el archivo de salida “salida.dat” */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Articulo {
    int codigo;
    char nombre[100]; // Mantenido como arreglo de caracteres para manejar correctamente las cadenas
    int existencias;
    double precio;
};

// Función para comparar dos artículos por su código
bool compararPorCodigo(const Articulo &a, const Articulo &b) {
    return a.codigo < b.codigo;
}

// Función para imprimir los datos de un archivo ordenados por código
void imprimirDatosOrdenados(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);

    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    Articulo articulo;

    // Leer e imprimir cada artículo
    while (archivo.read(reinterpret_cast<char*>(&articulo), sizeof(Articulo))) {
        cout << "Código: " << articulo.codigo << "\tNombre: " << articulo.nombre << "\tExistencias: " << articulo.existencias
             << "\tPrecio: " << fixed << setprecision(2) << articulo.precio << endl;
    }

    // Cerrar el archivo
    archivo.close();
}

// Función para filtrar artículos por la condición de precio
void filtrarPorPrecio(const string &nombreArchivoEntrada, const string &nombreArchivoSalida, double precioLimite) {
    ifstream archivoEntrada(nombreArchivoEntrada, ios::binary);
    ofstream archivoSalida(nombreArchivoSalida, ios::binary | ios::trunc);

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir los archivos." << endl;
        return;
    }

    Articulo articulo;

    // Leer cada artículo del archivo de entrada
    while (archivoEntrada.read(reinterpret_cast<char*>(&articulo), sizeof(Articulo))) {
        // Verificar la condición de precio
        if (articulo.precio <= precioLimite) {
            // Escribir el artículo en el archivo de salida si cumple con la condición
            archivoSalida.write(reinterpret_cast<char*>(&articulo), sizeof(Articulo));
        }
    }

    // Cerrar los archivos
    archivoEntrada.close();
    archivoSalida.close();

    cout << "Filtrado por precio completado. Resultado almacenado en " << nombreArchivoSalida << endl;

    // Imprimir los datos ordenados del archivo de salida
    cout << "\nDatos filtrados y ordenados por código:\n";
    imprimirDatosOrdenados(nombreArchivoSalida);
}

int main() {
    // Nombre del archivo de entrada y salida
    string archivoEntrada = "ALMACEN1.DAT";
    string archivoSalida = "salida.dat";

    double precioLimite;

    // Pedir al usuario la condición de precio
    cout << "Ingrese el límite de precio para la condición (por ejemplo, 100): ";
    cin >> precioLimite;

    // Llamar a la función para filtrar los artículos por precio
    filtrarPorPrecio(archivoEntrada, archivoSalida, precioLimite);

    return 0;
}
