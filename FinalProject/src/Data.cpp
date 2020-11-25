#include "include/Data.hpp"


Data::Data(int pixelXPassed, int pixelYPassed, unsigned long colorAsIntegerPassed, 
    std::string commandDescriptionPassed, int windowXPassed, int windowYPassed) 
    : pixelX(pixelXPassed), pixelY(pixelYPassed), colorAsInteger(colorAsIntegerPassed), 
    commandDescription(commandDescriptionPassed), windowX(windowXPassed), windowY(windowYPassed) {

    }

Data::~Data() {
   
}

void Data::setPixelX(int pixelXPassed) {
    pixelX = pixelXPassed;
}

void Data::setPixelY(int pixelYPassed) {
    pixelY = pixelYPassed;
}

void Data::setColorAsInteger(unsigned long colorAsIntegerPassed) {
    colorAsInteger = colorAsIntegerPassed;
}

void Data::setCommandDescription(std::string commandDescriptionPassed) {
    commandDescription = commandDescriptionPassed;
}

void Data::setWindowX(int windowXPassed) {
    windowX = windowXPassed;
}

void Data::setPixelX(int windowYPassed) {
    windowY = windowYPassed;
}

int Data::getPixelX() {
    return pixelX;
}

int Data::getPixelY() {
    return pixelY;
}

unsigned long Data::getColorAsInteger() {
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
