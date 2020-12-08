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
#include "Gui.hpp"

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

 /*! \brief Test initialing GUI window
  *
  */
  TEST_CASE("initialing GUI window test") {
    Gui* gui = new Gui();
    REQUIRE(gui->getWindow().isOpen() == true);
    REQUIRE(gui->getWindow().getSize().x == 600);
    REQUIRE(gui->getWindow().getSize().y == 800);
    gui->~Gui();
  }

/*! \brief Test initialing GUI parameters
*
*/
TEST_CASE("Initialing GUI parameters test") {
    Gui* gui = new Gui();
    REQUIRE(gui->getBrushColor() == Gui::BLACK);
    REQUIRE(gui->getBrushSize() == Gui::SMALL);
    REQUIRE(gui->getBrushType() == Gui::BRUSH);
    REQUIRE(gui->getBackColor() == Gui::WHITE);
    gui->~Gui();
}