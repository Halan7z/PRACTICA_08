// Materia: Programaci�n I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creaci�n: 26/11/2023

// Fecha modificaci�n: 26/11/2023

// N�mero de ejericio: 6

/* Problema planteado: Escriba un programa que tome como entrada el fichero del ejercicio 4 y una condici�n sobre el
campo Precio. La condici�n podr� ser:
Precio mayo o igual a 100 o cualquier otro dato ingresado por teclado.
Este programa debe generar como salida un fichero llamado "salida.dat" que contenga todos
aquellos art�culos para los que se cumple la condici�n de entrada.
Mostrar el archivo de salida �salida.dat� */

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

// Funci�n para comparar dos art�culos por su c�digo
bool compararPorCodigo(const Articulo &a, const Articulo &b) {
    return a.codigo < b.codigo;
}

// Funci�n para imprimir los datos de un archivo ordenados por c�digo
void imprimirDatosOrdenados(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);

    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    Articulo articulo;

    // Leer e imprimir cada art�culo
    while (archivo.read(reinterpret_cast<char*>(&articulo), sizeof(Articulo))) {
        cout << "C�digo: " << articulo.codigo << "\tNombre: " << articulo.nombre << "\tExistencias: " << articulo.existencias
             << "\tPrecio: " << fixed << setprecision(2) << articulo.precio << endl;
    }

    // Cerrar el archivo
    archivo.close();
}

// Funci�n para filtrar art�culos por la condici�n de precio
void filtrarPorPrecio(const string &nombreArchivoEntrada, const string &nombreArchivoSalida, double precioLimite) {
    ifstream archivoEntrada(nombreArchivoEntrada, ios::binary);
    ofstream archivoSalida(nombreArchivoSalida, ios::binary | ios::trunc);

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir los archivos." << endl;
        return;
    }

    Articulo articulo;

    // Leer cada art�culo del archivo de entrada
    while (archivoEntrada.read(reinterpret_cast<char*>(&articulo), sizeof(Articulo))) {
        // Verificar la condici�n de precio
        if (articulo.precio <= precioLimite) {
            // Escribir el art�culo en el archivo de salida si cumple con la condici�n
            archivoSalida.write(reinterpret_cast<char*>(&articulo), sizeof(Articulo));
        }
    }

    // Cerrar los archivos
    archivoEntrada.close();
    archivoSalida.close();

    cout << "Filtrado por precio completado. Resultado almacenado en " << nombreArchivoSalida << endl;

    // Imprimir los datos ordenados del archivo de salida
    cout << "\nDatos filtrados y ordenados por c�digo:\n";
    imprimirDatosOrdenados(nombreArchivoSalida);
}

int main() {
    // Nombre del archivo de entrada y salida
    string archivoEntrada = "ALMACEN1.DAT";
    string archivoSalida = "salida.dat";

    double precioLimite;

    // Pedir al usuario la condici�n de precio
    cout << "Ingrese el l�mite de precio para la condici�n (por ejemplo, 100): ";
    cin >> precioLimite;

    // Llamar a la funci�n para filtrar los art�culos por precio
    filtrarPorPrecio(archivoEntrada, archivoSalida, precioLimite);

    return 0;
}
