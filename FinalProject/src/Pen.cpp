#include "Pen.hpp"
#include <iostream>


// define direction matrix for 3 size of pens
std::vector<std::vector<int>> dir_smallPen = {
        {0, -1}, {1, -1},
        {-1, 0}, {0, 0}, {1, 0}, {2, 0},
        {-1, 1}, {0, 1},{1, 1}, {2, 1},
        {0, 2}, {1, 2}
};
std::vector<std::vector<int>> dir_mediumPen = { {-2, -1}, {-2, 0}, {-2, 1},
                                                 {-1, -2}, {-1, -1}, {-1, 0}, {-1, 1}, {-1, 2},
                                                 {0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2},
                                                 {1, -2}, {1, -1}, {1, 0}, {1, 1}, {1, 2},
                                                  {2, -1}, {2, 0}, {2, 1}};
std::vector<std::vector<int>> dir_largePen = { {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2},
                                                 {-1, -2}, { -1, -1}, {-1, 0}, {-1, 1}, {-1, 2},
                                                 {0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2},
                                                 {1, -2}, {1, -1}, {1, 0}, {1, 1}, {1, 2},
                                                 {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2},
                                                 {-1, -3}, {0, -3}, {1, -3},
                                                 {-1, 3}, {0, 3}, {1, 3},
                                                 {-3, -1}, {-3, 0}, {-3, 1},
                                                 {3, -1}, {3, 0}, {3, 1}

};

/**
 * Constructor of Pen
 */
Pen::Pen() {
    // std::cout<<"Pen created"<<std::endl;
    m_color = sf::Color::Black;
    m_size = size::small;
    m_shaders.push_back(dir_smallPen);
    m_shaders.push_back(dir_mediumPen);
    m_shaders.push_back(dir_largePen);

}

sf::Color Pen::getColor() {
    return m_color;
}

std::vector<std::vector<int>> Pen::getShader() {
    switch(m_size) {
        case small: return m_shaders[0];

        case medium: return m_shaders[1];

        case large: return m_shaders[2];
    }
}

int Pen::getSize() {
    switch(m_size) {
        case small: return 0;

        case medium: return 1;

        case large: return 2;
    }
}

void Pen::setSize(size size) {
    m_size = size;
}

void Pen::setColor(sf::Color color) {
    m_color = color;
}

int Pen::getType() {
    return 1;
}