#include "Gui.hpp"


#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SFML_GL2_IMPLEMENTATION
#include <SFML/OpenGL.hpp>
#include "nuklear.h"
#include "nuklear_sfml_gl2.h"
#include "iostream"



nk_window *win;

/*! \brief Constructor of Gui
 *
 */
Gui::Gui() {
    initGui();
}

Gui::~Gui() {
    delete m_guiWindow;
}

/*! \brief
 *
 */
 void Gui::drawGUI(App& app) {
    if (nk_begin(ctx, "Tools", nk_rect(50, 50, 500, 400),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE)) {
        static int property = 20;
        //nk_layout_row_static(ctx, 30, 80, 1);
        //if (nk_button_label(ctx, "button"))
        //    fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(ctx, 30, 1);
        nk_label(ctx, "Brush Color", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 30, 8);
        if (nk_button_label(ctx, "Red") ) {
            app.getBrush().setColor(sf::Color::Red);
        }
        if (nk_button_label(ctx, "Black") ) {
            app.getBrush().setColor(sf::Color::Black);
        }
        if (nk_button_label(ctx, "Green") ) {
            app.getBrush().setColor(sf::Color::Green);
        }
        if (nk_button_label(ctx, "Blue") ) {
            app.getBrush().setColor(sf::Color::Blue);
        }
        if (nk_button_label(ctx, "White") ) {
            app.getBrush().setColor(sf::Color::White);
        }
        if (nk_button_label(ctx, "Yellow") ) {
            app.getBrush().setColor(sf::Color::Yellow);
        }
        if (nk_button_label(ctx, "Magenta") ) {
            app.getBrush().setColor(sf::Color::Magenta);
        }
        if (nk_button_label(ctx, "Cyan") ) {
            app.getBrush().setColor(sf::Color::Cyan);
        }

        nk_layout_row_dynamic(ctx, 30, 3);
        nk_label(ctx, "Brush Type", NK_TEXT_LEFT);
        if (nk_button_label(ctx, "Brush") ) {
            app.setBrush(app.getBrushFactory().createBrush(1));
        }
        if (nk_button_label(ctx, "Pen") ) {
            app.setBrush(app.getBrushFactory().createBrush(2));
        }



        nk_layout_row_dynamic(ctx, 30, 4);
        nk_label(ctx, "Brush Size", NK_TEXT_LEFT);
        if (nk_button_label(ctx, "small") ) {
            app.getBrush().setSize(size::small);
        }
        if (nk_button_label(ctx, "medium") ) {
            app.getBrush().setSize(size::medium);
        }
        if (nk_button_label(ctx, "large") ) {
            app.getBrush().setSize(size::large);
        }

    }
    nk_end(ctx);

//    if(nk_beign(ctx, "Brush")) {
//
//    }
//    nk_end(ctx);
 }

/*! \brief
 *
 */
 void Gui::initGui() {
    sf::ContextSettings settings(24, 8, 4, 2, 2);

    m_guiWindow = new sf::RenderWindow(sf::VideoMode(600, 400), "GUI Window", sf::Style::Default, settings);

    m_guiWindow->setVerticalSyncEnabled(true);
    m_guiWindow->setActive(true);

    glViewport(0, 0, m_guiWindow->getSize().x, m_guiWindow->getSize().y);

    ctx = nk_sfml_init(m_guiWindow);

    struct nk_font_atlas *atlas;
    nk_sfml_font_stash_begin(&atlas);
    nk_sfml_font_stash_end();
 }

 sf::RenderWindow & Gui::getWindow() {
     return *m_guiWindow;
 }


/*! \brief
 *
 */

void Gui::nk_handle_event_wrapper(sf::Event event) {
    nk_sfml_handle_event(&event);
}


/*! \brief
 *
 */

void Gui::nk_input_end_wrapper() {
    nk_input_end(ctx);
}


void Gui::nk_input_begin_wrapper() {
    nk_input_begin(ctx);
}

void Gui::nk_shutdown_wrapper() {
    nk_sfml_shutdown();
}

void Gui::nk_sfml_render_wrapper() {
    nk_sfml_render(NK_ANTI_ALIASING_ON);
}