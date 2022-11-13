#include <cstdio>
#include <stdexcept>
#include <string>
#include <array>
#include <unistd.h>
#include <memory>
#include <omp.h>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "Commands.h"

// Estructura que tendra cada nodo nodo
struct Nodo
{
    std::string ip;
    std::string status;
    int pkRec,pkLoss,pkSend;
    Nodo *next; //salta al siguiente nodo
};

//Funcion que agrega pila
void addPila(Nodo *&, std::string ip, int pkSend, int pkRec, int pkLoss);
void addPila(Nodo *&pila, std::string ip, int pkSend, int pkRec, int pkLoss)
{
    Nodo *newNode = new Nodo();
    newNode->ip = ip;
    newNode->status = (pkRec > 0) ? "UP" : "DOWN";
    newNode->pkSend = pkSend;
    newNode->pkRec = pkRec;
    newNode->pkLoss = pkLoss;
    newNode->next = pila;
    pila = newNode;
}

//Pregunta si es un numero
bool esNum(const std::string &s);
bool esNum(const char* s)
{
  for( ; *s; ++s ){
    // En cuanto un caracter no sea numérico
    if( !std::isdigit(*s) )
    return false;
}

    return true;
}

void printfPila(Nodo *);
void printfPila(Nodo *pila)
{
    std::cout << "Ip\t\t|Status\t|Enviados\t|Recibido\t|Perdido.|" << std::endl;
    Nodo *aux = pila;
    while (aux != NULL)
    {
        std::cout << aux->ip << "\t|";
        std::cout << aux->status << "\t|";
        std::cout << aux->pkSend << "\t\t|";
        std::cout << aux->pkRec << "\t\t|";
        std::cout << aux->pkLoss << std::endl;
        aux = aux->next;
    }
}
//err = 0;
//string count = argv[2];
int main(int argc, char *argv[])
{
    // comprobacion de  argumentos anteriores
    if (argc < 2 || esNum(argv[2]) == false)
    {
        std::cout << "Argumentos ingresador en el Argv insuficientes [error1] \n";
        return 1;
    }

    // Variables que se declararon
    Nodo *pila = NULL;
    int countIp = 0;
    int CantE = 0;
    int pkRec,pkSend;
    std::string FILE = argv[1];
    std::ifstream file(FILE);
    std::string pkCant = argv[2];
    std::vector<std::string> ips;
    std::string linea;
    
    if (file.is_open())
    {
        // recorrer el archivo guardando las ip
        int count = 0;
    while (std::getline(file, linea)) //Obtiene el archivo y la linea
    {
        if (linea != "")
        {
            ips.push_back(linea); //Guarda la IP
        }
    }

    }else{
    std::cout << "El archivo no se pudo encontrar [error2] < " << FILE << " >" << std::endl;
    }
    file.close(); //Cierre de archivo
    countIp = ips.size(); //toma el tamaño de archivo

    //Cada ves que se agregue una pila, se usa una hebra
    #pragma omp parallel num_threads (countIp)
    {
        #pragma omp for
        for (auto x : ips)
        {
            // Llama al objeto de la clase creada
            Commands obj(x, pkCant);
            obj.runCommand();

            // Resguarda la pila
            #pragma omp critical
            {
                //Elementos que estaran en la pila
                addPila(pila, obj.getIp(), obj.getCantpkSend(), obj.getCantpkRec(), obj.getCantpkLoss());
            }
        }
    }
    printfPila(pila); //Imprime la pila y sus elementos
}
