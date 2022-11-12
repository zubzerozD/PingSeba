#include <iostream>
#include <string>
#include <sstream>

class Commands //Clase de ejecucion de comandos
{
    public:
        std::string ip,pkCant,getIp();
        int getCantpkLoss(),getCantpkRec(),getCantpkSend();
        void runCommand(),readList();
        Commands(std::string ip, std::string pkCant);

    private:
        std::string Answer;
        int pkSend,pkRec,pkLoss;
        void separatorAnswer();
};

/*
void Commands::readList()
{
    if (int argc < 2)
    {
        cout << "No se ingresaron los argumentos suficientes (2) \n";
        return 1;
    }
    //convierte el argumento 2 a integer
    pkCant = argv[2];
    //manejo de archivos
    // abrir el archivo de ips usando el argumento[1]
    std::ifstream ipFile;
    ipFile.open(argv[1]);

    // manejo de strings
    std::string ip;
    // si el archivo esta abierto
    if (ipFile.is_open())
    {
        // recorrer el archivo guardando las ip
        int count = 0;
        while (ipFile.good())
        {
            // lee y guarda hasta el primer salto de linea
            ipFile >> ip;
            pings[count].ip = ip;
            count++;
        }
    }
}*/


