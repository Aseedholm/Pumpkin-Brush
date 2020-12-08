/**
 *  @file   Clear.cpp
 *  @brief  This class represents a clear canvas command in the mini paint app.
 *  @author Japher Su and Hao Zheng
 *  @date   2020-07-12
 ***********************************************/

#include "Clear.hpp"

/*! \brief The constructor of the Clear class.
 *
*/
Clear::Clear(App *app, int flag, std::string command) :Command(flag, command) {
    m_app = app;
    m_originalImage = app->getImage();
    m_backgroundColor = app->getBackgroundColor();
    m_imageSize = app->getImage().getSize();
    m_newImage = new sf::Image;
    m_newImage->create(m_imageSize.x, m_imageSize.y, m_backgroundColor);
}


/*! \brief The destructor of the Clear class.
 *
 */
Clear::~Clear() {
    delete m_newImage;
}

/*! \brief Execute the clear canvas command and wipe off all the drawing from the canvas.
 *
 */

bool Clear::execute() {
    // change the m_image stored for the app
    m_app->setImage(m_newImage);
    // load the new image onto the app texture
    m_app->getTexture().loadFromImage(m_app->getImage());

    return true;
}


/*! \brief Undo the clear canvas command and restore the original image on the canvas.
 *
 */

bool Clear::undo() {
    // set m_image of the app to the original image
    m_app->setImage(&m_originalImage);
    // reload the original image back onto the app texture
    m_app->getTexture().loadFromImage(m_app->getImage());
    return true;
}
