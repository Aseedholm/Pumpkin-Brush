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
    if (nk_begin(ctx, "Gui", nk_rect(50, 50, 230, 250),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE)) {
        static int property = 20;
        //nk_layout_row_static(ctx, 30, 80, 1);
        //if (nk_button_label(ctx, "button"))
        //    fprintf(stdout, "button pressed\n");



        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "red", op == RED)){
            op = RED;
            app.getBrush().setColor(sf::Color::Red);
        }
        if (nk_option_label(ctx, "black", op == BLACK)){
            op = BLACK;
            app.getBrush().setColor(sf::Color::Black);
        }
        if (nk_option_label(ctx, "green", op == GREEN)){
            op = GREEN;
            app.getBrush().setColor(sf::Color::Green);
        }
        if (nk_option_label(ctx, "blue", op == BLUE)) {
            op = BLUE;
            app.getBrush().setColor(sf::Color::Blue);
        }
        if (nk_option_label(ctx, "white", op == WHITE)) {
            op = WHITE;
            app.getBrush().setColor(sf::Color::White);
        }
        if (nk_option_label(ctx, "yellow", op == YELLOW)) {
            op = YELLOW;
            app.getBrush().setColor(sf::Color::Yellow);
        }
        if (nk_option_label(ctx, "magenta", op == MAGENTA)) {
            op = MAGENTA;
            app.getBrush().setColor(sf::Color::Magenta);
        }
        if (nk_option_label(ctx, "cyan", op == CYAN)) {
            op = CYAN;
            app.getBrush().setColor(sf::Color::Cyan);
        }
    }
    nk_end(ctx);
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