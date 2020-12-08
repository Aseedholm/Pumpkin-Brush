#ifndef GENERALBRUSH_HPP
#define GENERALBRUSH_HPP
// Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
#include <vector>

// enum of size of the brush
enum size {small, medium, large};

/*! \brief GeneralBrush class which represent the brush instance when drawing on the canvas
 *
 */
class GeneralBrush {
private:

public:
    virtual ~GeneralBrush(){};
    virtual sf::Color getColor() = 0;
    virtual void setColor(sf::Color) = 0;
    virtual void setSize(size) = 0;
    virtual int getSize() = 0;
    virtual std::vector<std::vector<int>> getShader() = 0;
    virtual int getType() = 0;

};

#endif
