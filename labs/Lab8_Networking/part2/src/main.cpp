/** 
 *  @file   main.cpp 
 *  @brief  Entry point into the program.
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

// g++ -std=c++17 *.cpp -o App -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
//
// Note:	If your compiler does not support -std=c++17, 
//		then try -std=c++14 then -std=c++11.
//		
// HOW TO RUN
//
// ./App

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Network.hpp>             
// Include standard library C++ libraries.
#include <iostream>
#include <string>
#include <map>
#include <string.h> // for memset
// Project header files
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"


/*! \brief 	Call any initailization functions here.
*		This might be for example setting up any
*		global variables, allocating memory,
*		dynamically loading any libraries, or
*		doing nothing at all.
*		
*/
void initialization(void){
	std::cout << "Starting the App" << std::endl;
}

/*! \brief 	The update function presented can be simplified.
*		I have demonstrated two ways you can handle events,
*		if for example we want to add in an event loop.
*		
*/
void update(void){
	// Update our canvas
	sf::Event event;
	while(App::m_window->pollEvent(event)){
		if(event.type == sf::Event::MouseMoved){				
			// Modify the pixel
			App::mouseX = event.mouseMove.x; 
			App::mouseY = event.mouseMove.y; 
			App::GetImage().setPixel(App::mouseX,App::mouseY,sf::Color::Blue);
		}
	}

	// We can otherwise handle events normally
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		sf::Vector2i coordinate = sf::Mouse::getPosition(App::GetWindow());
		std::cout << "Hmm, lots of repeats here: " << coordinate.x << "," << coordinate.y << std::endl;
		// Modify the pixel
		App::GetImage().setPixel(coordinate.x,coordinate.y,sf::Color::Red);
	}
	// Capture any keys that are released
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		exit(EXIT_SUCCESS);
	}
	
	// Where was the mouse previously before going to the next frame
	App::pmouseX = App::mouseX;
	App::pmouseY = App::mouseY;
}


/*! \brief 	The draw call 
*		
*/
void draw(void){
	// Static variable 
	static int refreshRate = 0;
	++refreshRate;	// Increment 


	// We load into our texture the modified pixels	
	// But we only do so every 10 draw calls to reduce latency of transfer
	// between the GPU and CPU.
	// Ask yourself: Could we do better with sf::Clock and refresh once
	// 	 	 every 'x' frames? 
	if(refreshRate>10){
		App::GetTexture().loadFromImage(App::GetImage());	
		refreshRate =0;
	}
}


void LaunchUDPServer(){
    // Runs on local network
    // sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    // Setup a socket for a UDP connection
    // A UDP Socket is connectionless
    sf::UdpSocket socket;
    std::size_t received;
    char buffer[2000];
    memset(buffer,0,2000);
    // A map data structure stores all of the client connections to the server.
    std::map<unsigned short, sf::IpAddress> computerID; // <port#,ipaddress>
    
    // We need a 'port' number for our server.
    // Multiple computers can have the same port, but would need to be
    // on different ip addresses. Simiilarly, we could have connections
    // to the same ip addresse but need a different port.
    unsigned short port;
    std::cout << "Set port number: ";
    std::cin >> port;
    std::cout << "Confirming server port number as: " << port << std::endl;

    // Listening to a port
    socket.bind(port);
    // By default socket is blocking, and thus
    // waiting to receive some data.
    socket.setBlocking(true);

    std::cout << "============Starting UDP Server==========" << std::endl;
    std::cout << "Server awaiting first client connection(s)" << std::endl;
    char start = 'n';
    while(start=='n'){
        // We are going to store any clients that connect to our
        // server. 
        // A connection consists of an ip address and a port.
        // (ip:port)
        sf::IpAddress connectingClientIP;
        unsigned short port;
        // When a connection is made to our server, we get some amount of bytes
        // We store the clients ip and port that is connected
        socket.receive(buffer,sizeof(buffer),received,connectingClientIP,port);
        // Again, if we successfully receive some amount of bytes, then
        // we will store this in our internal map data structure.
        // Storing all of these ip:ports allow us to then broadcast messages
        // out to all of our clients from our server.
        if(received > 0){
            std::cout   << "Client joining:"
                        << connectingClientIP 
                        << ":"
                        << port 
                        << std::endl; 
            computerID[port] = connectingClientIP; 
        }
        std::cout << "Start server? (y/n):";
        std::cin >> start;
    }
    std::cout << "\nUDP Server Launched with " << computerID.size() << " clients\n\n";

    // Main UDP Server Loop
    //
    std::string text = "Connected to: ";
    while(true){
        std::cout << "server>";
        std::getline(std::cin, text);
        std::map<unsigned short, sf::IpAddress>::iterator ipIterator;
        for(ipIterator = computerID.begin(); ipIterator != computerID.end(); ipIterator++){
            socket.send(text.c_str(),text.length()+1, ipIterator->second, ipIterator->first);
        }
    }
}

void LaunchUDPClient(){
    std::cout << "============Initiating UDP Client==========" << std::endl;
    // Setup a socket for a UDP connection
    // A UDP Socket is connectionless
    sf::UdpSocket socket;
    // Buffer will hold messages that can be received
    char buffer[2000];
    memset(buffer,0,2000);
    std::size_t received;
    std::string text = "Connected to: ";
    // Multiple computers can have the same port
    // However, the IP addresses would need to be different.
    unsigned short port;
    std::cout << "Set port number: ";
    std::cin >> port;
    std::cout << "Confirming port number as: " << port << std::endl;
    
    // Listening to a port
    socket.bind(port);
    // By default socket is blocking, and thus
    // waiting to receive some data.
    socket.setBlocking(true);

    std::string serverIP;
    std::cout << "Enter server ip: ";
    // Note, you may want to make this value more private
    // for testing this is fine however.
    // Note we use 'getline' to avoid storing a '\n' mark
    // at the end of the serverIP string.
    std::getline(std::cin,serverIP);
    
    sf::IpAddress sendIP(serverIP);
    if(socket.send(text.c_str(), text.length()+1, sendIP, 2000) != sf::Socket::Done){
        std::cout << "Client error? Wrong IP?" << std::endl; 
    }else{
        std::cout << "Client connecting--awaiting server start" << std::endl;
    }

    // Main UDP loop
    while(true){
        std::cout << "client>";
        sf::IpAddress tempIp;
        unsigned short tempPort;
        socket.receive(buffer,sizeof(buffer),received,tempIp,tempPort);
        if(received > 0){
            std::cout << "Received: " << buffer << std::endl;
        } 
    }
}


// This is an example of a UDP Network using the SFML Library.
// A UDP Network is an unreliable network protocol, meaning that
// the data is not gaureenteed to be sent to a remote machine.
// However, when data is sent, it will not be corrupted.
// UDP sends data in what are known as 'datagrams' which are
// 'packets' of information that cannot be mixed together.
void UDPnetwork(){
    // Stores a role of either a server or client user.
    std::string role;    

    // Set the role
    std::cout << "Enter (s) for Server, Enter (c) for client: " << std::endl;
    std::cin >> role;

    // The std::cin function records the '\n' character,
    // so I instead just look at the first character of
    // the user input.
    // A 'trim' function may be more ideal.
    if(role[0] == 's'){
        LaunchUDPServer();
    }else if(role[0] == 'c'){
        LaunchUDPClient();
    }

}




 
/*! \brief 	The entry point into our program.
*		
*/
int main(){
   
    // TCPnetwork(); 

    // Run the UDP network code
    UDPnetwork();

    // Call any setup function
	// Passing a function pointer into the 'init' function.
	// of our application.
	App::Init(&initialization);
	// Setup your keyboard
	App::UpdateCallback(&update);
	// Setup the Draw Function
	App::DrawCallback(&draw);
	// Call the main loop function
	App::Loop();
	// Destroy our app
	App::Destroy();

	return 0;
}

