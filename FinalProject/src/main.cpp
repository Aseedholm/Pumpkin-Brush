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
#include "time.h"
// Project header files
#include "Data.hpp"
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"
#include "Erase.hpp"
#include "Clear.hpp"
#include <SFML/OpenGL.hpp>


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

        switch(event.type) {
            case sf::Event::Closed :
                app.m_window->close();
                exit(EXIT_SUCCESS);
            case sf::Event::MouseButtonPressed :
                srand(time(nullptr));
                app.commandFlag = rand();
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::U:
                        app.undoCommand();
                        break;
                    case sf::Keyboard::R:
                        app.redoCommand();
                        break;
                    case sf::Keyboard::C:
                        if(app.m_prevCommand != app.commandEnum::CLEAR) {
                            Command* command = new Clear(&app, app.commandFlag);
                            app.addCommand(command);
                            app.m_prevCommand = app.commandEnum::CLEAR;
                            break;
                        }
                }

        }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
//            Command* command = new Clear(&app, app.commandFlag);
//            app.addCommand(command);
//        }
//        if(event.type == sf::Event::KeyPressed) {
//            if(event.key.code = sf::Keyboard::U) {
//                app.undoCommand();
//            }
//        }
	}

  
    app.m_gui->nk_input_begin_wrapper();
    while(app.m_gui->getWindow().pollEvent(event)) {
        // Our close event.
        // Note: We only have a 'minimize' button
        //       in our window right now, so this event is not
        //       going to fire.
        if(event.type == sf::Event::Closed){
            app.m_gui->nk_shutdown_wrapper();
            app.m_gui->getWindow().close();
            exit(EXIT_SUCCESS);
        }

            // Capture any keys that are released
        else if(event.type == sf::Event::KeyReleased){
            std::cout << "Key Pressed" << std::endl;
            // Check if the escape key is pressed.
            if(event.key.code == sf::Keyboard::Escape){
                app.m_gui->nk_shutdown_wrapper();
                app.m_gui->getWindow().close();
                exit(EXIT_SUCCESS);
            }
        }
        //else if(event.type == sf::Event::Resized){
        //    glViewport(0, 0, event.size.width, event.size.height);
        //}
        app.m_gui->nk_handle_event_wrapper(event);

    }
    app.m_gui->nk_input_end_wrapper();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i coordinate = sf::Mouse::getPosition(app.getWindow());

			sf::Vector2f currentXYCoordinates = app.m_window->mapPixelToCoords(coordinate); //andrew edit ****
            // double xToPass = 0.0;
            // double yToPass = 0.0;
            sf::Uint32 xToPass = 0;
            sf::Uint32 yToPass = 0;
            std::string commandToPass;
            std::string brushSize;
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
			    if (app.onErase) {
			        Command* command = new Erase(currentXYCoordinates, &app, app.commandFlag);
                    app.addCommand(command);
                    app.m_prevCommand = app.commandEnum::ERASE;

			    }
			    // else, simple mouse event for drawing
			    else {
                    std::cout << currentXYCoordinates.x << " " << currentXYCoordinates.y << std::endl;
                    xToPass = currentXYCoordinates.x;
                    yToPass = currentXYCoordinates.y;

                    commandToPass = "draw";
                    commandToPass.append(std::to_string(counter));
                    counter++;

                    //brushSize = app.GetBrush().getSize();
                    packet << xToPass << yToPass << commandToPass;
                    clientSocket.send(packet);
                    packet.clear();

                    Command* command = new Draw(currentXYCoordinates, &app, app.commandFlag);
                    app.addCommand(command);
                    app.m_prevCommand = app.commandEnum::DRAW;

			    }
			}
			// Modify the pixel
			// App::getImage().setPixel(coordinate.x,coordinate.y,sf::Color::Red);
		}


//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
//        app.undoCommand();
//    }

//	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
//        app.redoCommand();
//    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        exit(EXIT_SUCCESS);
    }

    // Handling change color event
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        app.getBrush().setColor(sf::Color::Black);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        app.getBrush().setColor(sf::Color::White);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        app.getBrush().setColor(sf::Color::Red);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        app.getBrush().setColor(sf::Color::Green);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
        app.getBrush().setColor(sf::Color::Blue);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
        app.getBrush().setColor(sf::Color::Yellow);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
        app.getBrush().setColor(sf::Color::Magenta);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
        app.getBrush().setColor(sf::Color::Cyan);
    }

    // Handling change size of drawing tool
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
        app.getBrush().setSize(size::small);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
        app.getBrush().setSize(size::medium);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) {
        app.getBrush().setSize(size::large);
    }

    // Handling change drawing tools
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Divide)) {
        app.setBrush(app.getBrushFactory().createBrush(2));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply)) {
        app.setBrush(app.getBrushFactory().createBrush(1));
    }


    // only for debug and test
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        std::cout << app.commandFlag << std::endl;
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
    // clientSocket.setBlocking(false);
    //Testing data class. 
    std::string stringToPass = "Erase";
    // Data data1;
    Data data1(1, 1, 5555555, stringToPass, 5, 5);
    data1.printData();
    //Testing data class. 
    

    char buffer[1000];
    memset(buffer, 0, 1000);
    std::size_t received;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    status = clientSocket.connect(ip, 8080);
    if(status != sf::Socket::Done) {
        std::cerr << "Error!" << status << std::endl;
    }
    std::string text = "Client connected to Server";
    clientSocket.send(text.c_str(), text.length() +1);
    clientSocket.receive(buffer, sizeof(buffer), received);
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

