// Materia: Programación I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 4

/* Problema planteado: Codifique un programa que cree un fichero para contener los datos relativos a los artículos de
un almacén.
Para cada artículo habrá de guardar la siguiente información: ...... */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Articulo
{
    int codigo;
    string nombre;
    int existencias;
    double precio;
};

// Función para comparar dos artículos por su código
bool compararPorCodigo(const Articulo &a, const Articulo &b)
{
    return a.codigo<b.codigo;
}

int main() {
    vector<Articulo> almacen;

    int opcion;
    string nombreArchivo;

    cout<<"Seleccione el archivo para almacenar los datos:\n";
    cout<<"1. ALMACEN1.DAT\n";
    cout<<"2. ALMACEN2.DAT\n";
    cout<<"Ingrese la opción (1 o 2): ";cin>>opcion;

    switch (opcion)
    {
        case 1:
            nombreArchivo = "ALMACEN1.DAT";
            break;
        case 2:
            nombreArchivo = "ALMACEN2.DAT";
            break;
        default:
            cout<<"Opcion no valida"<<endl;
            return 1;
    }
    while (true)
    {
        Articulo nuevoArticulo;
        cout<<"Ingrese el codigo del articulo (0 para finalizar): ";
        cin>>nuevoArticulo.codigo;

        if (nuevoArticulo.codigo == 0)
            break;
        cin.ignore(); // Limpiar el buffer de entrada
        cout << "Ingrese el nombre del artículo: ";
        getline(cin, nuevoArticulo.nombre);
        cout << "Ingrese las existencias actuales: ";
        cin >> nuevoArticulo.existencias;
        cout << "Ingrese el precio: ";
        cin >> nuevoArticulo.precio;

        almacen.push_back(nuevoArticulo);
    }

    // Ordenar el vector por el código del artículo
    sort(almacen.begin(), almacen.end(), compararPorCodigo);

    ofstream archivoAlmacen(nombreArchivo, ios::binary | ios::app);

    while (!archivoAlmacen) {
        cerr << "Error al abrir el archivo para escritura. Intente nuevamente." << endl;
        cout << "Ingrese el nombre del archivo para almacenar los datos: ";
        cin >> nombreArchivo;
        archivoAlmacen.open(nombreArchivo, ios::binary | ios::app);
    }

    // Escribir los datos en el archivo
    for (const auto &articulo : almacen)
        archivoAlmacen.write(reinterpret_cast<const char*>(&articulo), sizeof(Articulo));

    archivoAlmacen.close();

    cout << "Datos añadidos al archivo " << nombreArchivo << "." << endl;

    // Imprimir los datos almacenados y ordenados por código
    cout << "\nDatos almacenados y ordenados por código:\n";
    for (const auto &articulo : almacen)
        cout << "Código: " << articulo.codigo << "\tNombre: " << articulo.nombre << "\tExistencias: " << articulo.existencias
             << "\tPrecio: " << fixed << setprecision(2) << articulo.precio << endl;

    return 0;
}
