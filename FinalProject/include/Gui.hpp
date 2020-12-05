#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "App.hpp"


class App;

class Gui {
private:
    enum colorEnum {RED, BLACK, GREEN, BLUE, WHITE, YELLOW, MAGENTA, CYAN};
    enum brushSizeEnum {SMALL, MEDIUM, LARGE};
    enum brushTypeEnum {BRUSH, PEN};
    int m_brushColor = BLACK;
    int m_brushSize = MEDIUM;
    int m_brushType = BRUSH;
    int m_backColor = WHITE;

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

    Gui();
    ~Gui();
    sf::RenderWindow& getWindow();
    void initGui();


    void drawGUI(App&);
    struct nk_context *ctx;
    void nk_input_begin_wrapper();
    void nk_input_end_wrapper();
    void nk_shutdown_wrapper();
    void nk_handle_event_wrapper(sf::Event event);
    void nk_sfml_render_wrapper();

};


#endif