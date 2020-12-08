#ifndef PEN_H
#define PEN_H



#include "GeneralBrush.hpp"

#include <vector>

/*! \brief One kind of Brush which draws a circle shape of pixels
 *
 */
class Pen : public GeneralBrush {
private:
    sf::Color m_color;
    size m_size;
    std::vector<std::vector<std::vector<int>>> m_shaders;

public:
    Pen();
    sf::Color getColor() override;
    void setColor(sf::Color color) override;
    void setSize(size size) override;
    int getSize() override;
    std::vector<std::vector<int>> getShader() override;
    int getType() override; 
};

#endif
