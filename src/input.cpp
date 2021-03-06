#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"

bool cannon_keyboard_input = true;
bool drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
     // Function is called first on GLFW_PRESS.

    if (game_paused) return;

    if (action == GLFW_RELEASE) {
//        switch (key) {
//        case GLFW_KEY_C:
//            rectangle_rot_status = !rectangle_rot_status;
//            break;
//        case GLFW_KEY_P:
//            triangle_rot_status = !triangle_rot_status;
//            break;
//        case GLFW_KEY_X:
//            // do something ..
//            break;
//        default:
//            break;
//        }
    }
    else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        case GLFW_KEY_E:
            cannon_keyboard_input = !cannon_keyboard_input;
            break;
        case GLFW_KEY_N:
            game_rate -= 0.25*game_rate;
            reset_game_rate();
            break;
        case GLFW_KEY_M:
            game_rate += 0.25*game_rate;
            reset_game_rate();
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
    if (key == 'P' || key == 'p') game_paused = !game_paused;

    if (game_paused) return;

    switch (key) {
    case 'Q':
    case 'q':
        quit(window);
        break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{
    if (game_paused) return;

    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_PRESS) {
                old_cki = cannon_keyboard_input;
                drag_pan = true;
                cannon_keyboard_input = true;
            } else if (action == GLFW_RELEASE) {
                cannon_keyboard_input = old_cki;
                drag_pan = false;
                drag_oldx = drag_oldy = -1;
            }
            break;
//        case GLFW_MOUSE_BUTTON_RIGHT:
//            if (action == GLFW_RELEASE) {
//                rectangle_rot_dir *= -1;
//            }
//            break;
        default:
            break;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (screen_zoom < 1) { screen_zoom = 1; return; }
    screen_zoom += yoffset/40;
    reset_screen();
}
