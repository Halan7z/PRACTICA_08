// Materia: Programación I, Paralelo 1

// Autor: Alan Franz Flores Campos

// Fecha creación: 26/11/2023

// Fecha modificación: 26/11/2023

// Número de ejericio: 9

/* Problema planteado: Dado una tabla grabada en un fichero en formato binario <nombre>.BIN hallar la suma
horizontal y vertical y grabar la tabla y los resultados en otro fichero de texto o binario según se
introduzca por pantalla. */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

void leerTablaDesdeBinario(const string&, vector<vector<double>>&);
void calcularSumaHorizontalVertical(vector<vector<double>>& );
void Imprimir (vector<vector<double>>);
void guardarResultados(vector<vector<double>>, const string);

int main()
{
    const string nombreArchivoEntrada = "binarios.bin";
    const string nombreArchivoSalida = "resultados.txt";

    vector<vector<double>> tabla;
    vector<double> sumaHorizontal, sumaVertical;

    // Leer la tabla desde el archivo binario
    leerTablaDesdeBinario(nombreArchivoEntrada, tabla);

    // Calcular la suma horizontal y vertical
    calcularSumaHorizontalVertical(tabla);

    // Guardar los resultados en un archivo de texto
    guardarResultados(tabla, nombreArchivoSalida);

    //Para imprimir
    Imprimir(tabla);
    cout<<endl;
    cout << "Resultados guardados en: " << nombreArchivoSalida << endl;

    return 0;
}

void leerTablaDesdeBinario(const string& nombreArchivo, vector<vector<double>>& tabla)
{
    ifstream archivoEntrada(nombreArchivo, ios::binary);

    if (!archivoEntrada.is_open())
    {
        cout<< "No se pudo abrir el archivo de entrada" << endl;
        return;
    }

    double filas;
    for(int i=0;i<3;i++)
    {
        vector<double> aux;
        for(int j=0;j<3;j++)
        {
            archivoEntrada.read(reinterpret_cast<char*>(&filas), sizeof(double));
            aux.push_back(filas);
        }
        tabla.push_back(aux);
    }
    archivoEntrada.close();
}

void calcularSumaHorizontalVertical(vector<vector<double>>& tabla)
{
    int filas = tabla.size();
    int columnas = tabla[0].size();
    for (int i = 0; i < filas; ++i)
    {
        double sumaHorizontal =0.0;
        for (int j = 0; j < columnas; ++j)
        {
            sumaHorizontal += tabla[i][j];
        }
        tabla[i].push_back(sumaHorizontal);
    }
    tabla.push_back(tabla[0]);
    for (int i = 0; i < columnas+1; ++i)
    {
        double sumaVertical =0.0;
        for (int j = 0; j < filas; ++j)
        {
            sumaVertical += tabla[j][i];
        }
        tabla[tabla.size()-1][i]=sumaVertical;
    }
}
void Imprimir (vector<vector<double>> tabla)
{
    for(int i=0;i<tabla.size();i++)
    {
        for(int j=0;j<tabla[i].size();j++)
            cout<<tabla[i][j]<<"\t";
        cout<<"\n";
    }
}
void guardarResultados(vector<vector<double>> tabla, const string nombreArchivo) {
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida.is_open())
    {
        cout<< "No se pudo abrir el archivo de salida." << endl;
        return;
    }

    int filas = tabla.size();
    int columnas = tabla[0].size();

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivoSalida << tabla[i][j] << "\t";
        }
        archivoSalida << "\n";
    }
    archivoSalida.close();
}



