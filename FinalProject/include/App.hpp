/** 
 *  @file   App.hpp 
 *  @brief  App class interface
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/
#ifndef APP_HPP 
#define APP_HPP



// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

// Include OpenGL


// Include standard library C++ libraries.
#include <queue>
#include <stack>
#include "Command.hpp"


#include "BrushFactory.hpp"
// Project header files
// #include ...

// Singleton for our Application called 'App'.
class App{
private:
// Member variables
	// Queue stores the next command to do.
	std::stack<Command*> m_redo;
	// Stack that stores the last action to occur.
	std::stack<Command*> m_undo;
	// Main image	
	sf::Image* m_image;
	// Create a sprite that we overaly
	// on top of the texture.
	sf::Sprite* m_sprite;
	// Texture sent to the GPU for rendering
	sf::Texture* m_texture;
	// Render texture
    // The Brush instance which can draw pixels
	GeneralBrush* m_brush;
	// Brush factory which can create different types of brushes
    BrushFactory m_brushFactory;

	sf::Color* m_backgroundColor;



// Member functions
	// Default constructor which is hidden in the Singleton
	// Store the address of our funcion pointer
	// for each of the callback functions.	
	void (*m_initFunc)(void);
	void (*m_updateFunc)(App&);
	void (*m_drawFunc)(App&);

	// Member variable of GUI
    enum {RED, BLACK,GREEN, BLUE};
    int op = RED;

public:
	
	
// Member Variables	
	// Keeps track of the previous mouse and current mouse positions
	// 'pmouse' is where the mouse previously was.
	// 'mouse' records where the mouse currently is.
	unsigned int pmouseX, pmouseY, mouseX, mouseY;
	sf::RenderWindow* m_window;
	sf::RenderWindow* m_guiWindow;
	App();
	// void operator=(const App& app);
// Member functions


	GeneralBrush& GetBrush();
  BrushFactory getBrushFactory();
	void SetBrush(GeneralBrush* brush);
	void addCommand(Command* c);
	void executeCommand(Command* c);
	void undoCommand();
	void redoCommand();
	sf::Image& getImage();
    void setImage(sf::Image* newImage);
	sf::Texture& getTexture();
	sf::RenderWindow& getWindow();



	void destroy();
	void init(void (*initFunction)(void));
	void updateCallback(void (*updateFunction)(App& app));
	void drawCallback(void (*drawFunction)(App& app));
	void loop(App& app);
	void setBackgroundColor(sf::Color *colorPassed);
	sf::Color& getBackgroundColor();
    void drawGUI(struct nk_context* ctx);
    struct nk_context *ctx;
   void nk_input_begin_wrapper();
   void nk_input_end_wrapper();
   void nk_shutdown_wrapper();
    void nk_handle_event_wrapper(sf::Event event);
};


#endif
//TODO: Write comments for the methods