#define CATCH_CONFIG_MAIN
#include "catch.hpp"

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

/*! \brief 	Init function argument
*
*/
void initialization(void) {
    std::cout << "Starting the App!!" << std::endl;
}
/*! \brief 	Sets pixel at a particular position of color blue 
*/
void setPixel(App& app, int x, int y) {
    Command* command = new Draw(x, y, &app);
    app.AddCommand(command);

}
/*! \brief 	Checks if a pixel is present at a particular place and has the same color as specified
*
*/
int CheckPixelColor(App& app, sf::Color pixelColor, int x, int y) {
    auto color = app.GetImage().getPixel(x, y);
    if (color == pixelColor) {
        return 1;
    }

    return 0;
}
/*! \brief 	Test the size of canvas if it's set to 600x400
*
*/
int testCanvasSize(App& app, int x, int y) {
    auto size = app.GetImage().getSize();
    if (size.x == x && size.y == y) {
        return 1;
    }
    return 0;
}
/*! \brief 	Check if the canvas' size is 600x400
*
*/
TEST_CASE("Check if the canvas' size is correct") {
    App app;
    app.Init(&initialization);
    REQUIRE(testCanvasSize(app, 600, 400));
    app.Destroy();

}
/*! \brief 	Check if a pixel of blue color is drawn on the canvas at position (100,100)
*
*/
TEST_CASE("Checking if pixel is created at position 100,100") {
    App app;
    app.Init(&initialization);
    setPixel(app, 100, 100);
    REQUIRE(CheckPixelColor(app, sf::Color::Blue, 100, 100));
}
/*! \brief 	Check if the undo command is working
*
*/
TEST_CASE("Test Undo command") {
    App app;
    app.Init(&initialization);
    setPixel(app, 200, 200);
    app.UndoCommand();
    REQUIRE(CheckPixelColor(app, sf::Color::White, 200, 200));
    
}
/*! \brief 	Checking single redo command 
*
*/
TEST_CASE("Test Redo command") {
    App app;
    app.Init(&initialization);
    setPixel(app, 300, 300);
    app.UndoCommand();
    app.RedoCommand();
    REQUIRE(CheckPixelColor(app, sf::Color::Blue, 300, 300));

}
/*! \brief 	Checking batch undo and redo commands
*
*/
TEST_CASE("Testing multiple undos and redos"){
    App app;
    app.Init(&initialization);
    //Making multiple pixels
    for (int i = 300; i < 310; i++) {
        setPixel(app, i, i);
    }
    //Looping through to check if the pixels were created
    for(int i=300; i<310; i++){
       
        REQUIRE(CheckPixelColor(app, sf::Color::Blue, i, i));
    }
    //Looping through again and undo-ing the pixels and also checking the pixels. 
    for(int i=309; i>=300; i--){
        app.UndoCommand();
        REQUIRE(CheckPixelColor(app, sf::Color::White, i, i));
    }
}