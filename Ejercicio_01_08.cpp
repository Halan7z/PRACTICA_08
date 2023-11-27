// Materia: Programaci�n I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creaci�n: 26/11/2023

// Fecha modificaci�n: 26/11/2023

// N�mero de ejericio: 1

/* Problema planteado: Escribir un programa con la opci�n de encriptar y de desencriptar un fichero de texto.
La encriptaci�n consiste en que dado un fichero de texto de entrada genere otro fichero de
salida de extensi�n <nombre>.COD donde el texto estar� codificado (encriptado).
Esta codificaci�n consiste en reemplazar cada car�cter por el tercero siguiente seg�n la tabla
ASCII.
La opci�n de desencriptado consiste en leer un fichero <nombre>.COD y recuperar la
informaci�n original. */
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

void encriptar(const string &entrada, const string &salida)
{
    fflush(stdin);
    ifstream archivoEntrada(entrada);
    ofstream archivoSalida(salida);
    if (!archivoEntrada || !archivoSalida)
    {
        cout<<"Error al abrir los archivos"<<endl;
        return;
    }
    char caracter;
    cout<<"\nTexto encriptado: ";
    while (archivoEntrada.get(caracter))
    {
        char encriptado=caracter+3; // encriptacion
        archivoSalida.put(encriptado);
        cout<<encriptado;
    }
    cout<<"\nEncriptacion completada"<<endl;
}

void desencriptar(const string &entrada, const string &salida)
{
    fflush(stdin);
    ifstream archivoEntrada(entrada);
    ofstream archivoSalida(salida);
    if (!archivoEntrada || !archivoSalida)
    {
        cout<<"Error al abrir los archivos"<<endl;
        return;
    }
    char caracter;
    cout<<"\nTexto desencriptado: ";
    while (archivoEntrada.get(caracter))
    {
        char desencriptado = caracter - 3; // desencriptacion
        archivoSalida.put(desencriptado);
        cout<<desencriptado;
    }
    cout<<"\nDesencriptacion completada"<<endl;
}

int main()
{
    string nombreArchivo;
    ofstream archivo;
    while (true)
    {
        cout<<"Ingrese el nombre del archivo: ";
        cin>>nombreArchivo;
        string nombreArchivoTxt=nombreArchivo+".txt";
        // Abrir el archivo para escritura
        archivo.open(nombreArchivoTxt);
        if (!archivo)
        {
            cout<<"Error al abrir el archivo para escritura."<<endl;
            return 1;
        }
        cout<<"Escriba el texto en el archivo: ";
        fflush(stdin);
        string texto;
        getline(cin, texto);
        archivo<<texto;
        // Cerrar el archivo
        archivo.close();
        cout<<"Texto guardado en: "<<nombreArchivoTxt<<endl;
        int opcion;
        do {
            cout<<"\nOPCIONES:\n1. Encriptar\n2. Desencriptar\n3. Salir\n";
            cout<<"Seleccione una opcion: ";cin>>opcion;
            string nombreArchivoCOD=nombreArchivo+".COD";
            switch (opcion)
            {
                case 1:
                    fflush(stdin);
                    encriptar(nombreArchivoTxt, nombreArchivoCOD);
                    break;
                case 2:
                    fflush(stdin);
                    desencriptar(nombreArchivoCOD, nombreArchivo+"_desencriptado.txt");
                    break;
                case 3:
                    fflush(stdin);
                    cout<<"Saliendo del programa"<<endl;
                    return 0;
                default:
                    cout<<"Opcion no valida"<<endl;
                    break;
            }
        } while (true);
    }
    return 0;
}
