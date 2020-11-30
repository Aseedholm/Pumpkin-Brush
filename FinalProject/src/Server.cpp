#include <SFML/Network.hpp>
#include <string.h> // memset
#include <queue>
#include <vector>
#include <thread>
#include "Data.hpp"



struct metaData {
    sf::Uint32 xToPass;
    sf::Uint32 yToPass;
    std::string commandToPass;
    sf::Uint32 colorOfModificationToPass;
    sf::Uint32 canvasColorToPass;
    sf::Uint32 sizeOfModification; //flag to send to server that'll be sent to other clients to determine GeneralBrush enum size. 
    sf::Uint32 brushTypeModification; //flag to send to server that'll be sent to other clients to determine if it is a Pen or Brush being used to draw. 
    sf::Uint32 windowXToPass;
    sf::Uint32 windowYToPass;
};

class Painter {
    public:
        void PainterThreadFunction(sf::TcpSocket socketP, int socketIndex) {
            
            sf::Packet packet;
            sf::Uint32 xToPass = 0;
            sf::Uint32 yToPass = 0;
            std::string commandToPass;
            sf::Uint32 colorOfModificationToPass = 0;
            sf::Uint32 canvasColorToPass = 0;
            sf::Uint32 sizeOfModification = 0; //flag to send to server that'll be sent to other clients to determine GeneralBrush enum size. 
            sf::Uint32 brushTypeModification = 0; //flag to send to server that'll be sent to other clients to determine if it is a Pen or Brush being used to draw. 
            sf::Uint32 windowXToPass = 0;
            sf::Uint32 windowYToPass = 0;
            while(true) {
                socketP.receive(packet);
                if (packet >> xToPass >> yToPass >> commandToPass >> colorOfModificationToPass >> canvasColorToPass >> sizeOfModification >> brushTypeModification >> windowXToPass >> windowYToPass)
                {
                    std::cout << "Server> Received PACKET FROM CLIENT: " << socketIndex << "\nX: " << xToPass << "\nY: " << yToPass << "\nCommand: " << commandToPass << "\nColor: " << colorOfModificationToPass << "\nCanvas Color: " << canvasColorToPass << "\nSize of Modifcation: " << sizeOfModification << "\nBrush TYpe of Modification: " << brushTypeModification << "\nWindow X: " << windowXToPass << "\nWindow Y: " << windowYToPass << std::endl;
                    //callback funtion that would execute the commands and broadcast it
                    packet.clear();
                }
            }
        }
};


int main() {

    // std::queue<metaData> commandQueue;
    // sf::Packet packet;
    // sf::TcpSocket serverSocket;
    // // sf::TcpSocket serverSocket2;
    // // serverSocket.setBlocking(false);
    // // serverSocket2.setBlocking(false);
    // sf::Socket::Status serverStatus;

    // //buffer that will contain datat
    // char buffer[1000];

    // memset(buffer, 0, 1000); //initialize buffer. 

    // std::size_t received;

    // sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    // sf::TcpListener listenerSocket;

    // serverStatus = listenerSocket.listen(8080);

    // if(serverStatus != sf::Socket::Done) {
    //     std::cerr << "Error!" << serverStatus << std::endl;
    // }

    // listenerSocket.accept(serverSocket);
    // // listenerSocket.accept(serverSocket2);

    // std::string serverMessage = "Connected to Server";
    // // std::string serverMessage2 = "Connected to Server AS CLIENT 2";
    // serverSocket.send(serverMessage.c_str(), serverMessage.length()+1);
    // // serverSocket2.send(serverMessage2.c_str(), serverMessage2.length()+1);

    // serverSocket.receive(buffer, sizeof(buffer), received);
    // // double xToPass = 0;
    // // double yToPass = 0;
    // // sf::Uint32 xToPass = 0;
    // // sf::Uint32 yToPass = 0;
    // // std::string commandToPass;


    // ///
    //         sf::Uint32 xToPass = 0;
    //         sf::Uint32 yToPass = 0;
    //         std::string commandToPass;
    //         sf::Uint32 colorOfModificationToPass = 0;
    //         sf::Uint32 canvasColorToPass = 0;
    //         sf::Uint32 sizeOfModification = 0; //flag to send to server that'll be sent to other clients to determine GeneralBrush enum size. 
    //         sf::Uint32 brushTypeModification = 0; //flag to send to server that'll be sent to other clients to determine if it is a Pen or Brush being used to draw. 
    //         sf::Uint32 windowXToPass = 0;
    //         sf::Uint32 windowYToPass = 0;
    // ////
    // while(true){ //serverStatus != sf::Socket::Done 
    // //spawn new socket and add pass it to a thread as an argument ->sf::TcpSocket serverSocket;
    // //spawn thread
    //     //pass class function into thread. 
    // // add the thread in vector 
    
    // //
    // //
    // //
    // // selector.add(socket);

    // serverSocket.receive(packet);
    // //spawn a thread
    // if (packet >> xToPass >> yToPass >> commandToPass >> colorOfModificationToPass >> canvasColorToPass >> sizeOfModification >> brushTypeModification >> windowXToPass >> windowYToPass)
    // {
    //     std::cout << "Server> Received PACKET: \nX: " << xToPass << "\nY: " << yToPass << "\nCommand: " << commandToPass << "\nColor: " << colorOfModificationToPass << "\nCanvas Color: " << canvasColorToPass << "\nSize of Modifcation: " << sizeOfModification << "\nBrush TYpe of Modification: " << brushTypeModification << "\nWindow X: " << windowXToPass << "\nWindow Y: " << windowYToPass << std::endl;
    //     //callback funtion that would execute the commands and broadcast it
    //     packet.clear();
    //     }
    //     //buffer that will contain datat
    // } //end of while loop.
    // std::cout << "Server shutdown" << std::endl; 

    ///////////////////////////////////////////////////////////////////////////////////////////
    std::vector<std::thread> painterThreadVector;
    std::vector<sf::TcpSocket> socketVector;
    std::queue<metaData> commandQueue;
    // sf::Packet packet;
    
    sf::Socket::Status serverStatus;

    std::size_t received;

    sf::TcpListener listenerSocket;

    serverStatus = listenerSocket.listen(8080);

    if(serverStatus != sf::Socket::Done) {
        std::cerr << "Error!" << serverStatus << std::endl;
    }


    Painter painter;

    int index = 0;
    while(serverStatus == sf::Socket::Done){ //serverStatus != sf::Socket::Done 
        std::cout<<serverStatus<<std::endl;
        sf::TcpSocket serverSocket;
        listenerSocket.accept(serverSocket);
        std::thread painterThread(&Painter::PainterThreadFunction, &painter,  serverSocket, index);
        //  std::thread painterThread(&Painter::PainterThreadFunction, &painter, index);
        painterThreadVector.push_back(std::move(painterThread));
        index++;
    }
    return 0;
}

