#include "UDPNetworkClient.hpp"
#include "Draw.hpp"

#include <iostream>

// Default Constructor
// In our constructor, we will want to setup our clients
// 1.) username
// 2.) port
//
// Then we will bind a socket to this port for which we will
// communicate over.
//
// Our UDPNetworkClient will be non-blocking by default
UDPNetworkClient::UDPNetworkClient(std::string username, unsigned short port){
    m_username = username;
	m_port = port;
    // Setup a socket for a UDP connection
    // Multiple computers can have the same port
    // However, the IP addresses would need to be different.
    // Listening to a port
    m_socket.bind(m_port);
    // By default socket is non-blocking
    m_socket.setBlocking(false);
}

// Default Destructor
UDPNetworkClient::~UDPNetworkClient(){
    std::cout << "Client destructor called" << std::endl;
}

// Join a server
// For this function, we will setup the server for which we will attempt to communicate
// Since this is a UDP network, we will keep things quite simple, meaning
// we will not do any error checking to see if the server even exists.
// We simply try to send messages to a server.
int UDPNetworkClient::joinServer(sf::IpAddress serverAddress, unsigned short serverPort){
    std::cout << "UDPClient will attemp to join server: " << std::endl;
    m_serverIpAddress = serverAddress;
    m_serverPort = serverPort;
}

// Send data to server
// Now is the fun part, for which we will attempt to send
// some data to the UDPNetworkServer.
//
// In this example, we will try to send over commands.
int UDPNetworkClient::sendCommand(Command* c){
	/*myPacket p;
	p.m_client = m_username;
	p.m_command = c;

	std::cout << "Packet Data:" << m_username << std::endl;

    if(m_socket.send(p, m_ipAddress, m_port) == sf::Socket::Done){
        std::cout << "Client error? Wrong IP?" << std::endl; 
    }else{
        std::cout << "Client(" << m_username << ") sending packet" << std::endl;
    }
*/
    return 0;
}

// Send 'string' data to server
// As an alternative, we may want to send string messages to the server.
// This can be a quick way to log, or perhaps 'chat' with the server
int UDPNetworkClient::sendString(std::string s){
    if(s.length() <= 0){
        return -1;
    }
    // Here we send a specific string
    // Let's keep things interesting by forcing the client to
    // append their user name to the message they send.
    s+= " (from "+ m_username+")";

    // Note that we are sending this message to our server:serverPort
    // Note that we add 1 more charater for the NULL terminator on our string
    if(m_socket.send(s.c_str(),s.length()+1, m_serverIpAddress, m_serverPort) == sf::Socket::Done){
        std::cout << "Client(" << m_username << ") sending packet" << std::endl;
    }

}


// Receive data from the server
//
// As a client, we will receive data from our server.
// Clients can send '2' types of messages to server given our API.
// One type is a string, the other is our custom packet.
// We will handle both.
//
// FIXME Depending on how you want to handle returning of data
// you can modify the return type.
void /*myPacket*/ UDPNetworkClient::receiveData(){
    // 1.) Situation 1 -- we receive a packet from sendCommand
    // Create a temporary packet and see
    // if something was received from our server
    //myPacket temp;
    //std::string client;
    //Command* c;
	//if(temp.getDataSize()>0){
    //    std::cout << "Some Custom packet receieved from:" << client << std::endl;
    //    return temp;
    //} 

    // 2.) Situation 2 -- we receive a string from sendString
    // This situation is a little bit simpler, in that we can
    // received a fixed size message from the server.
    // For now '128' is a magic number FIXME and make me something configurable
    // :)
	char in[128];
    size_t received;
    sf::IpAddress copyAddress = m_serverIpAddress;
    unsigned short copyPort = m_serverPort;
	if(m_socket.receive(in,sizeof(in),received,copyAddress,copyPort) == sf::Socket::Done){
        if(received >0){
	        std::cout << "From Server: " << in << std::endl;
        }
	}
	
}

// Return our username
std::string UDPNetworkClient::getUsername(){
    return m_username;
}

// Set our username
int UDPNetworkClient::setUsername(std::string name){
    m_username = name;
}

