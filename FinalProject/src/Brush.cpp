#include "Brush.hpp"




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

/*! \brief Constructor of Brush
 *
 */
Brush::Brush() {
    m_color = sf::Color::Black;
    m_size = size::small;
    m_shaders.push_back(dir_smallBrush);
    m_shaders.push_back(dir_mediumBrush);
    m_shaders.push_back(dir_largeBrush);
}

/*! \brief Get color of brush
 *
 */
sf::Color Brush::getColor() {
    return m_color;
}

/*! \brief Set color of brush
 *
 */
void Brush::setColor(sf::Color color) {
    m_color = color;
}

/*! \brief Set size of brush
 *
 */
void Brush::setSize(size size) {
    m_size = size;
}

/*! \brief Get size of brush
 *
 */
int Brush::getSize() {
    switch(m_size) {
        case small: return 0;

        case medium: return 1;

        case large: return 2;

        default: return 0;
    }
}

/*! \brief Get shader of brush
 *
 */
std::vector<std::vector<int>> Brush::getShader(){
    switch(m_size) {
        case small: return m_shaders[0];

        case medium: return m_shaders[1];

        case large: return m_shaders[2];

        default: return m_shaders[0];
    }

}

/*! \brief Get type of brush
 *
 */
int Brush::getType() {
    return 0;
}

