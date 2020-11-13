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
		// if(event.type == sf::Event::MouseLeft){				
			// Modify the pixel
			// App::mouseX = event.mouseMove.x; 
			// App::mouseY = event.mouseMove.y; 
			// App::GetImage().setPixel(App::mouseX,App::mouseY,sf::Color::Blue);

		// }

	// We can otherwise handle events normally
	// sf::Mouse::isButtonPressed(sf::Mouse::Left)
	//event.mouseButton.button == sf::Mouse::Left

		
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Z) {
				app.UndoCommand();
			}
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Y) {
				app.RedoCommand();
			}
		}
		// Capture any keys that are released
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			exit(EXIT_SUCCESS);
		}
	}
	// if (event.type == sf::Event::MouseButtonReleased) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i coordinate = sf::Mouse::getPosition(app.GetWindow());
			//relative positioning and resizing the window 
			std::cout << "Hmm, lots of repeats here: " << coordinate.x << "," << coordinate.y << std::endl;
			if (coordinate.x <= 600 && coordinate.y <= 400) {
				Command* command = new Draw(coordinate.x, coordinate.y, &app);
				app.AddCommand(command);
			}
			// Modify the pixel
			// App::GetImage().setPixel(coordinate.x,coordinate.y,sf::Color::Red);
		}
	// }
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

