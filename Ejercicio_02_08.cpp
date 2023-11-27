// Materia: Programaci�n I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creaci�n: 26/11/2023

// Fecha modificaci�n: 26/11/2023

// N�mero de ejericio: 2

/* Problema planteado: Escriba un programa que cree un fichero de texto llamado "PERSONAS.BIN" en el que se
guarde la informaci�n de un n�mero indeterminado de personas.
La informaci�n que se guardar� por cada persona ser�: ... */
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Persona
{
    char nombre[31];
    int edad;
    char sexo;
    char fechaNacimiento[11];
};

int main()
{
    // modo binario
    ofstream archivo("PERSONAS.BIN", ios::binary | ios::app);
    if (!archivo)
    {
        cout<<"Error al abrir el archivo para escritura"<<endl;
        return 1;
    }
    Persona persona;
    while (true)
    {
        cout << "Ingrese el nombre (o espacio para salir): ";
        cin.getline(persona.nombre, 30);
        // verificar si se debe salir del bucle
        if (persona.nombre[0]==' '&& strlen(persona.nombre)==1)
            break;
        cout<<"Ingrese la edad (1-100): ";cin>>persona.edad;
        cout<<"Ingrese el sexo (M/F): ";cin>>persona.sexo;
        cout<<"Ingrese la fecha de nacimiento (dd/mm/yyyy): ";cin>>persona.fechaNacimiento;
        // Escribir la informaci�n de la persona en el archivo
        archivo.write(reinterpret_cast<char*>(&persona), sizeof(Persona));
        // Limpiar el buffer de entrada
        fflush(stdin);
    }
    // Cerrar el archivo
    archivo.close();
    cout << "El archivo PERSONAS.BIN fue creado exitosamente" << endl;
    return 0;
}
