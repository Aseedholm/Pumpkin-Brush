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


/*! \brief Add command that adds the pixel position in stack
*
*/
void App::addCommand(Command* c) {

	while (!m_redo.empty()) {
		m_redo.pop();
	}
    App::executeCommand(c);
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
	m_brush = m_brushFactory.createBrush(1);
	sf::Uint32 c1 = 254;
	sf::Uint32 c2 = 254;
	sf::Uint32 c3 = 254;
	sf::Uint32 c4 = 255;
	sf::Color l_color(c1, c2, c3, c4);
	sf::Uint32 l_color_int = l_color.toInteger();
	m_backgroundColor = new sf::Color(l_color_int);
}

/*! \brief Add command that adds the pixel position in stack
*
*/
App::App(sf::IpAddress ipAddress, int port){
	std::cout << "Constructor of App called" << std::endl;
	m_window = nullptr;
	m_image = new sf::Image;
	m_sprite = new sf::Sprite;
	m_texture = new sf::Texture;
	m_brush = m_brushFactory.createBrush(1);
	sf::Uint32 c1 = 254;
	sf::Uint32 c2 = 254;
	sf::Uint32 c3 = 254;
	sf::Uint32 c4 = 255;
	sf::Color l_color(c1, c2, c3, c4);
	sf::Uint32 l_color_int = l_color.toInteger();
	m_backgroundColor = new sf::Color(l_color_int);
	//Networking
	clientSocketInApp.setBlocking(false);
    statusInApp = clientSocketInApp.connect(ipAddress, port);
    if(statusInApp != sf::Socket::Done) {
        std::cerr << "Error!" << statusInApp << std::endl;
    }
}

// void App::operator=(const App& app){

// }


/*! \brief 	Executing the command to generate pixel on left mouseclick
*
*/
void App::executeCommand(Command* c) {

	m_undo.push(c);
	m_undo.size();
	c->execute();

}
/*! \brief The undoCommand function unodoes the the pixel in reverse chronological order
*
*/
void App::undoCommand(bool sendMessage) {
	//std::cout << "Size of Undo: **************************************************   " << m_undo.size() << std::endl;
	if (!m_undo.empty()) {
	    Command* t = m_undo.top();
		// packetInApp << xToPass << yToPass << t->getCommand() <<  << canvasColorToPass
		// 	<< sizeOfModification << brushTypeModification << windowXToPass << windowYToPass;

		// clientSocketInApp.send(packetInApp);

	    m_redo.push(t);
		if(sendMessage) {
			sf::Uint32 notImportant = 1;
			packetInApp << notImportant << notImportant << "undo" << notImportant << notImportant<< notImportant<< notImportant<< notImportant<< notImportant<< notImportant;
			clientSocketInApp.send(packetInApp);
			packetInApp.clear();
		}

	    t->undo();
	    m_undo.pop();
	    if(!m_undo.empty() && m_undo.top()->m_cmdFlag == t->m_cmdFlag) {
	        undoCommand(false);
	    }
	    m_prevCommand = UNDO;
	}

}

/*! \brief The undoCommand function unodoes the the pixel in reverse chronological order
*
*/
void App::undoCommandNetwork() {
	if (!m_undo.empty()) {
	    Command* t = m_undo.top();
	    std::cout<<"undo cmd from network flag ------>"<<t->m_cmdFlag<<std::endl;
	    m_redo.push(t);
	    t->undo();
	    m_undo.pop();
	    if(!m_undo.empty() && m_undo.top()->m_cmdFlag == t->m_cmdFlag) {
	        undoCommandNetwork();
	    }
	    m_prevCommand = UNDO;
	}

}

/*! \brief The redo commands redo an undo command until if there is an input in between.
*
*/
void App::redoCommand(bool sendMessage) {
	if (!m_redo.empty()) {
	    Command* t = m_redo.top();
		if(sendMessage) {
			sf::Uint32 notImportant = 1;
			packetInApp << notImportant << notImportant << "redo" << notImportant << notImportant<< notImportant<< notImportant<< notImportant<< notImportant<< notImportant;
			clientSocketInApp.send(packetInApp);
			packetInApp.clear();
		}

        App::executeCommand(t);
		m_redo.pop();
		if(!m_redo.empty() && m_redo.top()->m_cmdFlag == t->m_cmdFlag) {
		    redoCommand(false);
		}
		m_prevCommand = REDO;
	}
}

/*! \brief The redo commands redo an undo command until if there is an input in between.
*
*/
void App::redoCommandNetwork() {
	if (!m_redo.empty()) {
	    Command* t = m_redo.top();
	App::executeCommand(t);
		m_redo.pop();
		if(!m_redo.empty() && m_redo.top()->m_cmdFlag == t->m_cmdFlag) {
		    redoCommandNetwork();
		}
		m_prevCommand = REDO;
	}
}

/*! \brief 	Return a reference to our m_image, so that
*		we do not have to publicly expose it.
*
*/
sf::Image& App::getImage() {
	return *m_image;
}

void App::setImage(sf::Image* newImage) {
    m_image = newImage;
}

/*! \brief 	Return a reference to our m_Texture so that
*		we do not have to publicly expose it.
*
*/
sf::Texture& App::getTexture() {
	return *m_texture;
}

/*! \brief 	Return a reference to our m_window so that we
*		do not have to publicly expose it.
*
*/
sf::RenderWindow& App::getWindow() {
	return *m_window;
}


/*! \brief Return the brush factory of App
 *
 *
 */
BrushFactory App::getBrushFactory() {
    return m_brushFactory;
}

/*! \brief Return the current brush instance of the App
 *
 *
 */
GeneralBrush& App::getBrush() {
    return *m_brush;
}

/*! \brief Set the current brush
 *
 */
void App::setBrush(GeneralBrush* brush) {
    m_brush = brush;
}

std::stack<Command *> App::getUndoStack(){
	return m_undo;

}

std::stack<Command *> App::getRedoStack(){

	return m_redo;
}

/*! \brief 	Destroy we manually call at end of our program.

/*! \brief 	Return a reference to our m_backgroundColor so that we
*		do not have to publicly expose it.
*
*/
sf::Color &App::getBackgroundColor()
{ //Andrew edit*****
	return *m_backgroundColor;
}

/*! \brief 	destroy we manually call at end of our program.

*
*/
void App::destroy() {
	delete m_image;
	delete m_sprite;
	delete m_texture;
	delete m_backgroundColor; //Andrew edit*****
}

/*! \brief 	Initializes the App and sets up the main
*		rendering window(i.e. our canvas.)
*/
void App::init(void (*initFunction)(void)) {
	// Create our window
	m_window = new sf::RenderWindow(sf::VideoMode(300, 300), "Mini-Paint alpha 0.0.2", sf::Style::Titlebar);
    // m_window = new sf::RenderWindow(sf::VideoMode(600, 400), "Mini-Paint alpha 0.0.2"); //andrew edit *********
	m_window->setVerticalSyncEnabled(true);

    // Create gui instance
    m_gui = new Gui();


	// Create an image which stores the pixels we will update
	m_image->create(300, 300, *m_backgroundColor); //Andrew edit*****
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
void App::updateCallback(void (*updateFunction)(App&)) {
	m_updateFunc = updateFunction;
}

/*! \brief 	Set a callback function which will be called
		each iteration of the main loop after update.
*
*/
void App::drawCallback(void (*drawFunction)(App&)) {
	m_drawFunc = drawFunction;
}

/*! \brief 	The main loop function which handles initialization
		and will be executed until the main window is closed.
		Within the loop function the update and draw callback
		functions will be called.
*
*/
void App::loop(App& app) {
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

		// Update Gui window
		m_gui->drawGUI(*this);
        m_gui->getWindow().setActive(true);
        m_gui->getWindow().clear();
        m_gui->nk_sfml_render_wrapper();
        m_gui->getWindow().display();

        // Update the texture
        // Note: This can be done in the 'draw call'
        // Draw to the canvas
		
		// if(m_sprite->getColor() != (*m_backgroundColor)) { //Only change color if colors don't match. 
		// 	m_sprite->setColor(*m_backgroundColor);
		// } //Andrew background update. 
		
		m_window->draw(*m_sprite);
		// Display the canvas
		m_window->display();


	}
}

/*! \brief 	Set a reference to m_backgroundColor.
*
*/
void App::setBackgroundColor(sf::Color *colorPassed) { //Andrew edit*****
	sf::Color newBackground = *colorPassed;
	sf::Color oldColor = *m_backgroundColor;
	for(int i =0; i < m_window->getSize().x; i++) {
		for (int j = 0; j < m_window->getSize().y; j++) {
			if(m_image->getPixel(i, j) == oldColor) {
				m_image->setPixel(i,j, newBackground);
			}
		}
	}
	m_backgroundColor = new sf::Color(newBackground.toInteger());
}



