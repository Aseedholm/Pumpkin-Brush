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
// Include standard library C++ libraries.
#include <iostream>
#include <string>
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
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i coordinate = sf::Mouse::getPosition(app.GetWindow());

			sf::Vector2f currentXYCoordinates = app.m_window->mapPixelToCoords(coordinate); //andrew edit ****

			//relative positioning and resizing the window
			// store the mouse position of the current frame
			app.mouseX = currentXYCoordinates.x;
			app.mouseY = currentXYCoordinates.y;


			if(app.mouseX == app.pmouseX && app.mouseY == app.pmouseY){
			    std::cout << "Clicking the same pixel, do not execute commands" << std::endl;
			}
			else if (currentXYCoordinates.x > 0 && currentXYCoordinates.x <= app.GetWindow().getSize().x
			&& currentXYCoordinates.y > 0 && currentXYCoordinates.y <= app.GetWindow().getSize().y) {
				Command* command = new Draw(currentXYCoordinates, &app);
				app.AddCommand(command);
			}
			// Modify the pixel
			// App::GetImage().setPixel(coordinate.x,coordinate.y,sf::Color::Red);
		}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        app.UndoCommand();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
        app.RedoCommand();
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
		app.GetTexture().loadFromImage(app.GetImage());
		refreshRate = 0;
	}
}


/*! \brief 	The entry point into our program.
*
*/
int main() {

	App app;
	// Call any setup function
	// Passing a function pointer into the 'init' function.
	// of our application.
	app.Init(&initialization);
	// Setup your keyboard
	app.UpdateCallback(&update);
	// Setup the Draw Function
	app.DrawCallback(&draw);
	// Call the main loop function
	app.Loop(app);
	// Destroy our app
	app.Destroy();

	return 0;
}

