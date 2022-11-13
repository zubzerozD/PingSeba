#include <iostream>
#include <sstream>
#include <string>

class Commands //Clase de ejecucion de comandos
{
    //Objetos publicos
    public:
        std::string ip,pkCant,getIp();
        int getCantpkLoss(),getCantpkRec(),getCantpkSend();
        void runCommand(),readList();
        Commands(std::string ip, std::string pkCant);

    //Objetos privados
    private:
        std::string Answer;
        int pkSend,pkRec,pkLoss;
        void separatorAnswer();
};

//Constructor de Commands
Commands::Commands(std::string ip, std::string pkCant)
{
    this->ip = ip;
    this->pkCant = pkCant;
}

// Obtiene informacion mas precisa sobre el ping
void Commands::separatorAnswer()
{
    std::stringstream input_stringstream(this->Answer);
    std::string aux;
    getline(input_stringstream, aux, '\n');
    this->pkSend = std::stoi(aux);
    getline(input_stringstream, aux, '\n');
    this->pkRec = std::stoi(aux);
    this->pkLoss = this->pkSend - this->pkRec;
}

// lanza el comando por defecto ping,
// lee el output del comando separa la informacion sobre los paquetes que se transmitieron y se Reciben
void Commands::runCommand()
{
    std::string cmd = "ping -q -c " + this->pkCant + " " + this->ip + 
    " | grep -oP '[\\d+.,]+(?= packets transmitted)'\\|'[\\d+.,]+(?= received)'"; //Busca y lee en formato correcto el ping
    char buffer[256];
    FILE *pipe = popen(cmd.c_str(), "r"); //pipe = Tuberia
    if (!pipe)
    {
        return;
    }
    while (!feof(pipe))
    {
        if (fgets(buffer, 256, pipe) != NULL)
            this->Answer += buffer;
    }
    pclose(pipe);
    this->separatorAnswer();
}

//Retornos de ip y paquetes haciendo uso de get con puntero
std::string Commands::getIp(){return this->ip;}
int Commands::getCantpkRec(){return this->pkRec;}
int Commands::getCantpkSend(){return this->pkSend;}
int Commands::getCantpkLoss(){return this->pkLoss;}