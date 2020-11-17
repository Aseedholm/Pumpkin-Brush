#ifndef BRUSH_H
#define BRUSH_H



#include "GeneralBrush.hpp"

/**
 * One kind of Brush
 */
class Brush : public GeneralBrush {
private:
    sf::Color m_color;
    int m_size;

public:
    Brush();
    sf::Color getColor() override;
    void setColor(sf::Color color) override;
    void incSize() override;
    void decSize() override;
};

#endif
