#include "Brush.hpp"
#include "iostream"

/**
 * Constructor of brush
 * @param color
 * @param size
 */

std::vector<std::vector<int>> dir_1 = {{0, 0}};
std::vector<std::vector<int>> dir_2 = {{-1,-1}, {0, -1}, {1, -1},
                                        {-1, 0}, {0, 0}, {1, 0},
                                       {-1, 1}, {0, 1}, {1, 1}};
std::vector<std::vector<int>> dir_3 = {{-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2},
                                       {-1, -2}, { -1, -1}, {-1, 0}, {-1, 1}, {-1, 2},
                                       {0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2},
                                       {1, -2}, {1, -1}, {1, 0}, {1, 1}, {1, 2},
                                       {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}};

Brush::Brush() {
    std::cout << "brush created\n";
    m_color = sf::Color::Black;
    m_size = size::small;
    m_shaders.push_back(dir_1);
    m_shaders.push_back(dir_2);
    m_shaders.push_back(dir_3);
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

std::vector<std::vector<int>> Brush::getShader(){
    switch(m_size) {
        case small: return m_shaders[0];

        case medium: return m_shaders[1];

        case large: return m_shaders[2];
    }

}

