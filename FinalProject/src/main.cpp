/**
 *  @file   main.cpp
 *  @brief  Entry point into the program.
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/

 // g++ -std=c++17 *.cpp -o App -lsfml-graphics -lsfml-window -lsfml-system
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
#include <string.h> // memset
// Project header files
#include "Data.hpp"
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"
#include "Erase.hpp"

//Networking
sf::TcpSocket clientSocket;
sf::Socket::Status status;
sf::Packet packet;

int counter = 0;

/*! \brief 	Call any initailization functions here.
*		This might be for example setting up any
*		global variables, allocating memory,
*		dynamically loading any libraries, or
*		doing nothing at all.
*
*/
void initialization(void) {
	std::cout << "Starting the App" << std::endl;
}

/*! \brief 	The update function presented can be simplified.
*		I have demonstrated two ways you can handle events,
*		if for example we want to add in an event loop.
*
*/
void update(App& app) {
	// Update our canvas
	sf::Event event;
	while (app.m_window->pollEvent(event)) {
        //andrew edit ****
        //closing the window by clicking the x button (japher edit ***)
        if (event.type == sf::Event::Closed) {
            app.m_window->close();
            exit(EXIT_SUCCESS);
        }
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i coordinate = sf::Mouse::getPosition(app.getWindow());

			sf::Vector2f currentXYCoordinates = app.m_window->mapPixelToCoords(coordinate); //andrew edit ****


            //Need to send x, y location for pixel modification, 
            //command being done, 
            //brush color at time of modification, 
            //canvas color at time of modifcation,
            //brush size at time of mdofication, 
            //brush type (pen or brush) at time of modification, 
            //window x at time of modification, 
            //window y at time of modification. 
            

            sf::Uint32 xToPass = 0;
            sf::Uint32 yToPass = 0;
            std::string commandToPass;
            sf::Uint32 colorOfModificationToPass = 0;
            sf::Uint32 canvasColorToPass = 0;
            sf::Uint32 sizeOfModification = 0; //flag to send to server that'll be sent to other clients to determine GeneralBrush enum size. 
            sf::Uint32 brushTypeModification = 0; //flag to send to server that'll be sent to other clients to determine if it is a Pen or Brush being used to draw. 
            sf::Uint32 windowXToPass = 0;
            sf::Uint32 windowYToPass = 0;

			//relative positioning and resizing the window
			// store the mouse position of the current frame
			app.mouseX = currentXYCoordinates.x;
			app.mouseY = currentXYCoordinates.y;


			if(app.mouseX == app.pmouseX && app.mouseY == app.pmouseY){
			    //std::cout << "Clicking the same pixel, do not execute commands" << std::endl;
			}
			else if (currentXYCoordinates.x > 0 && currentXYCoordinates.x <= app.getWindow().getSize().x
			&& currentXYCoordinates.y > 0 && currentXYCoordinates.y <= app.getWindow().getSize().y) {
			    // if mouse is left-clicked AND key E is pressed, execute the pixel
			    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			        Command* command = new Erase(currentXYCoordinates, &app);
                    app.addCommand(command);
			    }
			    // else, simple mouse event for drawing
			    else {
                    // std::cout << currentXYCoordinates.x << " " << currentXYCoordinates.y << std::endl;
                    xToPass = currentXYCoordinates.x;
                    yToPass = currentXYCoordinates.y;

                    commandToPass = "draw ";
                    commandToPass.append(std::to_string(counter));
                    counter++;

                    colorOfModificationToPass = app.GetBrush().getColor().toInteger();
                    canvasColorToPass = app.getBackgroundColor().toInteger();

                    sizeOfModification = app.GetBrush().getSize(); //When implemented will reflect brush size relating to enum, flags can be 0 = small, 1 = medium, 2 = large. 
                    brushTypeModification = app.GetBrush().getType(); //flag could be  0 = brush, 1 = pen. 
                    windowXToPass = app.getWindow().getSize().x;
                    windowYToPass = app.getWindow().getSize().y;
                    std::cout << "Client Sent PACKET: \nX: " << xToPass << "\nY: " << yToPass << "\nCommand: " << commandToPass <<"\nColor: " << colorOfModificationToPass << "\nCanvas Color: " << canvasColorToPass << "\nSize of Modifcation: " << sizeOfModification << "\nBrush TYpe of Modification: " << brushTypeModification << "\nWindow X: " << windowXToPass << "\nWindow Y: " << windowYToPass <<std::endl;
                    // brushSize = app.GetBrush().getSize();
                    packet << xToPass << yToPass << commandToPass << colorOfModificationToPass << canvasColorToPass << sizeOfModification << brushTypeModification << windowXToPass << windowYToPass;
                    clientSocket.send(packet);
                    packet.clear();

                    Command* command = new Draw(currentXYCoordinates, &app);
                    app.addCommand(command);
			    }
			}
			// Modify the pixel
			// App::getImage().setPixel(coordinate.x,coordinate.y,sf::Color::Red);
		}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
        app.undoCommand();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        app.redoCommand();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        exit(EXIT_SUCCESS);
    }


    // Handling change color event
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        app.GetBrush().setColor(sf::Color::Black);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        app.GetBrush().setColor(sf::Color::White);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        app.GetBrush().setColor(sf::Color::Red);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        app.GetBrush().setColor(sf::Color::Green);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
        app.GetBrush().setColor(sf::Color::Blue);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
        app.GetBrush().setColor(sf::Color::Yellow);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
        app.GetBrush().setColor(sf::Color::Magenta);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
        app.GetBrush().setColor(sf::Color::Cyan);
    }

    // Handling change size of drawing tool
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
        app.GetBrush().setSize(size::small);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
        app.GetBrush().setSize(size::medium);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
        app.GetBrush().setSize(size::large);
    }

    // Handling change drawing tools
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Divide)) {
        app.SetBrush(app.getBrushFactory().createBrush(2));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply)) {
        app.SetBrush(app.getBrushFactory().createBrush(1));
    }


    // only for debug and test
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        app.GetBrush().getSize();
    }






	if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        app.setBackgroundColor(new sf::Color(sf::Color::Blue.toInteger()));
    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        app.setBackgroundColor(new sf::Color(sf::Color::White.toInteger()));
    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
        app.setBackgroundColor(new sf::Color(sf::Color::Yellow.toInteger()));
    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
        app.setBackgroundColor(new sf::Color(sf::Color::Green.toInteger()));
    }


    // Stores the previous mouse click position before going to next frame
    app.pmouseX = app.mouseX;
    app.pmouseY = app.mouseY;
}


/*! \brief 	The draw call
*
*/
void draw(App& app) {
	// Static variable
	static int refreshRate = 0;
	++refreshRate;	// Increment

	// We load into our texture the modified pixels
	// But we only do so every 10 draw calls to reduce latency of transfer
	// between the GPU and CPU.
	// Ask yourself: Could we do better with sf::Clock and refresh once
	// 	 	 every 'x' frames?
	if (refreshRate > 10) {
        app.getTexture().loadFromImage(app.getImage());
		refreshRate = 0;
	}
}


/*! \brief 	The entry point into our program.
*
*/
int main() {
    // // clientSocket.setBlocking(false);
    // //Testing data class. 
    // std::string stringToPass = "Erase";
    // // Data data1;
    // Data data1(1, 1, 5555555, stringToPass, 5, 5);
    // data1.printData();
    // //Testing data class. 
    

    char buffer[1000];
    memset(buffer, 0, 1000);
    std::size_t received;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    status = clientSocket.connect(ip, 8080);
    if(status != sf::Socket::Done) {
        std::cerr << "Error!" << status << std::endl;
    }
    std::string text = "Client connected to Server";
    // clientSocket.send(text.c_str(), text.length() +1);
    // clientSocket.receive(buffer, sizeof(buffer), received);
    std::cout << "Client> " << buffer << std::endl;
    // char mode = 's';
    // bool done = false
    //Networking

	App app;
	// Call any setup function
	// Passing a function pointer into the 'init' function.
	// of our application.
    app.init(&initialization);
	// Setup your keyboard
    app.updateCallback(&update);
	// Setup the Draw Function
    app.drawCallback(&draw);
	// Call the main loop function
    app.loop(app);
	// destroy our app
    app.destroy();

	return 0;
}

