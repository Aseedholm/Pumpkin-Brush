/**
 * GeneralBrush class which represent the brush instance when drawing on the canvas
 */

#ifndef GENERALBRUSH_HPP
#define GENERALBRUSH_HPP
// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
#include <vector>

// enum of size of the brush
enum size {small, medium, large};

class GeneralBrush {
private:

public:
    virtual ~GeneralBrush(){};
    virtual sf::Color getColor(){};
    virtual void setColor(sf::Color){};
    virtual void setSize(size){};
    virtual void incSize(){};
    virtual void decSize(){};
    virtual void getSize(){};
    virtual std::vector<std::vector<int>> getShader(){};

};

#endif
