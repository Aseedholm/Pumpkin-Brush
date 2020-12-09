/**
 *  @file   Gui.cpp
 *  @brief  A GUI class that renders a gui window and operation widgets for the mini paint app.
 *  @author Japher Su and Hao Zheng
 *  @date   2020-07-12
 ***********************************************/
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

nk_window* win;

/*! \brief Constructor of Gui.
 *
 */
Gui::Gui() {
    initGui();
}

/*! \brief Destructor of Gui.
 *
 */
Gui::~Gui() {
    delete m_guiWindow;
}

/*! \brief Initialise the gui window.
 *
 */
void Gui::initGui() {
    m_brushColor = BLACK;
    m_brushSize = SMALL;
    m_brushType = BRUSH;
    m_backColor = WHITE;

    sf::ContextSettings settings(24, 8, 4, 2, 2);

    m_guiWindow = new sf::RenderWindow(sf::VideoMode(600, 800), "Pumpkin Brush Toolbox", sf::Style::Default, settings);

    m_guiWindow->setVerticalSyncEnabled(true);
    m_guiWindow->setActive(true);

    glViewport(0, 0, m_guiWindow->getSize().x, m_guiWindow->getSize().y);

    ctx = nk_sfml_init(m_guiWindow);

    // Init style
    ctx->style.text.color.g = 255;
    ctx->style.text.color.r = 0;
    ctx->style.text.color.b = 0;
    // Window color header
    ctx->style.window.header.normal.data.color.r = 255;
    ctx->style.window.header.normal.data.color.g = 220;
    ctx->style.window.header.normal.data.color.b = 0;
    ctx->style.window.header.active.data.color.r = 255;
    ctx->style.window.header.active.data.color.g = 220;
    ctx->style.window.header.active.data.color.b = 0;
    // Button color
    ctx->style.button.hover.data.color.r = 0;
    ctx->style.button.hover.data.color.g = 204;
    ctx->style.button.hover.data.color.b = 255;

    ctx->style.button.active.data.color.r = 0;
    ctx->style.button.active.data.color.g = 128;
    ctx->style.button.active.data.color.b = 255;
    // Init font
    struct nk_font_atlas* atlas;
    nk_sfml_font_stash_begin(&atlas);
    const char* font_path = "../nuklear/extra_font/kenvector_future_thin.ttf";
    struct nk_font* future = nk_font_atlas_add_from_file(atlas, font_path, 16, 0);
    nk_sfml_font_stash_end();
    nk_style_set_font(ctx, &future->handle);
}


/*! \brief Draw the gui window.
 *
 */
void Gui::drawGUI(App& app) {
    if (nk_begin(ctx, "Commands", nk_rect(50, 50, 500, 150),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        static int property = 20;

        undoRedoOption(app);
        clearCanvas(app);
    }
    nk_end(ctx);

    if (nk_begin(ctx, "Brush Tools", nk_rect(50, 250, 500, 250),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        static int property = 20;

        changeBrushColor(app);
        changeBrushSize(app);
        changeBrushType(app);
    }
    nk_end(ctx);

    if (nk_begin(ctx, "Background Tools", nk_rect(50, 550, 500, 200),
        NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
        NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        static int property = 20;

        changeBackColor(app);
    }
    nk_end(ctx);
}

/*! \brief Set up the widgets for brush color.
 *
 */
void Gui::changeBrushColor(App& app) {
    nk_layout_row_dynamic(ctx, 30, 1);
    nk_label(ctx, "Tool Color", NK_TEXT_LEFT);

    nk_layout_row_dynamic(ctx, 30, 4);
    if (nk_option_label(ctx, "Black", m_brushColor == colorEnum::BLACK) && m_brushColor != colorEnum::BLACK) {
        m_brushColor = colorEnum::BLACK;
        app.getBrush().setColor(sf::Color::Black);
    }
    if (nk_option_label(ctx, "Red", m_brushColor == colorEnum::RED) && m_brushColor != colorEnum::RED) {
        m_brushColor = colorEnum::RED;
        app.getBrush().setColor(sf::Color::Red);
    }
    if (nk_option_label(ctx, "Green", m_brushColor == colorEnum::GREEN) && m_brushColor != colorEnum::GREEN) {
        m_brushColor = colorEnum::GREEN;
        app.getBrush().setColor(sf::Color::Green);
    }
    if (nk_option_label(ctx, "Blue", m_brushColor == colorEnum::BLUE) && m_brushColor != colorEnum::BLUE) {
        m_brushColor = colorEnum::BLUE;
        app.getBrush().setColor(sf::Color::Blue);
    }
    if (nk_option_label(ctx, "White", m_brushColor == colorEnum::WHITE) && m_brushColor != colorEnum::WHITE) {
        m_brushColor = colorEnum::WHITE;
        app.getBrush().setColor(sf::Color::White);
    }
    if (nk_option_label(ctx, "Yellow", m_brushColor == colorEnum::YELLOW) && m_brushColor != colorEnum::YELLOW) {
        m_brushColor = colorEnum::YELLOW;
        app.getBrush().setColor(sf::Color::Yellow);
    }
    if (nk_option_label(ctx, "Magenta", m_brushColor == colorEnum::MAGENTA) && m_brushColor != colorEnum::MAGENTA) {
        m_brushColor = colorEnum::MAGENTA;
        app.getBrush().setColor(sf::Color::Magenta);
    }
    if (nk_option_label(ctx, "Cyan", m_brushColor == colorEnum::CYAN) && m_brushColor != colorEnum::CYAN) {
        m_brushColor = colorEnum::CYAN;
        app.getBrush().setColor(sf::Color::Cyan);
    }
}


/*! \brief Set up the widgets for brush size.
*
*/
void Gui::changeBrushSize(App& app) {
    nk_layout_row_dynamic(ctx, 30, 4);
    nk_label(ctx, "Tool Size", NK_TEXT_LEFT);

    nk_layout_row_dynamic(ctx, 30, 4);
    if (nk_option_label(ctx, "Small", m_brushSize == brushSizeEnum::SMALL) && m_brushSize != brushSizeEnum::SMALL) {
        m_brushSize = brushSizeEnum::SMALL;
        app.getBrush().setSize(size::small);
    }
    if (nk_option_label(ctx, "Medium", m_brushSize == brushSizeEnum::MEDIUM) && m_brushSize != brushSizeEnum::MEDIUM) {
        m_brushSize = brushSizeEnum::MEDIUM;
        app.getBrush().setSize(size::medium);

    }
    if (nk_option_label(ctx, "Large", m_brushSize == brushSizeEnum::LARGE) && m_brushSize != brushSizeEnum::LARGE) {
        m_brushSize = brushSizeEnum::LARGE;
        app.getBrush().setSize(size::large);
    }
}

/*! \brief Set up the widgets for brush type.
*
*/
void Gui::changeBrushType(App& app) {
    nk_layout_row_dynamic(ctx, 30, 4);
    nk_label(ctx, "Tool Type", NK_TEXT_LEFT);

    //    nk_layout_row_dynamic(ctx, 30, 3);
    if (nk_button_label(ctx, "Brush")) {
        //        m_brushType = brushTypeEnum::BRUSH;
        app.setBrush(app.getBrushFactory().createBrush(1));
        m_brushColor = colorEnum::BLACK;
        m_brushSize = brushSizeEnum::SMALL;
        app.onErase = false;
    }
    if (nk_button_label(ctx, "Pen")) {
        //        m_brushType = brushTypeEnum::PEN;
        app.setBrush(app.getBrushFactory().createBrush(2));
        m_brushColor = colorEnum::BLACK;
        m_brushSize = brushSizeEnum::SMALL;
        app.onErase = false;
    }
    if (nk_button_label(ctx, "Eraser")) {
        if (app.m_prevCommand != app.commandEnum::ERASE) {
            app.onErase = !app.onErase;
        }
    }
}

/*! \brief Set up the widgets for undo and redo operations.
 *
 */
void Gui::undoRedoOption(App& app) {
    nk_layout_row_dynamic(ctx, 30, 2);
    if (nk_button_label(ctx, "Undo")) {
        app.undoCommand(true);
    }
    if (nk_button_label(ctx, "Redo")) {
        app.redoCommand(true);
    }
}


/*! \brief Set up the widget for clear canvas operation.
*
*/
void Gui::clearCanvas(App& app) {
    nk_layout_row_dynamic(ctx, 30, 1);
    if (nk_button_label(ctx, "Clear Canvas")) {
        if (app.m_prevCommand != app.commandEnum::CLEAR) {
            srand(time(nullptr));
            app.commandFlag = rand();
            Command* command = new Clear(&app, app.commandFlag, "clear");
            //networking
            std::string clear = "clear";
            sf::Uint32 send = 1;
            packetInGui << send << send << clear << send << send << send << send << send << send;
            app.clientSocketInApp.send(packetInGui);
            packetInGui.clear();
            //networking
            app.addCommand(command);
            app.m_prevCommand = app.commandEnum::CLEAR;
        }
    }
}


/*! \brief This function is a helper function for changeBackColor that will send the 
* background color information over the network to the Server. 
*/
void Gui::networkBackground(sf::Uint32 color, App& app) {
    std::string background = "backgroundChange";
    sf::Uint32 send = 1;
    packetInGui << send << send << background << send << color << send << send << send << send;
    app.clientSocketInApp.send(packetInGui);
    packetInGui.clear();
}

/*! \brief Set up the widgets for changing background color.
*
*/
void Gui::changeBackColor(App& app) {
    if (nk_tree_push(ctx, NK_TREE_TAB, "Canvas Background Color", NK_MAXIMIZED)) {
        sf::Uint32 localColor = 0;
            sf::Uint8 c1 = 0;
            sf::Uint8 c2 = 0;
            sf::Uint8 c3 = 0;
            sf::Uint8 c4 = 0;
        nk_layout_row_dynamic(ctx, 30, 1);
        if (nk_option_label(ctx, "White", m_backColor == colorEnum::WHITE) && m_backColor != colorEnum::WHITE) {
            m_backColor = colorEnum::WHITE;
            // localColor = sf::Color::White.toInteger();
            c1 = 254;
            c2 = 254;
            c3 = 254;
            c4 = 255;
            sf::Color l_color(c1, c2, c3, c4);
            localColor = l_color.toInteger();
            networkBackground(localColor, app);
            app.setBackgroundColor(new sf::Color(localColor));
            std::cout << "Black back";
        }
        if (nk_option_label(ctx, "Black", m_backColor == colorEnum::BLACK) && m_backColor != colorEnum::BLACK) {
            m_backColor = colorEnum::BLACK;
            // localColor = sf::Color::Black.toInteger();
            c1 = 1;
            c2 = 0;
            c3 = 0;
            c4 = 255;
            sf::Color l_color(c1, c2, c3, c4);
            localColor = l_color.toInteger();
            networkBackground(localColor, app);
            app.setBackgroundColor(new sf::Color(localColor));
        }
        if (nk_option_label(ctx, "Yellow", m_backColor == colorEnum::YELLOW) && m_backColor != colorEnum::YELLOW) {
            m_backColor = colorEnum::YELLOW;
            // localColor = sf::Color::Yellow.toInteger();
            c1 = 255;
            c2 = 254;
            c3 = 0;
            c4 = 255;
            sf::Color l_color(c1, c2, c3, c4);
            localColor = l_color.toInteger();
            networkBackground(localColor, app);
            app.setBackgroundColor(new sf::Color(localColor));
        }
        if (nk_option_label(ctx, "Green", m_backColor == colorEnum::GREEN) && m_backColor != colorEnum::GREEN) {
            m_backColor = colorEnum::GREEN;
            // localColor = sf::Color::Green.toInteger();
            c1 = 0;
            c2 = 128;
            c3 = 1;
            c4 = 255;
            sf::Color l_color(c1, c2, c3, c4);
            localColor = l_color.toInteger();
            networkBackground(localColor, app);
            app.setBackgroundColor(new sf::Color(localColor));
        }
        nk_tree_pop(ctx);
    }
}

/*! \brief Get the gui window.
*
*/
sf::RenderWindow& Gui::getWindow() {
    return *m_guiWindow;
}

/*! \brief Get the brush color.
 *
 */
int Gui::getBrushColor () {
    return m_brushColor;
}

/*! \brief Get the brush size.
 *
 */
int Gui::getBrushSize() {
    return m_brushSize;
}
/*! \brief Get the brush type.
 *
 */
int Gui::getBrushType() {
    return m_brushType;
}

/*! \brief Get the background color.
 *
 */
int Gui::getBackColor() {
    return m_backColor;
}

/*! \brief Wrapper function for nk_sfml_handle_event.
 *
 */
void Gui::nk_handle_event_wrapper(sf::Event event) {
    nk_sfml_handle_event(&event);
}


/*! \brief Wrapper function for nk_input_end.
 *
 */
void Gui::nk_input_end_wrapper() {
    nk_input_end(ctx);
}

/*! \brief Wrapper function for nk_input_begin.
 *
 */
void Gui::nk_input_begin_wrapper() {
    nk_input_begin(ctx);
}

/*! \brief Wrapper function for nk_sfml_shutdown.
 *
 */
void Gui::nk_shutdown_wrapper() {
    nk_sfml_shutdown();
}

/*! \brief Wrapper function for nk_sfml_render.
 *
 */
void Gui::nk_sfml_render_wrapper() {
    nk_sfml_render(NK_ANTI_ALIASING_ON);
}