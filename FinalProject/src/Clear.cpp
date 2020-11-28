/**
 *  @file   Clear.hpp
 *  @brief  Implementation of Clear.hpp
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/

#include "Clear.hpp"

Clear::Clear(App *app) {
    m_app = app;
    m_originalImage = app->getImage();
    m_backgroundColor = app->getBackgroundColor();
    m_imageSize = app->getImage().getSize();

    m_newImage = new sf::Image;
    m_newImage->create(m_imageSize.x, m_imageSize.y, m_backgroundColor);
}

Clear::~Clear() {
    delete m_newImage;
}

bool Clear::execute() {
    // change the m_image stored for the app
    m_app->setImage(m_newImage);
    // load the new image onto the app texture
    m_app->getTexture().loadFromImage(m_app->getImage());

    return true;
}

bool Clear::undo() {
    // set m_image of the app to the original image
    m_app->setImage(&m_originalImage);
    // reload the original image back onto the app texture
    m_app->getTexture().loadFromImage(m_app->getImage());

    return true;
}
