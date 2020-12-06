#include <SFML/Network.hpp>
#include <string.h> // memset
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <map>
#include <condition_variable>
#include "Data.hpp"



struct metaData {
    int socketIndex;
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
    private:
        std::mutex mtx;
        std::mutex map_mtx;
        std::queue<metaData>commandQueue;
        std::vector<std::unique_ptr<sf::TcpSocket>> vectorOfSockets;
        std::map<int, std::unique_ptr<sf::TcpSocket>> mapOfSocket;
        std::condition_variable m_cv;

            //list of unqiue pointers to the socket
            public : 
            void PainterThreadFunction(std::unique_ptr<sf::TcpSocket> socketP, int socketIndex)
        {
            //move socket to vector at the provided index 
            //
            // vector_mtx.lock();
            // //socketP.getHandle(); 
            // vectorOfSockets.push_back(std::move(socketP));
            // vector_mtx.unlock();
            map_mtx.lock();
            mapOfSocket.insert({socketIndex, std::move(socketP)});
            map_mtx.unlock();
            sf::Packet packet;
            // sf::Uint32 xToPass = 0;
            // sf::Uint32 yToPass = 0;
            // std::string commandToPass;
            // sf::Uint32 colorOfModificationToPass = 0;
            // sf::Uint32 canvasColorToPass = 0;
            // sf::Uint32 sizeOfModification = 0; //flag to send to server that'll be sent to other clients to determine GeneralBrush enum size. 
            // sf::Uint32 brushTypeModification = 0; //flag to send to server that'll be sent to other clients to determine if it is a Pen or Brush being used to draw. 
            // sf::Uint32 windowXToPass = 0;
            // sf::Uint32 windowYToPass = 0;

          
            while (true)
            {
                mapOfSocket.find(socketIndex)->second->receive(packet);
               
                struct metaData dataToStore;

                // socketP->receive(packet);
                

                // vectorOfSockets[socketIndex]->receive(packet);
                if (packet >> dataToStore.xToPass >> dataToStore.yToPass >> dataToStore.commandToPass >> dataToStore.colorOfModificationToPass 
                >> dataToStore.canvasColorToPass >> dataToStore.sizeOfModification >> dataToStore.brushTypeModification >> dataToStore.windowXToPass >> 
                dataToStore.windowYToPass)
                {
                    dataToStore.socketIndex = socketIndex;
                    mtx.lock();
                    commandQueue.push(dataToStore);
                    m_cv.notify_one();
                    mtx.unlock();

                    // std::cout << "Server> Received PACKET FROM CLIENT: " << dataToStore.socketIndex << "\nX: "
                    //     << dataToStore.xToPass << "\nY: " << dataToStore.yToPass << "\nCommand: " << dataToStore.commandToPass << "\nColor: "
                    //     << dataToStore.colorOfModificationToPass << "\nCanvas Color: " << dataToStore.canvasColorToPass << "\nSize of Modifcation: "
                    //     << dataToStore.sizeOfModification << "\nBrush TYpe of Modification: " << dataToStore.brushTypeModification << "\nWindow X: "
                    //     << dataToStore.windowXToPass << "\nWindow Y: " << dataToStore.windowYToPass << "\nSize of Queue: " << commandQueue.size() << std::endl;
                    //callback funtion that would execute the commands and broadcast it
                    packet.clear();
                }
            }
        }

        void PicassoThreadFunction() {
            std::unique_lock<std::mutex> ul(mtx, std::defer_lock);
            while (true) {
                sf::Packet packet;
                ul.lock();
                if(commandQueue.empty()) {
                    m_cv.wait(ul, [this]{return !commandQueue.empty();});
                }

                struct metaData dataToProcess = commandQueue.front();
                commandQueue.pop();
                std::map<int, std::unique_ptr<sf::TcpSocket>>::iterator it = mapOfSocket.begin();
                

                for(it; it != mapOfSocket.end(); it++) {
                 if(dataToProcess.socketIndex != it->first) {
                    packet << dataToProcess.xToPass << dataToProcess.yToPass << dataToProcess.commandToPass << dataToProcess.colorOfModificationToPass
                            << dataToProcess.canvasColorToPass << dataToProcess.sizeOfModification << dataToProcess.brushTypeModification <<dataToProcess.windowXToPass << dataToProcess.windowYToPass;
                    it->second->send(packet);
                 } 
                }

                ul.unlock();
            }
        }
};


int main() {
    std::vector<std::thread> painterThreadVector;
    std::vector<std::unique_ptr<sf::TcpSocket>> socketVector;
    std::queue<metaData> commandQueue;
    // sf::Packet packet;
    
    sf::Socket::Status serverStatus;

    std::size_t received;

    sf::TcpListener listenerSocket;

    serverStatus = listenerSocket.listen(8081);

    // if(serverStatus != sf::Socket::Done) {
    //     std::cerr << "Error!" << serverStatus << std::endl;
    // }

    


    Painter painter;

    std::thread picassoThread(&Painter::PicassoThreadFunction, &painter);
    painterThreadVector.push_back(std::move(picassoThread));

    int index = 0;
    while(serverStatus == sf::Socket::Done){ //serverStatus != sf::Socket::Done 
        std::cout<<serverStatus<<std::endl;
        std::unique_ptr<sf::TcpSocket> socketToAdd = std::unique_ptr<sf::TcpSocket>(new sf::TcpSocket);
        // sf::TcpSocket serverSocket;
        listenerSocket.accept(*socketToAdd);
        // socketVector.push_back(std::move(socketToAdd));
        std::thread painterThread(&Painter::PainterThreadFunction, &painter,  std::move(socketToAdd), index);
        //  std::thread painterThread(&Painter::PainterThreadFunction, &painter, index);
        painterThreadVector.push_back(std::move(painterThread));
        index++;
    }
    return 0;
}

