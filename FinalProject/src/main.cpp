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
#include "Brush.hpp"
#include "Pen.hpp"

//Networking
sf::TcpSocket clientSocket;
sf::Socket::Status status;
sf::Packet packet;

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

int counter = 0;
//newly added
//original,remote,temp
void remoteDraw(App& app, sf::Uint32 xToPass, sf::Uint32 yToPass, sf::Uint32 colorOfModification, sf::Uint32 sizeOfModification, sf::Uint32 brushTypeOfModification){
    GeneralBrush originalBrush;

    GeneralBrush& temp = app.GetBrush();

    int brushType; //0 = brush 1 = pen
    brushType = app.GetBrush().getType();

    if(brushTypeOfModification == 0) { //brush
        Brush* networkBrush;
        networkBrush->setColor(sf::Color(colorOfModification));
        
        if(sizeOfModification == 0) {
            size small = small;
            networkBrush->setSize(small);
        } else if(sizeOfModification == 1) {
            size medium = medium;
            networkBrush->setSize(medium);
        } else if(sizeOfModification == 2) {
            size large = large;
            networkBrush->setSize(large);
        }

        app.SetBrush(networkBrush);

    } else if(brushTypeOfModification == 1) { //pen
        Pen* networkPen;
        networkPen->setColor(sf::Color(colorOfModification));

        if(sizeOfModification == 0) {
            size small = small;
            networkPen->setSize(small);
        } else if(sizeOfModification == 1) {
            size medium = medium;
            networkPen->setSize(medium);
        } else if(sizeOfModification == 2) {
            size large = large;
            networkPen->setSize(large);
        }
        app.SetBrush(networkPen);
    }

    

    sf::Vector2f passedXY{xToPass, yToPass};
    Command* command = new Draw(passedXY, &app);
    app.addCommand(command);

    app.SetBrush(&temp);

    //make local brush variable. call getter for app so we can retain old brush.
    //set app's brush to remoteDraw's value. 
    //get APp's brushType
    //set app's brush type
    //get app's color
    //set app's color to remoteDraw's value

    //do draw command

    //set app's brush to old value
    //set app's brush size to old value
    //set app's color to old value. 

    //app.SetBrush(small, medium, or large);


}

void packetReceiver(App& app) {
    metaData dataToWrite;
    clientSocket.receive(packet);
    if(packet >> dataToWrite.xToPass >> dataToWrite.yToPass >> dataToWrite.commandToPass 
    >> dataToWrite.colorOfModificationToPass >> dataToWrite.canvasColorToPass >> dataToWrite.sizeOfModification 
    >> dataToWrite.brushTypeModification >> dataToWrite.windowXToPass >> dataToWrite.windowYToPass) {
        packet.clear();
        if(dataToWrite.commandToPass.compare("draw")){
            remoteDraw(app, dataToWrite.xToPass, dataToWrite.yToPass, dataToWrite.colorOfModificationToPass, dataToWrite.sizeOfModification, dataToWrite.brushTypeModification);
        }
    }
    //draw

    //erase

    //clear

    //background change - color


}


//newly added

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
    //networking receive logic
    // metaData dataToWrite;
    // clientSocket.receive(packet);
    // if(packet >> dataToWrite.xToPass >> dataToWrite.yToPass >> dataToWrite.commandToPass 
    // >> dataToWrite.colorOfModificationToPass >> dataToWrite.canvasColorToPass >> dataToWrite.sizeOfModification 
    // >> dataToWrite.brushTypeModification >> dataToWrite.windowXToPass >> dataToWrite.windowYToPass) {
    //     sf::Vector2f passedXY{dataToWrite.xToPass, dataToWrite.yToPass};
    //     Command* command = new Draw(passedXY, &app);
    //     app.addCommand(command);
    //     packet.clear();
    // }
    packetReceiver(app);


    //networking receive logic



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
        ///
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
        //test
        // sf::Color oldColor = app.getBackgroundColor();
        // for(int i =0; i < app.getWindow().getSize().x; i++) {
        //     for (int j = 0; j < app.getWindow().getSize().y; j++) {
        //         if(app.getImage().getPixel(i, j) == oldColor) {
        //             app.getImage().setPixel(i,j, sf::Color::Blue);
        //         }
        //     }
        // }

        //test

    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        app.setBackgroundColor(new sf::Color(sf::Color::White.toInteger()));
        // sf::Color oldColor = app.getBackgroundColor();
        // for(int i =0; i < app.getWindow().getSize().x; i++) {
        //     for (int j = 0; j < app.getWindow().getSize().y; j++) {
        //         if(app.getImage().getPixel(i, j) == oldColor) {
        //             app.getImage().setPixel(i,j, sf::Color::White);
        //         }
        //     }
        // }
    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
        app.setBackgroundColor(new sf::Color(sf::Color::Yellow.toInteger()));

        // sf::Color oldColor = app.getBackgroundColor();
        // for(int i =0; i < app.getWindow().getSize().x; i++) {
        //     for (int j = 0; j < app.getWindow().getSize().y; j++) {
        //         if(app.getImage().getPixel(i, j) == oldColor) {
        //             app.getImage().setPixel(i,j, sf::Color::Yellow);
        //         }
        //     }
        // }
    }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
        app.setBackgroundColor(new sf::Color(sf::Color::Green.toInteger()));
        // sf::Color oldColor = app.getBackgroundColor();
        // for(int i =0; i < app.getWindow().getSize().x; i++) {
        //     for (int j = 0; j < app.getWindow().getSize().y; j++) {
        //         if(app.getImage().getPixel(i, j) == oldColor) {
        //             app.getImage().setPixel(i,j, sf::Color::Green);
        //         }
        //     }
        // }
    }

    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
    //     // sf::Vector2u vector{1500, 500};
    //     // app.getWindow().setSize(vector);
    //     app.getImage().saveToFile("testimage.jpg");
    // }

    //     if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
    //     // sf::Vector2u vector{1500, 500};
    //     // app.getWindow().setSize(vector);
    //     app.getImage().loadFromFile("testimage.jpg");
    // }


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
    clientSocket.setBlocking(false);
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
    status = clientSocket.connect(ip, 8081);
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

