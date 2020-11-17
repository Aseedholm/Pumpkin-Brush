/**
 * GeneralBrush class which represent the brush instance when drawing on the canvas
 */

#ifndef GENERALBRUSH_HPP
#define GENERALBRUSH_HPP
// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>

class GeneralBrush {
private:

public:
    virtual ~GeneralBrush(){};
    virtual sf::Color getColor(){};
    virtual void setColor(sf::Color){};
    virtual void incSize(){};
    virtual void decSize(){};
};

#endif
