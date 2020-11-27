#include "Gui.hpp"


// Some globals
enum {RED, BLACK,GREEN, BLUE};
static int op = RED;

void drawLayout(struct nk_context* ctx, struct nk_colorf& bg){

    /* GUI */
    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        static int property = 20;
        //nk_layout_row_static(ctx, 30, 80, 1);
        //if (nk_button_label(ctx, "button"))
        //    fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "red", op == RED)){
            op = RED;
        }
        if (nk_option_label(ctx, "black", op == BLACK)){
            op = BLACK;
        }
        if (nk_option_label(ctx, "green", op == GREEN)){
            op = GREEN;
        }
        if (nk_option_label(ctx, "blue", op == BLUE)) {
            op = BLUE;
        }

        //nk_layout_row_dynamic(ctx, 25, 1);
        //nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            bg = nk_color_picker(ctx, bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
            bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
            bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
            bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);
}

void gui_init() {
    /*  GUI
       We are creating a GUI context, and it needs
       to attach to our 'window'.
   */
    // Create a GUI window to draw to
    sf::ContextSettings settings(24, 8, 4, 2, 2);
    sf::RenderWindow gui_window(sf::VideoMode(800,600), "GUI Window",sf::Style::Default,settings);
    gui_window.setVerticalSyncEnabled(true);
    gui_window.setActive(true);
    glViewport(0, 0, gui_window.getSize().x, gui_window.getSize().y);
    struct nk_context *ctx;
    ctx = nk_sfml_init(&gui_window);
    // Load Fonts: if none of these are loaded a default font will be used
    //Load Cursor: if you uncomment cursor loading please hide the cursor
    struct nk_font_atlas *atlas;
    nk_sfml_font_stash_begin(&atlas);
    nk_sfml_font_stash_end();
    // Setup a color for the nuklear gui
    struct nk_colorf bg;
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
}