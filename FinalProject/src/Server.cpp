/**
 *  @file   Server.cpp
 *  @brief  Server that will receive commands from Clients and send commands to Clients allowing concurrently operations on multiple canvases.
 *  @author Jugal Joshi and Andrew Seedholm
 *  @date   2020-07-12
 ***********************************************/
#include <SFML/Network.hpp>
#include <string.h> // memset
#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <map>
#include <condition_variable>


/*! \brief 	This struct represents meta data that will be sent to and from the server. It will be used to pack into
* the SFML API's Packet class and also to unpack that same data. 
*/
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

/*! \brief 	This class represents the operations the threads in the main function of Server.cpp will execute.
*/
class Painter {
    private:
        std::mutex mtx;
        std::mutex map_mtx;
        std::queue<metaData>commandQueue;
        std::vector<std::unique_ptr<sf::TcpSocket>> vectorOfSockets;
        std::map<int, std::unique_ptr<sf::TcpSocket>> mapOfSocket;
        std::condition_variable m_cv;

            public : 
            /*! \brief 	The PainterThreadFunction represents the function the painterThread will execute. It will allow a painterThread to 
            * enqueue command information into a queue and then notify the picassoThread that it needs to send that command to the relevant 
            * clients. 
            * 
            * @param socketP a unique-pointer representing a TcpSocket from the SFML library, this is the socket the thread will use to receive information, it will be stored in a map with the socketIndex as the key. 
            * @param socketIndex the key within the map that will have the socketP as the value. 
            */
            void PainterThreadFunction(std::unique_ptr<sf::TcpSocket> socketP, int socketIndex)
        {

            map_mtx.lock();
            mapOfSocket.insert({socketIndex, std::move(socketP)});
            map_mtx.unlock();
            sf::Packet packet;
          
            while (true)
            {
                mapOfSocket.find(socketIndex)->second->receive(packet);
               
                struct metaData dataToStore;

                if (packet >> dataToStore.xToPass >> dataToStore.yToPass >> dataToStore.commandToPass >> dataToStore.colorOfModificationToPass 
                >> dataToStore.canvasColorToPass >> dataToStore.sizeOfModification >> dataToStore.brushTypeModification >> dataToStore.windowXToPass >> 
                dataToStore.windowYToPass)
                {
                    dataToStore.socketIndex = socketIndex;
                    mtx.lock();
                    commandQueue.push(dataToStore);
                    m_cv.notify_one();
                    mtx.unlock();
                    packet.clear();
                }
            }
        }
        /*! \brief 	The PicassoThreadFunction represents the function that the picassoThread will execute. This function will be notified
        * by the PainterThreadFunction that it needs to execute. It dequeues information from the shared queue and sends it to the relevant clients. 
        */
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

/*! \brief 	The entry point into our program.
*
*/
int main(int argc, char* argv[]) {
    std::vector<std::thread> painterThreadVector;
    std::vector<std::unique_ptr<sf::TcpSocket>> socketVector;
    std::queue<metaData> commandQueue;
    // sf::Packet packet;
    
    sf::Socket::Status serverStatus;

    std::size_t received;

    sf::TcpListener listenerSocket;
    if(argc<2){
        std::cout << "Please enter the port number. For example: ./Server 8080" << std::endl;
        return 0;
    }
    int port = atoi(argv[1]);
    serverStatus = listenerSocket.listen(port);


    Painter painter;

    std::thread picassoThread(&Painter::PicassoThreadFunction, &painter);
    painterThreadVector.push_back(std::move(picassoThread));

    int index = 0;
    while(serverStatus == sf::Socket::Done){
        std::unique_ptr<sf::TcpSocket> socketToAdd = std::unique_ptr<sf::TcpSocket>(new sf::TcpSocket);
        listenerSocket.accept(*socketToAdd);
        std::thread painterThread(&Painter::PainterThreadFunction, &painter,  std::move(socketToAdd), index);
        painterThreadVector.push_back(std::move(painterThread));
        index++;
    }
    return 0;
}

