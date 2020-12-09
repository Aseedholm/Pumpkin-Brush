/**
 *  @file   main.cpp
 *  @brief  Entry point into the program.
 *  @author Mike, Japher Su, Jugal Joshi, Hao Zheng, and Andrew Seedholm
 *  @date   2020-07-12
 ***********************************************/

 // Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Network.hpp>
// Include standard library C++ libraries.


#include <iostream>
#include <ostream>
#include <string>
#include <string.h> // memset
#include "time.h"
// Project header files
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"
#include "Erase.hpp"
#include "Brush.hpp"
#include "Pen.hpp"
#include "Clear.hpp"
#include <SFML/OpenGL.hpp>


//Networking
sf::TcpSocket clientSocket;
sf::Socket::Status status;
sf::Packet packet;

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

/*! \brief 	The remoteDraw function allows a Client to draw locally the received draw 
* commands from the Server representing draw commands sent from a different client. 
* @param app an App object that allows us to execute draw commands outside of the update loop.
* @param xToPass a sf::Uint32 variable representing the x coordinate for where the remote draw command took place. 
* @param yToPass a sf::Uint32 variable representing the y coordinate for where the remote draw command took place. 
* @param colorOfModification a sf::Uint32 variable representing the color drawn where the remote draw command took place.
* @param sizeOfModification a sf::Uint32 variable representing the size of the brush(or pen) where the remote draw command took place (small, medium, or large).
* @param brushTypeOfModification a sf::Uint32 variable representing the brush type (brush or pen) for where the remote draw command took place.
*/
void remoteDraw(App& app, sf::Uint32 xToPass, sf::Uint32 yToPass, sf::Uint32 colorOfModification, sf::Uint32 sizeOfModification, sf::Uint32 brushTypeOfModification){

    GeneralBrush& temp = app.getBrush();
    

    if(brushTypeOfModification == 0) { //brush
        Brush* networkBrush = new Brush();

        networkBrush->setColor(sf::Color(colorOfModification));

        if(sizeOfModification == 0) {
            size small = size::small;
            networkBrush->setSize(small);
        } else if(sizeOfModification == 1) {
            size medium = size::medium;
            networkBrush->setSize(medium);
        } else if(sizeOfModification == 2) {
            size large = size::large;
            networkBrush->setSize(large);
        }
        app.setBrush(networkBrush);

        sf::Vector2f passedXY{static_cast<float>(xToPass), static_cast<float>(yToPass)};


        srand(time(nullptr));

        Command* command = new Draw(passedXY, &app, rand(), "draw");

        app.addCommand(command);

        delete networkBrush;

        app.setBrush(&temp);
    } 



    else if(brushTypeOfModification == 1) { //pen
        Pen* networkPen = new Pen();
        networkPen->setColor(sf::Color(colorOfModification));

        if(sizeOfModification == 0) {
            size small = size::small;
            networkPen->setSize(small);
        } else if(sizeOfModification == 1) {
            size medium = size::medium;
            networkPen->setSize(medium);
        } else if(sizeOfModification == 2) {
            size large = size::large;
            networkPen->setSize(large);
        }
        app.setBrush(networkPen);

        sf::Vector2f passedXY{static_cast<float>(xToPass), static_cast<float>(yToPass)};

        srand(time(nullptr));

        Command* command = new Draw(passedXY, &app, rand(), "draw");

        app.addCommand(command);

        delete networkPen;

        app.setBrush(&temp);
    }
}

/*! \brief 	The packetReceiver function uses the socket with in App close to receive information from the server
* then controls the work flow based on the unpacked command received from the server. 
* @param app an App object that allows us to receive packets from the Server as well as execute various commands based on 
*            the received information. 
*/
void packetReceiver(App& app) {
    metaData dataToWrite;

    app.clientSocketInApp.receive(packet);

    if(packet >> dataToWrite.xToPass >> dataToWrite.yToPass >> dataToWrite.commandToPass 
    >> dataToWrite.colorOfModificationToPass >> dataToWrite.canvasColorToPass >> dataToWrite.sizeOfModification 
    >> dataToWrite.brushTypeModification >> dataToWrite.windowXToPass >> dataToWrite.windowYToPass) {

        packet.clear();
        if(dataToWrite.commandToPass.compare("draw") == 0){
            remoteDraw(app, dataToWrite.xToPass, dataToWrite.yToPass, dataToWrite.colorOfModificationToPass, dataToWrite.sizeOfModification, dataToWrite.brushTypeModification);
        } else if (dataToWrite.commandToPass.compare("erase") == 0) {
            sf::Vector2f passedXY{static_cast<float>(dataToWrite.xToPass), static_cast<float>(dataToWrite.yToPass)};
            srand(time(nullptr));
            Command* command = new Erase(passedXY, &app, rand(), "erase");
            app.addCommand(command);
        } else if(dataToWrite.commandToPass.compare("clear") == 0) {
            srand(time(nullptr));
            Command *command = new Clear(&app, rand(), "clear");
            app.addCommand(command);
            app.m_prevCommand = app.commandEnum::CLEAR;
        } else if(dataToWrite.commandToPass.compare("backgroundChange") == 0) {
            app.setBackgroundColor(new sf::Color(dataToWrite.canvasColorToPass));
        } else if(dataToWrite.commandToPass.compare("undo") == 0) {
            app.undoCommandNetwork();
        } else if(dataToWrite.commandToPass.compare("redo") == 0) {
            app.redoCommandNetwork();
        } 
    }
}

/*! \brief 	The initialization function simply verifies the Application has started
* by printing out a statement to the command line.
*
*/
void initialization(void) {
	std::cout << "Starting the App" << std::endl;
}

/*! \brief 	The update function controls key and mouse events on the painting canvas of the application.
* Then updates the canvas accordingly. This function also is where the packetReceiver function is called
* allowing inputs from the Server to be handled. 
* @param app an App object that allows us to access and manipulate the canvas. 
*/
void update(App& app) {



    // Update our canvas
    sf::Event event;
    while (app.m_window->pollEvent(event)) {
        Command* test;

        switch (event.type) {
            case sf::Event::Closed :
                app.m_window->close();
                exit(EXIT_SUCCESS);
            case sf::Event::MouseButtonPressed :
                srand(time(nullptr));
                app.commandFlag = rand();
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::U:
                        app.undoCommand(true);
                        
                        break;
                    case sf::Keyboard::R:
                        app.redoCommand(true);
                        break;
                    case sf::Keyboard::C:
                        if (app.m_prevCommand != app.commandEnum::CLEAR) {
                            Command *command = new Clear(&app, app.commandFlag, "clear");
                            app.addCommand(command);
                            app.m_prevCommand = app.commandEnum::CLEAR;
                            break;
                        }
                }

        }
    }


    app.m_gui->nk_input_begin_wrapper();
    while (app.m_gui->getWindow().pollEvent(event)) {
        // Our close event.
        // Note: We only have a 'minimize' button
        //       in our window right now, so this event is not
        //       going to fire.
        if (event.type == sf::Event::Closed) {
            app.m_gui->nk_shutdown_wrapper();
            app.m_gui->getWindow().close();
            exit(EXIT_SUCCESS);
        }

            // Capture any keys that are released
        else if (event.type == sf::Event::KeyReleased) {
            std::cout << "Key Pressed" << std::endl;
            // Check if the escape key is pressed.
            if (event.key.code == sf::Keyboard::Escape) {
                app.m_gui->nk_shutdown_wrapper();
                app.m_gui->getWindow().close();
                exit(EXIT_SUCCESS);
            }
        }
        app.m_gui->nk_handle_event_wrapper(event);

    }
    app.m_gui->nk_input_end_wrapper();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i coordinate = sf::Mouse::getPosition(app.getWindow());

        sf::Vector2f currentXYCoordinates = app.m_window->mapPixelToCoords(coordinate); //andrew edit ****


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

        if (app.mouseX == app.pmouseX && app.mouseY == app.pmouseY) {
        } else if (currentXYCoordinates.x > 0 && currentXYCoordinates.x <= app.getWindow().getSize().x
                   && currentXYCoordinates.y > 0 && currentXYCoordinates.y <= app.getWindow().getSize().y) {
            // if mouse is left-clicked AND key E is pressed, execute the pixel

            if (app.onErase && app.getWindow().hasFocus()) {
                    //networking
                    xToPass = currentXYCoordinates.x;
                    yToPass = currentXYCoordinates.y;

                    commandToPass = "erase";
                    colorOfModificationToPass = app.getBackgroundColor().toInteger();
                    canvasColorToPass = app.getBackgroundColor().toInteger();

                    sizeOfModification = app.getBrush().getSize(); //When implemented will reflect brush size relating to enum, flags can be 0 = small, 1 = medium, 2 = large.
                    brushTypeModification = app.getBrush().getType(); //flag could be  0 = brush, 1 = pen.
                    windowXToPass = app.getWindow().getSize().x;
                    windowYToPass = app.getWindow().getSize().y;
                    packet << xToPass << yToPass << commandToPass << colorOfModificationToPass << canvasColorToPass
                           << sizeOfModification << brushTypeModification << windowXToPass << windowYToPass;


                    app.clientSocketInApp.send(packet);


                    packet.clear();
                    //networking
                    srand(time(nullptr));

                    Command *command = new Erase(currentXYCoordinates, &app, rand(), "erase");

                    app.addCommand(command);
                    app.m_prevCommand = app.commandEnum::ERASE;


                // else, simple mouse event for drawing
            }
                else {
                    if (app.getWindow().hasFocus()) {
                        xToPass = currentXYCoordinates.x;
                        yToPass = currentXYCoordinates.y;

                        commandToPass = "draw";

                        colorOfModificationToPass = app.getBrush().getColor().toInteger();
                        canvasColorToPass = app.getBackgroundColor().toInteger();

                        sizeOfModification = app.getBrush().getSize(); //When implemented will reflect brush size relating to enum, flags can be 0 = small, 1 = medium, 2 = large.
                        brushTypeModification = app.getBrush().getType(); //flag could be  0 = brush, 1 = pen.
                        windowXToPass = app.getWindow().getSize().x;
                        windowYToPass = app.getWindow().getSize().y;
                        packet << xToPass << yToPass << commandToPass << colorOfModificationToPass << canvasColorToPass
                               << sizeOfModification << brushTypeModification << windowXToPass << windowYToPass;


                        app.clientSocketInApp.send(packet);



                        packet.clear();

                        srand(time(nullptr));

                        Command *command = new Draw(currentXYCoordinates, &app, rand(), "draw");
                        app.addCommand(command);
                        app.m_prevCommand = app.commandEnum::DRAW;
                    }
                }
        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            exit(EXIT_SUCCESS);
        }

        // Handling change color event
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            app.getBrush().setColor(sf::Color::Black);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            app.getBrush().setColor(sf::Color::White);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            app.getBrush().setColor(sf::Color::Red);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            app.getBrush().setColor(sf::Color::Green);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
            app.getBrush().setColor(sf::Color::Blue);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
            app.getBrush().setColor(sf::Color::Yellow);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
            app.getBrush().setColor(sf::Color::Magenta);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
            app.getBrush().setColor(sf::Color::Cyan);
        }

        // Handling change size of drawing tool

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && app.getWindow().hasFocus()) {
            app.getBrush().setSize(size::small);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2) && app.getWindow().hasFocus()) {
            app.getBrush().setSize(size::medium);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3) && app.getWindow().hasFocus()) {
            app.getBrush().setSize(size::large);

        }

        // Handling change drawing tools
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Divide)) {
            app.setBrush(app.getBrushFactory().createBrush(2));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply)) {
            app.setBrush(app.getBrushFactory().createBrush(1));
        }


        // only for debug and test
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            std::cout << app.commandFlag << std::endl;
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            app.setBackgroundColor(new sf::Color(sf::Color::Blue.toInteger()));

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            app.setBackgroundColor(new sf::Color(sf::Color::White.toInteger()));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            app.setBackgroundColor(new sf::Color(sf::Color::Yellow.toInteger()));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && app.getWindow().hasFocus()) {
            app.setBackgroundColor(new sf::Color(sf::Color::Green.toInteger()));
        }

        // Stores the previous mouse click position before going to next frame
        app.pmouseX = app.mouseX;
        app.pmouseY = app.mouseY;
        packetReceiver(app);
    }
}


/*! \brief 	The draw call, this is how the canvas refreshes.
*
*/
void draw(App& app) {
	// Static variable
	static int refreshRate = 0;
	++refreshRate;	// Increment
	if (refreshRate > 10) {
        app.getTexture().loadFromImage(app.getImage());
		refreshRate = 0;
	}
}



/*! \brief 	The entry point into our program.
*
*/
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Please enter the port number. For example: ./App 8080" << std::endl;
        return 0;
    }

    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    int port = atoi(argv[1]);
    App app(ip, port);

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
