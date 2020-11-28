#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>

/**
 * Data that will be sent as a packet from Client to Server and Server to Clients.
 */
class Data {
private:
    int pixelX;
    int pixelY;
    int colorAsInteger;
    std::string commandDescription;
    int windowX;
    int windowY;

public:
    // Data();
    // Data(int pixelXPassed, int pixelYPassed, int colorAsIntegerPassed, int windowXPassed, int windowYPassed);
    Data(int pixelXPassed, int pixelYPassed, int colorAsIntegerPassed, std::string commandDescriptionPassed, int windowXPassed, int windowYPassed);
    // ~Data();
    void setPixelX(int pixelXPassed);
    void setPixelY(int pixelYPassed);
    void setColorAsInteger(int colorAsIntegerPassed);
    void setCommandDescription(std::string commandDescriptionPassed);
    void setWindowX(int windowXPassed);
    void setWindowY(int windowYPassed);

    int getPixelX();
    int getPixelY();
    int getColorAsInteger();
    std::string getCommandDescription();
    int getWindowX();
    int getWindowY();
    void printData(); // Method to just verify things were saved correctly. 
};

#endif
