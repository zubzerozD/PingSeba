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

// estructura
struct Nodo
{
    std::string ip;
    std::string status;
    int pkRec,pkLoss,pkSend;
    Nodo *next; //salta al siguiente nodo
};

// prototipos
void addPila(Nodo *&, std::string ip, int pkSend, int pkRec, int pkLoss);
void printfPila(Nodo *);
bool esNum(const std::string &str);

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
    while (std::getline(file, linea))
    {
        if (linea != "")
        {
            ips.push_back(linea);
        }
    }
    }else{
    std::cout << "El archivo no se pudo encontrar [error2] < " << FILE << " >" << std::endl;
    }
    file.close();
    countIp = ips.size();

}

bool is_number(const std::string &s)
{
    bool flag = false;
    std::const_iterator it = s.begin();
    while (it != s.end()) {
        if (isdigit(*it)) flag = true;
        ++it;
    }
    return flag;
}


