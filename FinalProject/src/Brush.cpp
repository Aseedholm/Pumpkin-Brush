#include "Brush.hpp"
#include "iostream"



// define the direction matrix of 3 size of brushes
std::vector<std::vector<int>> dir_smallBrush = {{0, 0}};
std::vector<std::vector<int>> dir_mediumBrush = {{-1,-1}, {0, -1}, {1, -1},
                                        {-1, 0}, {0, 0}, {1, 0},
                                       {-1, 1}, {0, 1}, {1, 1}};
std::vector<std::vector<int>> dir_largeBrush = {{-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2},
                                       {-1, -2}, { -1, -1}, {-1, 0}, {-1, 1}, {-1, 2},
                                       {0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2},
                                       {1, -2}, {1, -1}, {1, 0}, {1, 1}, {1, 2},
                                       {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}};

/**
 * Constructor of brush
 */
Brush::Brush() {
    // std::cout << "brush created\n";
    m_color = sf::Color::Black;
    m_size = size::small;
    m_shaders.push_back(dir_smallBrush);
    m_shaders.push_back(dir_mediumBrush);
    m_shaders.push_back(dir_largeBrush);
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


int Brush::getSize() {
    switch(m_size) {
        case small: return 0;

        case medium: return 1;

        case large: return 2;
    }
}


std::vector<std::vector<int>> Brush::getShader(){
    switch(m_size) {
        case small: return m_shaders[0];

        case medium: return m_shaders[1];

        case large: return m_shaders[2];
    }

}

int Brush::getType() {
    return 0;
}

