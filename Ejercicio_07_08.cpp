// Materia: Programación I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 7

/* Problema planteado: Escriba un programa que tenga como entrada un fichero que contenga un texto y dé como
resultado una estadística del número de palabras. */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int contarPalabras(ifstream& archivo);

int main()
{
    ofstream archivoSalida("texto_ingresado.txt");
    if (!archivoSalida.is_open())
    {
        cout<<"No se pudo abrir el archivo de salida"<<endl;
        return 1;
    }
    string textoIngresado;
    cout<<"Ingrese el texto:"<<endl;
    getline(cin, textoIngresado);
    archivoSalida<<textoIngresado<<endl;

    archivoSalida.close();
    int opcion;

    do {
        cout<<"\nOPCIONES:\n";
        cout<<"1. Contar palabras en el archivo.\n";
        cout<<"2. Salir del programa.\n";
        cout<<"Ingrese su opcion: ";cin>>opcion;

        switch (opcion)
        {
            case 1: {
                ifstream archivoEntrada("texto_ingresado.txt");

                if (!archivoEntrada.is_open())
                {
                    cout<<"No se pudo abrir el archivo de entrada"<<endl;
                    return 1;
                }
                int totalPalabras=contarPalabras(archivoEntrada);
                cout<<"\nEstadísticas del archivo:\n";
                cout<<"Número total de palabras: "<<totalPalabras<<endl;

                archivoEntrada.close();
                break;
            }
            case 2:
                cout<<"Saliendo del programa\n";
                break;
            default:
                cout<<"Opcion no valida\n";
        }
    } while (opcion != 2);
    return 0;
}

int contarPalabras(ifstream& archivo)
{
    string linea;
    int contador=0;
    while (getline(archivo, linea))
    {
        istringstream stream(linea);
        string palabra;

        while (stream>>palabra)
            contador++;
    }

    return contador;
}
