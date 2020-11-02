/** 
 *  @file   main.cpp 
 *  @brief  Entry point into the program.
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

// g++ -std=c++17 *.cpp -o App -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
//
// Note:    If your compiler does not support -std=c++17, 
//      then try -std=c++14 then -std=c++11.
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
#include "UDPNetworkServer.hpp"
#include "UDPNetworkClient.hpp"

/*! \brief  Call any initailization functions here.
*       This might be for example setting up any
*       global variables, allocating memory,
*       dynamically loading any libraries, or
*       doing nothing at all.
*       
*/
void initialization(void){
    std::cout << "Starting the App" << std::endl;
}

/*! \brief  The update function presented can be simplified.
*       I have demonstrated two ways you can handle events,
*       if for example we want to add in an event loop.
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


/*! \brief  The draw call 
*       
*/
void draw(void){
    // Static variable 
    static int refreshRate = 0;
    ++refreshRate;  // Increment 


    // We load into our texture the modified pixels 
    // But we only do so every 10 draw calls to reduce latency of transfer
    // between the GPU and CPU.
    // Ask yourself: Could we do better with sf::Clock and refresh once
    //       every 'x' frames? 
    if(refreshRate>10){
        App::GetTexture().loadFromImage(App::GetImage());   
        refreshRate =0;
    }
}



 
/*! \brief  The entry point into our program.
*       
*/
int main(){
   

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
	    UDPNetworkServer server("Server Name",sf::IpAddress::getLocalAddress(),50000);
		// Create a server 
		// Run the server on local network for now
		server.start();
    }else if(role[0] == 'c'){
		// Create a client and have them join
        std::string uname;
        unsigned short port;
        std::cout << "Enter your username:";
        std::cin >> uname;
        std::cout << "Which port will you try? (e.g. 50001-50010):";
        std::cin >> port;
        // FIXME Ideally in a real world application, a client would
        // never have to 'guess' which ports are open on a server.
        // One could improve this code by communicating with the server
        // what ports are 'open' for connection in the 'joinServer' function.
        // For now, we will create clients that can simply join however!
	    UDPNetworkClient me(uname,port);
		
        me.joinServer(sf::IpAddress::getLocalAddress(),50000);
        me.setUsername(uname);
        me.sendString("Hello, "+uname+" is joining!");

        // Loop our client forever
		while(true){
			me.receiveData();
		}
    }



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

