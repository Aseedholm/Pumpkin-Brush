#include "Data.hpp"

// Data::Data() {
//     pixelX = -1;
//     pixelY = -1;
//     colorAsInteger = -1000;
//     commandDescription = "Null";
//     windowX = -1;
//     windowY = -1; 
// }

// Data::Data(int pixelXPassed, int pixelYPassed, int colorAsIntegerPassed, int windowXPassed, int windowYPassed) 
//     : pixelX(pixelXPassed), pixelY(pixelYPassed), colorAsInteger(colorAsIntegerPassed), windowX(windowXPassed), windowY(windowYPassed) {
//         commandDescription = "seomething";
//     }

Data::Data(int pixelXPassed, int pixelYPassed, int colorAsIntegerPassed, 
    std::string commandDescriptionPassed, int windowXPassed, int windowYPassed) 
    : pixelX(pixelXPassed), pixelY(pixelYPassed), colorAsInteger(colorAsIntegerPassed), 
    commandDescription(commandDescriptionPassed), windowX(windowXPassed), windowY(windowYPassed) {

    }

// Data::~Data() {
   
// }

void Data::setPixelX(int pixelXPassed) {
    pixelX = pixelXPassed;
}

void Data::setPixelY(int pixelYPassed) {
    pixelY = pixelYPassed;
}

void Data::setColorAsInteger(int colorAsIntegerPassed) {
    colorAsInteger = colorAsIntegerPassed;
}

void Data::setCommandDescription(std::string commandDescriptionPassed) {
    commandDescription = commandDescriptionPassed;
}

void Data::setWindowX(int windowXPassed) {
    windowX = windowXPassed;
}

void Data::setWindowY(int windowYPassed) {
    windowY = windowYPassed;
}

int Data::getPixelX() {
    return pixelX;
}

int Data::getPixelY() {
    return pixelY;
}

int Data::getColorAsInteger() {
    return colorAsInteger;
}

std::string Data::getCommandDescription() {
    return commandDescription;
}

int Data::getWindowX() {
    return windowX;
}

int Data::getWindowY() {
    return windowY;
}

void Data::printData() {
    std::cout << "X pixel passed: " << pixelX << "\nY pixel passed: " << pixelY << "\nColor as integer: " << colorAsInteger <<
                "\nCommand Description Passed: " << commandDescription << "\nWindow X Passed: " << windowX << "\nWindow Y Passed: " << windowY << std::endl;
}
