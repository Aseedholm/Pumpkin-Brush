
// LAB
//
// We have provided the following starter code for creating a GUI.
//
// HOW TO COMPILE
//
//
// g++ main.cpp -o mygui -I./include/ -lsfml-graphics -lsfml-window -lsfml-system -lGL
//
// HOW TO RUN
//
// ./mygui


// Include some standard libraries
// The 'C-based' libraries are needed for Nuklear GUI
#include <string.h>

// Include our Third-Party SFML header
// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

// NUKLEAR - for our GUI
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SFML_GL2_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sfml_gl2.h"

// Include standard library C++ libraries.
#include <iostream>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

// Some globals
enum {RED, BLACK,GREEN, BLUE};
static int op = RED;


// Function to render our GUI
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


// The entry point into our program.
int main(){
    // Setup the context
    sf::ContextSettings settings(24, 8, 4, 2, 2);
        // Create a rendering window where we can draw an image on
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Mini-Paint Lab",sf::Style::Default,settings);
    // Set the sync rate after creating a window
        // Refreshes window at same rate as the monitor
        window.setVerticalSyncEnabled(true);
    window.setActive(true);

        // create an image to draw on in the window
        sf::Image image;
        image.create(WINDOW_WIDTH,WINDOW_HEIGHT, sf::Color::White);

        // Create the texture that will be displayed
        sf::Texture texture;
        texture.loadFromImage(image);

        // Create a sprite that we overaly
        // on top of the texture.
        sf::Sprite sprite;
        sprite.setTexture(texture);

    /*  GUI
        We are creating a GUI context, and it needs
        to attach to our 'window'.
    */
        // Create a GUI window to draw to
        sf::RenderWindow gui_window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "GUI Window",sf::Style::Default,settings);
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

        // Main Program Loop
        while(window.isOpen() && gui_window.isOpen()){
                // Capture events in our main window
                sf::Event event;

                // Main event loop that cycles through event queue
                while(window.pollEvent(event)){
                        // Our close event.
                        // Note: We only have a 'minimize' button
                        //       in our window right now, so this event is not
                        //       going to fire.
                        if(event.type == sf::Event::Closed){
                                window.close();
                                exit(EXIT_SUCCESS);
                        }

                        // Capture any keys that are released
                        else if(event.type == sf::Event::KeyReleased){
                                std::cout << "Key Pressed" << std::endl;
                                // Check if the escape key is pressed.
                                if(event.key.code == sf::Keyboard::Escape){
                                        std::cout << "escape Pressed" << std::endl;
                                        window.close();
                                        exit(EXIT_SUCCESS);
                                }
                        }
                }

        // Capture input from the nuklear GUI
        nk_input_begin(ctx);
        while(gui_window.pollEvent(event)){
                        // Our close event.
                        // Note: We only have a 'minimize' button
                        //       in our window right now, so this event is not
                        //       going to fire.
                        if(event.type == sf::Event::Closed){
                nk_sfml_shutdown();
                                gui_window.close();
                                exit(EXIT_SUCCESS);
                        }

                        // Capture any keys that are released
                        else if(event.type == sf::Event::KeyReleased){
                                std::cout << "Key Pressed" << std::endl;
                                // Check if the escape key is pressed.
                                if(event.key.code == sf::Keyboard::Escape){
                    nk_sfml_shutdown();
                                    gui_window.close();
                                        exit(EXIT_SUCCESS);
                                }
                        }
            //else if(event.type == sf::Event::Resized){
            //    glViewport(0, 0, event.size.width, event.size.height);
            //}
            nk_sfml_handle_event(&event);
        }

        // Complete input from nuklear GUI
        nk_input_end(ctx);

        // Draw our GUI
        drawLayout(ctx,bg);

                // Capture an event outside of our event loop
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                std::cout << "Mouse left" << std::endl;
                        // Capture mouse coordinates
            sf::Vector2i coords = sf::Mouse::getPosition(window);
                        if(coords.x < WINDOW_WIDTH && coords.y < WINDOW_HEIGHT && coords.x > 0 && coords.y > 0){
                // Now we can modify our image based on the mouse position
                // and our current paint brush.

                int color = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
                if(op==RED){
                    image.setPixel(coords.x,coords.y,sf::Color::Red);
                }
                if(op==BLACK){
                    image.setPixel(coords.x,coords.y,sf::Color::Black);
                }
                if(op==GREEN){
                    image.setPixel(coords.x,coords.y,sf::Color::Green);
                }
				if(op==BLUE){
					image.setPixel(coords.x, coords.y,sf::Color::Blue);
				}
                // We load into our texture the modified mpixels
                texture.loadFromImage(image);
            }
                }

        // OpenGL is the background rendering engine,
        // so we are going to clear our GUI graphics system.
                gui_window.setActive(true);
        gui_window.clear();
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        glClear(GL_COLOR_BUFFER_BIT);
        nk_sfml_render(NK_ANTI_ALIASING_ON);
        gui_window.display();

        // Clear our window
                window.setActive(true);
        window.clear();
        // Display the GUI
        // Note that this happens after our window drawing so that
        // the GUI will draw on top.
        window.draw(sprite);
                // Draw our sprite
                // Display on our window any sprites or any shapes we have drawn.
        window.display();
        }

    // Terminate the Nuklear GUI library
    nk_sfml_shutdown();

        return 0;

}
