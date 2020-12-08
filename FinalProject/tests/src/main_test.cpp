#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"

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
#include "Brush.hpp"
#include "Pen.hpp"

#include "Command.hpp"
#include "Draw.hpp"
#include "Erase.hpp"
#include "Clear.hpp"
#include "Data.hpp"


/*! \brief 	Init function argument
*
*/
void initialization(void) {
    std::cout << "Starting the App!!" << std::endl;
}

/*! \brief 	Check if the canvas' size is 600x400
*
*/
TEST_CASE("Check if app can be initialized") {
    App app;
    app.init(&initialization);
    app.destroy();
}


/*! \brief 	Check if we can properly change the background color of the canvas. 
*
*/
TEST_CASE("Check if App's setBackground function works as expected.") {

    //Used custom values for our background colors. 
    /*

            White
            c1 = 254;
            c2 = 254;
            c3 = 254;
            c4 = 255;
            
            Black
            c1 = 1;
            c2 = 0;
            c3 = 0;
            c4 = 255;

            Yellow
            c1 = 255;
            c2 = 254;
            c3 = 0;
            c4 = 255;

            Green
            c1 = 0;
            c2 = 128;
            c3 = 1;
            c4 = 255;
        }
    */
    sf::Color white(254, 254, 254, 255);
    sf::Color black(1, 0, 0, 255);
    sf::Color yellow(255, 254, 0, 255);
    sf::Color green(0, 128, 1, 255);


    App app; //application is intialzied with a white background, confirm this. 
    app.init(&initialization);

    //Test we start with a white background. 
    for(int x = 0; x < app.getImage().getSize().x; x++) {
        for (int y = 0; y < app.getImage().getSize().y; y++) {
            REQUIRE(white == app.getImage().getPixel(x,y));
        }
    }

    //set the background to black and verify every pixel is black. 
    app.setBackgroundColor(new sf::Color(black.toInteger()));
    for(int x = 0; x < app.getImage().getSize().x; x++) {
        for (int y = 0; y < app.getImage().getSize().y; y++) {
            REQUIRE(black == app.getImage().getPixel(x,y));
        }
    }

    //set the background to yellow and verify every pixel is yellow. 
    app.setBackgroundColor(new sf::Color(yellow.toInteger()));
    for(int x = 0; x < app.getImage().getSize().x; x++) {
        for (int y = 0; y < app.getImage().getSize().y; y++) {
            REQUIRE(yellow == app.getImage().getPixel(x,y));
        }
    }

    //set the background to green and verify every pixel is green. 
    app.setBackgroundColor(new sf::Color(green.toInteger()));
    for(int x = 0; x < app.getImage().getSize().x; x++) {
        for (int y = 0; y < app.getImage().getSize().y; y++) {
            REQUIRE(green == app.getImage().getPixel(x,y));
        }
    }

    //set the background to white and verify every pixel is white. 
    app.setBackgroundColor(new sf::Color(white.toInteger()));
    for(int x = 0; x < app.getImage().getSize().x; x++) {
        for (int y = 0; y < app.getImage().getSize().y; y++) {
            REQUIRE(white == app.getImage().getPixel(x,y));
        }
    }
    app.destroy();
}

/*! \brief 	Check if the undo and redo function in App work as expected. 
*
*/
TEST_CASE("Check if App's undo/redo functions works as expected.") {
    sf::Vector2f xAndY1 = {100.0, 100.0};
    sf::Vector2f xAndY2 = {200.0, 200.0};
    sf::Vector2f xAndY3 = {300.0, 300.0};
    App app;
    app.init(&initialization);
    //do a draw command
    Command* drawCommand1 = new Draw(xAndY1, &app, 1, "draw");
    Command* drawCommand2 = new Draw(xAndY2, &app, 1, "draw");
    Command* drawCommand3 = new Draw(xAndY3, &app, 1, "draw");
    app.addCommand(drawCommand1);
    app.addCommand(drawCommand2);
    app.addCommand(drawCommand3);
    //verify pixel is there. //default drawing color is black.
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY1.x, xAndY1.y));
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY2.x, xAndY2.y));
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY3.x, xAndY3.y));

    app.undoCommand(true); //all three pixels draw should disappear because of our smooth undo. 

    REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY1.x, xAndY1.y));
    REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY2.x, xAndY2.y));
    REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY3.x, xAndY3.y));

    app.redoCommand(true); //all three pixels draw should reappear because of our smooth redo. 

    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY1.x, xAndY1.y));
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY2.x, xAndY2.y));
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY3.x, xAndY3.y));

    //execute two erase commands. 
    Command* eraseCommand1 = new Erase(xAndY1, &app, 2, "erase");
    Command* eraseCommand2 = new Erase(xAndY2, &app, 2, "erase");
    app.addCommand(eraseCommand1);
    app.addCommand(eraseCommand2);

    REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY1.x, xAndY1.y));
    REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY2.x, xAndY2.y));
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY3.x, xAndY3.y)); //this pixel should still be there. 

    //undo erase command
    app.undoCommand(true); //all three pixels draw should disappear because of our smooth undo. 

    //verify pixel is there
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY1.x, xAndY1.y));
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY2.x, xAndY2.y));
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY3.x, xAndY3.y));
    
    //redo erase command
    app.redoCommand(true);

    REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY1.x, xAndY1.y));
    REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY2.x, xAndY2.y));
    REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY3.x, xAndY3.y)); //this pixel should still be there. 

    // Command* clearCommand = new Clear(&app, 3, "clear");
    // app.addCommand(clearCommand);
    // //Verify canvas has been cleared. 
    // REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY1.x, xAndY1.y));
    // REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY2.x, xAndY2.y));
    // REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY3.x, xAndY3.y));

    // app.undoCommandNetwork();
    // //verify canvas has been reset to having just the 1 pixel drawn. 
    // REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY1.x, xAndY1.y));
    // REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY2.x, xAndY2.y));
    // REQUIRE(sf::Color::Black == app.getImage().getPixel(xAndY3.x, xAndY3.y));

    // app.redoCommandNetwork();
    // //Verify canvas has been cleared. 
    // REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY1.x, xAndY1.y));
    // REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY2.x, xAndY2.y));
    // REQUIRE(sf::Color::Black != app.getImage().getPixel(xAndY3.x, xAndY3.y));
    app.destroy();
}
