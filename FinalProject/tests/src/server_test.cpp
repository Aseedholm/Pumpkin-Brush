#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Network.hpp>
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
#include "Gui.hpp"

TEST_CASE("Check if app can be initialized") {
    sf::TcpListener listenerSocket;
    sf::Socket::Status serverStatus;
    sf::Packet packet;
    serverStatus = listenerSocket.listen(8081);
    sf::TcpSocket clientTest;
    listenerSocket.accept(clientTest);
    clientTest.receive(packet);
    std::string str;
    packet >> str;
    std::cout << str << std::endl;
    REQUIRE(str.compare("This is from the Client") == 0);
    packet.clear();
    packet << "This is from the Server";
    clientTest.send(packet);
    
    
}
