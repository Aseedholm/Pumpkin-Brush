#include <SFML/Network.hpp>
#include <string.h> // memset
#include "Data.hpp"

struct dataStored {

};

int main() {
    sf::Packet packet;
    sf::TcpSocket serverSocket;
    // serverSocket.setBlocking(false);
    sf::Socket::Status serverStatus;

    //buffer that will contain datat
    char buffer[1000];

    memset(buffer, 0, 1000); //initialize buffer. 

    std::size_t received;

    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    sf::TcpListener listener;

    serverStatus = listener.listen(8080);

    if(serverStatus != sf::Socket::Done) {
        std::cerr << "Error!" << serverStatus << std::endl;
    }

    listener.accept(serverSocket);

    std::string serverMessage = "Connected to Server";
    serverSocket.send(serverMessage.c_str(), serverMessage.length()+1);

    serverSocket.receive(buffer, sizeof(buffer), received);
    // double xToPass = 0;
    // double yToPass = 0;
    // sf::Uint32 xToPass = 0;
    // sf::Uint32 yToPass = 0;
    // std::string commandToPass;


    ///
            sf::Uint32 xToPass = 0;
            sf::Uint32 yToPass = 0;
            std::string commandToPass;
            sf::Uint32 colorOfModificationToPass = 0;
            sf::Uint32 canvasColorToPass = 0;
            sf::Uint32 sizeOfModification = 0; //flag to send to server that'll be sent to other clients to determine GeneralBrush enum size. 
            sf::Uint32 brushTypeModification = 0; //flag to send to server that'll be sent to other clients to determine if it is a Pen or Brush being used to draw. 
            sf::Uint32 windowXToPass = 0;
            sf::Uint32 windowYToPass = 0;
    ////
    while(true){
        serverSocket.receive(packet);
        if (packet >> xToPass >> yToPass >> commandToPass >> colorOfModificationToPass >> canvasColorToPass >> sizeOfModification >> brushTypeModification >> windowXToPass >> windowYToPass) {
            std::cout << "Server> Received PACKET: \nX: " << xToPass << "\nY: " << yToPass << "\nCommand: " << commandToPass << "\nColor: " << colorOfModificationToPass << "\nCanvas Color: " << canvasColorToPass << "\nSize of Modifcation: " << sizeOfModification << "\nBrush TYpe of Modification: " << brushTypeModification << "\nWindow X: " << windowXToPass << "\nWindow Y: " << windowYToPass <<std::endl;
            packet.clear();
        }
        //buffer that will contain datat
    } //end of while loop.
    std::cout << "Server shutdown" << std::endl; 

    return 0;
}