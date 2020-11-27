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

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SFML_GL2_IMPLEMENTATION
#include <SFML/OpenGL.hpp>
#include "nuklear.h"
#include "nuklear_sfml_gl2.h"




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
    m_guiWindow = nullptr;
	m_image = new sf::Image;
	m_sprite = new sf::Sprite;
	m_texture = new sf::Texture;
	m_brush = m_brushFactory.createBrush(1);
	m_backgroundColor = new sf::Color(sf::Color::White.toInteger());


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
void App::undoCommand() {
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
void App::redoCommand() {
	if (!m_redo.empty()) {
        App::executeCommand(m_redo.top());
		m_redo.pop();
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
GeneralBrush& App::GetBrush() {
    return *m_brush;
}

/*! \brief Set the current brush
 *
 */
void App::SetBrush(GeneralBrush* brush) {
    m_brush = brush;
}


/*! \brief 	Destroy we manually call at end of our program.

/*! \brief 	Return a reference to our m_backgroundColor so that we
*		do not have to publicly expose it.
*
*/
sf::Color& App::getBackgroundColor() { //Andrew edit*****
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
//	m_window = new sf::RenderWindow(sf::VideoMode(600, 400), "Mini-Paint alpha 0.0.2", sf::Style::Titlebar);
    m_window = new sf::RenderWindow(sf::VideoMode(600, 400), "Mini-Paint alpha 0.0.2"); //andrew edit *********
	m_window->setVerticalSyncEnabled(true);

	// Create Gui window
    sf::ContextSettings settings(24, 8, 4, 2, 2);
    m_guiWindow = new sf::RenderWindow(sf::VideoMode(600, 400), "GUI Window", sf::Style::Default, settings);

    m_guiWindow->setVerticalSyncEnabled(true);
    m_guiWindow->setActive(true);

    glViewport(0, 0, m_guiWindow->getSize().x, m_guiWindow->getSize().y);

    ctx = nk_sfml_init(m_guiWindow);


    // Load fonts of GUI
    struct nk_font_atlas *atlas;
    nk_sfml_font_stash_begin(&atlas);
    nk_sfml_font_stash_end();

	// Create an image which stores the pixels we will update
	m_image->create(600, 400, *m_backgroundColor); //Andrew edit*****
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

		drawGUI(ctx);
		// Update the texture
		// Note: This can be done in the 'draw call'
		// Draw to the canvas

        m_guiWindow->setActive(true);
        m_guiWindow->clear();

        nk_sfml_render(NK_ANTI_ALIASING_ON);

        m_guiWindow->display();

		
		if(m_sprite->getColor() != (*m_backgroundColor)) { //Only change color if colors don't match. 
			m_sprite->setColor(*m_backgroundColor);
		}
		
		m_window->draw(*m_sprite);
		// Display the canvas
		m_window->display();


	}
}

/*! \brief 	Set a reference to m_backgroundColor.
*
*/
void App::setBackgroundColor(sf::Color *colorPassed) { //Andrew edit*****
	m_backgroundColor = colorPassed;
}



/*! \brief Draw the layout of gui
 *
 */
void App::drawGUI(struct nk_context *ctx) {
    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE)) {
        static int property = 20;
        //nk_layout_row_static(ctx, 30, 80, 1);
        //if (nk_button_label(ctx, "button"))
        //    fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "red", op == RED)){
            op = RED;
            this->GetBrush().setColor(sf::Color::Red);
        }
        if (nk_option_label(ctx, "black", op == BLACK)){
            op = BLACK;
        }
        if (nk_option_label(ctx, "green", op == GREEN)){
            op = GREEN;
        }
        if (nk_option_label(ctx, "blue", op == BLUE)) {
            op = BLUE;
        }
    }
    nk_end(ctx);
}

void App::nk_input_begin_wrapper(){
    nk_input_begin(ctx);
}

void App::nk_input_end_wrapper() {
    nk_input_end(ctx);
}

void App::nk_shutdown_wrapper() {
    nk_sfml_shutdown();
}

void App::nk_handle_event_wrapper(sf::Event event) {
    nk_sfml_handle_event(&event);
}

