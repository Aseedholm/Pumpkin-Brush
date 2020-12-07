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
