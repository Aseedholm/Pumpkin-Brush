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

/*! \brief 	Test on different brush size
 *
*/
TEST_CASE("Check on different brush size") {
    App app;
    app.init(&initialization);
    app.setBrush(app.getBrushFactory().createBrush(1));
    app.getBrush().setSize(size::small);
    app.getBrush().setColor(sf::Color::Black);
    sf::Vector2f position(10,10);
    app.addCommand(new Draw(position, &app, 1, "draw"));

    sf::Uint32 c1 = 254;
    sf::Uint32 c2 = 254;
    sf::Uint32 c3 = 254;
    sf::Uint32 c4 = 255;
    sf::Color l_color(c1, c2, c3, c4);

    REQUIRE(app.getImage().getPixel(10, 10) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(9, 9) == l_color);
    REQUIRE(app.getImage().getPixel(9, 10) == l_color);
    REQUIRE(app.getImage().getPixel(9, 11) == l_color);
    REQUIRE(app.getImage().getPixel(10, 9) == l_color);
    REQUIRE(app.getImage().getPixel(10, 11) == l_color);
    REQUIRE(app.getImage().getPixel(11, 9) == l_color);
    REQUIRE(app.getImage().getPixel(11, 10) == l_color);
    REQUIRE(app.getImage().getPixel(11, 11) == l_color);

    app.undoCommand(0);
    app.setBrush(app.getBrushFactory().createBrush(1));
    app.getBrush().setSize(size::medium);
    app.getBrush().setColor(sf::Color::Black);
    app.addCommand(new Draw(position, &app, 2, "draw"));
    REQUIRE(app.getImage().getPixel(10, 10) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(9, 9) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(9, 10) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(9, 11) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(10, 9) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(10, 11) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(11, 9) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(11, 10) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(11, 11) == sf::Color::Black);
}

/*! \brief Test on different brush color
 *
 */
TEST_CASE("Check on different brush color") {
    App app;
    app.init(&initialization);
    app.setBrush(app.getBrushFactory().createBrush(1));
    app.getBrush().setSize(size::small);
    app.getBrush().setColor(sf::Color::Black);
    sf::Vector2f position(10,10);
    app.addCommand(new Draw(position, &app, 1, "draw"));
    REQUIRE(app.getImage().getPixel(10, 10) == sf::Color::Black);
    app.getBrush().setColor(sf::Color::Red);
    app.addCommand(new Draw(position, &app, 2, "draw"));
    REQUIRE(app.getImage().getPixel(10, 10) == sf::Color::Red);
    app.getBrush().setColor(sf::Color::Yellow);
    app.addCommand(new Draw(position, &app, 3, "draw"));
    REQUIRE(app.getImage().getPixel(10, 10) == sf::Color::Yellow);
}

/*! \brief Test on different brush type
 *
 */
TEST_CASE("Check on different brush type") {
    App app;
    app.init(&initialization);
    app.setBrush(app.getBrushFactory().createBrush(1));
    app.getBrush().setSize(size::small);
    app.getBrush().setColor(sf::Color::Black);
    sf::Vector2f position(10,10);
    app.addCommand(new Draw(position, &app, 1, "draw"));

    sf::Uint32 c1 = 254;
    sf::Uint32 c2 = 254;
    sf::Uint32 c3 = 254;
    sf::Uint32 c4 = 255;
    sf::Color l_color(c1, c2, c3, c4);

    REQUIRE(app.getImage().getPixel(10, 10) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(9, 9) == l_color);
    REQUIRE(app.getImage().getPixel(9, 10) == l_color);
    REQUIRE(app.getImage().getPixel(9, 11) == l_color);
    REQUIRE(app.getImage().getPixel(10, 9) == l_color);
    REQUIRE(app.getImage().getPixel(10, 11) == l_color);
    REQUIRE(app.getImage().getPixel(11, 9) == l_color);
    REQUIRE(app.getImage().getPixel(11, 10) == l_color);
    REQUIRE(app.getImage().getPixel(11, 11) == l_color);

    app.undoCommand(0);

    app.setBrush(app.getBrushFactory().createBrush(2));
    app.getBrush().setSize(size::small);
    app.getBrush().setColor(sf::Color::Black);
    app.addCommand(new Draw(position, &app, 2, "draw"));
    REQUIRE(app.getImage().getPixel(10, 9) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(11, 9) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(9, 10) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(10, 10) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(11, 10) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(12, 10) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(9, 11) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(10, 11) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(11, 11) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(12, 11) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(10, 12) == sf::Color::Black);
    REQUIRE(app.getImage().getPixel(11, 12) == sf::Color::Black);
}