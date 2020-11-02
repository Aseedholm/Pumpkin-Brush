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






// TCP Server
void TCPServer(){
    std::cout << "============Starting TCP Server==========" << std::endl;
    // A socket is an endpoint for which we can send and receive data.
	sf::TcpSocket socket;
    // Status
    sf::Socket::Status status;
    // Buffer will hold messages that can be received
    char buffer[2000];
    memset(buffer,0,2000);
    
    std::size_t received;
    
    // Figure out our ip address on this machine.
    // For now just use the local address 127.0.0.1
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
   
    
    sf::TcpListener listener;
    // Note:    I have picked the port '2000' at random
    //          if for some reason this program does not work
    //          you may need to choose a different value or
    //          disable your firewall.
    status = listener.listen(2000);  
    if(status != sf::Socket::Done){
        std::cerr << "Error!" << status << std::endl;
    }

    // The accept function is blocking until
    // a connection arrives.
    // When a client connection arrives, we will then
    // be able to proceed forward
    listener.accept(socket);
    
    // Now we will send some data to our newly connected
    // client socket.
    // Let's send some text data
    std::string text = "Connected to Server";
    socket.send(text.c_str(),text.length()+1);
    // Proceed forward once we have successfully 
    // sent our message. This means we are 'blocked'
    socket.receive(buffer,sizeof(buffer),received);
    std::cout << "server> Received: " << buffer << std::endl;

    char mode = 'r'; // By default our server only listens to client connections
    bool done = false;
    while(!done){
        /*if(mode=='s'){
            std::cout << "(me) Server>";
            std::getline(std::cin,text);
            socket.send(text.c_str(),text.length()+1);
            mode = 'r';
        }
        else*/ if(mode=='r'){
            socket.receive(buffer, sizeof(buffer), received);
            if(received > 0){
                std::cout << "From Client> " << buffer << std::endl;
             //   mode = 's';
            }
        } 
    }

}

// TCP Client
void TCPClient(){
    std::cout << "============Initiating TCP Client==========" << std::endl;
    // A socket is an endpoint for which we can send and receive data.
	sf::TcpSocket socket;
    // Status
    sf::Socket::Status status;
    // Buffer will hold messages that can be received
    char buffer[2000];
    memset(buffer,0,2000);
    std::size_t received;

    // Figure out our ip address on this machine.
    // For now just use the local address 127.0.0.1
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
   
    // We attempt to connect to a server at a designated ip
    // and a specific port.
    // Note:    I have picked the port '2000' at random
    //          if for some reason this program does not work
    //          you may need to choose a different value or
    //          disable your firewall.
    status = socket.connect(ip, 2000);
    if(status != sf::Socket::Done){
        std::cerr << "Error!" << status << std::endl;
    }

    std::string text = "Client connected to Server"; 
    socket.send(text.c_str(),text.length()+1);
    socket.receive(buffer,sizeof(buffer),received);
    std::cout << "Client> " << buffer << std::endl;

    char mode = 's'; // By default our client only sends messages
    bool done = false;
    while(!done){
        if(mode=='s'){
            std::cout << "(me) Client>";
            std::getline(std::cin,text);
            socket.send(text.c_str(),text.length()+1);
        //    mode = 'r';
        }
        /*else if(mode=='r'){
            socket.receive(buffer, sizeof(buffer), received);
            if(received > 0){
                std::cout << "From Server> " << buffer << std::endl;
                mode = 's';
            }
        } */
    }
}


// This example is of a TCP Network using the SFML Library.
// A TCP Network is a reliable protocol for sending messages between
// a machine that you are connected to. TCP is a streaming protocol
// which transports data to a remote machine as it can.
void TCPnetwork(){
    // Store the role as either a client or server
    std::string role = "undefined";
    
    // User input
    std::cout << "Enter (s) for server, enter (c) for client" << std::endl;
    std::cin >> role;

    // The std::cin function records the '\n' character,
    // so I instead just look at the first character of
    // the user input.
    // A 'trim' function may be more ideal.
    if(role[0] == 's'){
        TCPServer();    
    }else if(role[0] == 'c'){
        TCPClient();
    }

}



 
/*! \brief 	The entry point into our program.
*		
*/
int main(){
   
    // Run the TCP Network code
    TCPnetwork(); 
    
    // UDPnetwork();

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

