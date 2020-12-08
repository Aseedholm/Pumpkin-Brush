/**
 *  @file   Gui.hpp
 *  @brief  A GUI class that renders a gui window and operation widgets for the mini paint app.
 *  @author Japher Su and Hao Zheng
 *  @date   2020-07-12
 ***********************************************/
#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "App.hpp"

class App;

class Gui {
private:
    int m_brushColor;
    int m_brushSize;
    int m_brushType;
    int m_backColor;

    sf::RenderWindow* m_guiWindow;

    void changeBrushColor(App& app);
    void changeBrushSize(App& app);
    void changeBrushType(App& app);
    void undoRedoOption(App& app);
    void clearCanvas(App &app);
    void changeBackColor(App& app);
    void networkBackground(sf::Uint32 color, App& app);
    sf::Packet packetInGui;

public:
    enum colorEnum {RED, BLACK, GREEN, BLUE, WHITE, YELLOW, MAGENTA, CYAN};
    enum brushSizeEnum {SMALL, MEDIUM, LARGE};
    enum brushTypeEnum {BRUSH, PEN};

    Gui();
    ~Gui();
    void initGui();

    sf::RenderWindow& getWindow();
    int getBrushColor();
    int getBrushSize();
    int getBrushType();
    int getBackColor();

    void drawGUI(App&);
    struct nk_context *ctx;
    void nk_input_begin_wrapper();
    void nk_input_end_wrapper();
    void nk_shutdown_wrapper();
    void nk_handle_event_wrapper(sf::Event event);
    void nk_sfml_render_wrapper();
};

#endif