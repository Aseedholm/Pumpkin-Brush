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
    m_size = 1;
}

sf::Color Brush::getColor() {
    return m_color;
}

void Brush::setColor(sf::Color color) {
    m_color = color;
}

void Brush::incSize() {

}

void Brush::decSize() {

}