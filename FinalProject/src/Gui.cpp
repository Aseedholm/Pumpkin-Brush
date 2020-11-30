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
#include "Clear.hpp"



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

        changeBrushColor(app);
        changeBrushSize(app);
        changeBrushType(app);
        undoRedoOption(app);
        clearCanvas(app);

    }
    nk_end(ctx);


 }


 void Gui::changeBrushColor(App& app) {
     nk_layout_row_dynamic(ctx, 30, 1);
     nk_label(ctx, "Brush Color", NK_TEXT_LEFT);

     nk_layout_row_dynamic(ctx, 30, 4);
     if (nk_option_label(ctx, "Black", m_brushColor == brushColorEnum::BLACK)) {
         m_brushColor = brushColorEnum::BLACK;
         app.getBrush().setColor(sf::Color::Black);
     }
     if (nk_option_label(ctx, "Red", m_brushColor == brushColorEnum::RED)) {
         m_brushColor = brushColorEnum::RED;
         app.getBrush().setColor(sf::Color::Red);
     }
     if (nk_option_label(ctx, "Green", m_brushColor == brushColorEnum::GREEN)) {
         m_brushColor = brushColorEnum::GREEN;
         app.getBrush().setColor(sf::Color::Green);
     }
     if (nk_option_label(ctx, "Blue", m_brushColor == brushColorEnum::BLUE)) {
         m_brushColor = brushColorEnum::BLUE;
         app.getBrush().setColor(sf::Color::Blue);
     }
     if (nk_option_label(ctx, "White", m_brushColor == brushColorEnum::WHITE)) {
         m_brushColor = brushColorEnum::WHITE;
         app.getBrush().setColor(sf::Color::White);
     }
     if (nk_option_label(ctx, "Yellow", m_brushColor == brushColorEnum::YELLOW)) {
         m_brushColor = brushColorEnum::YELLOW;
         app.getBrush().setColor(sf::Color::Yellow);
     }
     if (nk_option_label(ctx, "Magenta", m_brushColor == brushColorEnum::MAGENTA)) {
         m_brushColor = brushColorEnum::MAGENTA;
         app.getBrush().setColor(sf::Color::Magenta);
     }
     if (nk_option_label(ctx, "Cyan", m_brushColor == brushColorEnum::CYAN)) {
         m_brushColor = brushColorEnum::CYAN;
         app.getBrush().setColor(sf::Color::Cyan);
     }
 }

 void Gui::changeBrushSize(App& app) {
     nk_layout_row_dynamic(ctx, 30, 4);
     nk_label(ctx, "Brush Size", NK_TEXT_LEFT);

     nk_layout_row_dynamic(ctx, 30, 4);
     if (nk_option_label(ctx, "Small", m_brushSize == brushSizeEnum::SMALL)) {
         m_brushSize = brushSizeEnum::SMALL;
         app.getBrush().setSize(size::small);
     }
     if (nk_option_label(ctx, "Medium", m_brushSize == brushSizeEnum::MEDIUM)) {
         m_brushSize = brushSizeEnum::MEDIUM;
         app.getBrush().setSize(size::medium);

     }
     if (nk_option_label(ctx, "Large", m_brushSize == brushSizeEnum::LARGE)) {
         m_brushSize = brushSizeEnum::LARGE;
         app.getBrush().setSize(size::large);
     }
 }

void Gui::changeBrushType(App& app) {
    nk_layout_row_dynamic(ctx, 30, 3);
    nk_label(ctx, "Brush Type", NK_TEXT_LEFT);

//    nk_layout_row_dynamic(ctx, 30, 3);
    if (nk_button_label(ctx, "Brush")) {
//        m_brushType = brushTypeEnum::BRUSH;
        app.setBrush(app.getBrushFactory().createBrush(1));
    }
    if (nk_button_label(ctx, "Pen")) {
//        m_brushType = brushTypeEnum::PEN;
        app.setBrush(app.getBrushFactory().createBrush(2));
    }
}

void Gui::undoRedoOption(App &app) {
    nk_layout_row_dynamic(ctx, 30, 3);
    nk_label(ctx, "Option", NK_TEXT_LEFT);
    if(nk_button_label(ctx, "Undo")) {
        app.undoCommand();
    }
    if(nk_button_label(ctx, "Redo")) {
        app.redoCommand();
    }

 }

 void Gui::clearCanvas(App &app) {
     nk_layout_row_dynamic(ctx, 30, 1);
     if(nk_button_label(ctx, "Clear Canvas")) {
         Command* command = new Clear(&app);
         app.addCommand(command);
     }
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