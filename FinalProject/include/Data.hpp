#ifndef DATA_H
#define DATA_H

#include <string>

/**
 * Data that will be sent as a packet from Client to Server and Server to Clients.
 */
class Data {
private:
    int pixelX;
    int pixelY;
    unsigned long colorAsInteger;
    std::string commandDescription;
    int windowX;
    int windowY;

public:
    Data(int pixelXPassed, int pixelYPassed, unsigned long colorAsIntegerPassed, 
    std::string commandDescriptionPassed, int windowXPassed, int windowYPassed);
    ~Data();
    void setPixelX(int pixelXPassed);
    void setPixelY(int pixelYPassed);
    void setColorAsInteger(unsigned long colorAsIntegerPassed);
    void setCommandDescription(std::string commandDescriptionPassed);
    void setWindowX(int windowXPassed);
    void setWindowY(int windowYPassed);

    int getPixelX();
    int getPixelY();
    unsigned long getColorAsInteger();
    std::string getCommandDescription();
    int getWindowX();
    int getWindowY();
};

#endif
