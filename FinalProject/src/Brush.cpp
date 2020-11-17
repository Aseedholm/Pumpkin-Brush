#include "Brush.hpp"
#include "iostream"

/**
 * Constructor of brush
 * @param color
 * @param size
 */
Brush::Brush() {
    std::cout << "brush created\n";
    m_color = sf::Color::Black;
    m_size = size::small;
}

sf::Color Brush::getColor() {
    return m_color;
}

void Brush::setColor(sf::Color color) {
    m_color = color;
}

void Brush::setSize(size size) {
    m_size = size;
}

void Brush::incSize() {


}

void Brush::decSize() {

}

void Brush::getSize() {
    std::cout<<m_size<<std::endl;
}
