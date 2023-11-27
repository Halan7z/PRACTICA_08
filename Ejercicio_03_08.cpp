// Materia: Programación I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 3

/* Problema planteado: Amplíe el programa anterior que procesa clientes de una agencia matrimonial para que tome
los datos de todos los candidatos a estudiar del fichero PERSONAS.DAT del ejercicio anterior,
lea el cliente del teclado y finalmente genere como resultado un listado por pantalla con los
nombres de los candidatos aceptados y un fichero llamado ACEPTADOS.DAT con toda la
información correspondiente a los candidatos aceptados....... */

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

void mostrarCandidatosAceptados(const Persona& cliente, const Persona& candidato)
{
    cout<<"-Candidato: "<<candidato.nombre<<endl;
}
int main()
{
    //modo binario
    ifstream archivoPersonas("PERSONAS.BIN", ios::binary);

    if (!archivoPersonas)
    {
        cout<<"Error al abrir el archivo de personas para lectura"<<endl;
        return 1;
    }
    // Crear el archivo de candidatos aceptados para escritura en modo binario
    ofstream archivoAceptados("ACEPTADOS.BIN", ios::binary);
    if (!archivoAceptados)
    {
        cout<<"Error al abrir el archivo de candidatos aceptados para escritura"<<endl;
        return 1;
    }
    Persona cliente;
    Persona candidato;
    cout<<"Ingrese sus datos como cliente:"<<endl;cout<<"Nombre: ";
    cin.getline(cliente.nombre, 30);
    cout<<"Edad: ";cin>>cliente.edad;
    cout<<"Sexo (M/F): ";cin>>cliente.sexo;
    cout<<"Fecha de Nacimiento (dd/mm/yyyy): ";cin>>cliente.fechaNacimiento;

    // Mostrar encabezado del listado
    cout << "\nListado de Candidatos Aceptados:\n";

    // Leer datos de candidatos desde el archivo y procesar
    while (archivoPersonas.read(reinterpret_cast<char*>(&candidato), sizeof(Persona))) //Lectura desde el archivo binario
    {
        // Verificar si el candidato es aceptable
        if (cliente.sexo!=candidato.sexo && strncmp(cliente.fechaNacimiento+3, candidato.fechaNacimiento+3, 7)==0) // Comparación de las fechas de nacimiento de cliente y candidato.
        //esta condición verifica si el mes y el año de nacimiento del cliente y del candidato son iguales ademas del sexo diferente.
        {
            mostrarCandidatosAceptados(cliente, candidato);
            // Escribir el candidato aceptado en el archivo de aceptados
            archivoAceptados.write(reinterpret_cast<char*>(&candidato), sizeof(Persona));
        }
    }
    // Cerrar los archivos
    archivoPersonas.close();
    archivoAceptados.close();
    return 0;
}

