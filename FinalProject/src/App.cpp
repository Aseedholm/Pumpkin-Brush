/**
 *  @file   App.cpp
 *  @brief  Main class for program
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/

 // Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <cassert>
// Project header files
#include "App.hpp"


#include<iostream>

// All static members of a Singleton need to initialized to some value.
// This is so that when the program is compiled, memory is reserved
// for each of these static values.
// Potentially handy data structures for building an undo system.
// std::stack<Command*> App::m_redo;
// std::stack<Command*> App::m_undo;
// // Function pointers
// void (*App::m_initFunc)(void) = nullptr;
// void (*App::m_updateFunc)(void) = nullptr;
// void (*App::m_drawFunc)(void) = nullptr;
// // Mouse variables
// unsigned int App::pmouseX = 0;
// unsigned int App::pmouseY = 0;
// unsigned int App::mouseX = 0;
// unsigned int App::mouseY = 0;
// // Canvas variables
// sf::RenderWindow* App::m_window = nullptr;
// sf::Image* App::m_image = new sf::Image;
// sf::Sprite* App::m_sprite = new sf::Sprite;
// sf::Texture* App::m_texture = new sf::Texture;


/*! \brief Add command that adds the pixel position in stack
*
*/
void App::AddCommand(Command* c) {

	while (!m_redo.empty()) {
		m_redo.pop();
	}
	App::ExecuteCommand(c);
}
/*! \brief Add command that adds the pixel position in stack
*
*/
App::App(){
	std::cout << "Constructor of App called" << std::endl;
	m_window = nullptr;
	m_image = new sf::Image;
	m_sprite = new sf::Sprite;
	m_texture = new sf::Texture;
	m_brush = brushFactory.createBrush(1);

}
// void App::operator=(const App& app){

// }


/*! \brief 	Executing the command to generate pixel on left mouseclick
*
*/
void App::ExecuteCommand(Command* c) {

	m_undo.push(c);
	m_undo.size();
	c->execute();

}
/*! \brief The UndoCommand function unodoes the the pixel in reverse chronological order
*
*/
void App::UndoCommand() {
	if (!m_undo.empty()) {
		Command* t = m_undo.top();
		m_redo.push(t);
		t->undo();
		m_undo.pop();
	}

}
/*! \brief The redo commands redo an undo command until if there is an input in between.
*
*/
void App::RedoCommand() {
	if (!m_redo.empty()) {
		App::ExecuteCommand(m_redo.top());
		m_redo.pop();
	}
}

/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*
*/
sf::Image& App::GetImage() {
	return *m_image;
}

/*! \brief 	Return a reference to our m_Texture so that
*		we do not have to publicly expose it.
*
*/
sf::Texture& App::GetTexture() {
	return *m_texture;
}

/*! \brief 	Return a reference to our m_window so that we
*		do not have to publicly expose it.
*
*/
sf::RenderWindow& App::GetWindow() {
	return *m_window;
}

/*! \brief Return the current brush instance of the App
 *
 *
 */
GeneralBrush& App::GetBrush() {
    return *m_brush;
}

/*! \brief 	Destroy we manually call at end of our program.
*
*/
void App::Destroy() {
	delete m_image;
	delete m_sprite;
	delete m_texture;
}

/*! \brief 	Initializes the App and sets up the main
*		rendering window(i.e. our canvas.)
*/
void App::Init(void (*initFunction)(void)) {
	// Create our window
//	m_window = new sf::RenderWindow(sf::VideoMode(600, 400), "Mini-Paint alpha 0.0.2", sf::Style::Titlebar);
    m_window = new sf::RenderWindow(sf::VideoMode(600, 400), "Mini-Paint alpha 0.0.2"); //andrew edit *********
	m_window->setVerticalSyncEnabled(true);
	// Create an image which stores the pixels we will update
	m_image->create(600, 400, sf::Color::White);
	assert(m_image != nullptr && "m_image != nullptr");
	// Create a texture which lives in the GPU and will render our image
	m_texture->loadFromImage(*m_image);
	assert(m_texture != nullptr && "m_texture != nullptr");
	// Create a sprite which is the entity that can be textured
	m_sprite->setTexture(*m_texture);
	assert(m_sprite != nullptr && "m_sprite != nullptr");
	// Set our initialization function to perform any user
	// initialization
	m_initFunc = initFunction;
}

/*! \brief 	Set a callback function which will be called
		each iteration of the main loop before drawing.
*
*/
void App::UpdateCallback(void (*updateFunction)(App&)) {
	m_updateFunc = updateFunction;
}

/*! \brief 	Set a callback function which will be called
		each iteration of the main loop after update.
*
*/
void App::DrawCallback(void (*drawFunction)(App&)) {
	m_drawFunc = drawFunction;
}

/*! \brief 	The main loop function which handles initialization
		and will be executed until the main window is closed.
		Within the loop function the update and draw callback
		functions will be called.
*
*/
void App::Loop(App& app) {
	// Call the init function

	m_initFunc();

	// Start the main rendering loop
	while (m_window->isOpen()) {
		// Clear the window
		m_window->clear();
		// Updates specified by the user
		m_updateFunc(app);
		// Additional drawing specified by user
		m_drawFunc(app);
		// Update the texture
		// Note: This can be done in the 'draw call'
		// Draw to the canvas
		m_window->draw(*m_sprite);
		// Display the canvas
		m_window->display();
	}
}


