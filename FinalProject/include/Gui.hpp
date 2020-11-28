#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include "App.hpp"


class Gui {
private:
    enum {RED, BLACK, GREEN, BLUE, WHITE, YELLOW, MAGENTA, CYAN};
    int op = BLACK;
    sf::RenderWindow* m_guiWindow;

public:

    Gui();
    ~Gui();
    sf::RenderWindow& getWindow();
    void initGui();


    void drawGUI(App& app);
    struct nk_context *ctx;
    void nk_input_begin_wrapper();
    void nk_input_end_wrapper();
    void nk_shutdown_wrapper();
    void nk_handle_event_wrapper(sf::Event event);
    void nk_sfml_render_wrapper();
};


#endif