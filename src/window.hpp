#pragma once

#include <GLFW/glfw3.h>
#include "common.hpp"

/**
 * A window system
 */
struct Window {
    struct Button {
        bool down, pressed, last;
    };

    GLFWwindow *handle;

    f32 dt, fps, tps;

    u32 width = 800;
    u32 height = 600;

    // Input Listeners
    // ---------------
    struct {
        struct Window::Button buttons[GLFW_MOUSE_BUTTON_LAST];
        glm::vec2 position, delta, last;
        f64 scroll; // Scroll offset
    } mouse;

    struct Window::Button key[GLFW_KEY_LAST];
} extern window;

/// Called once
bool windowInit();

/// Called once
void windowLoop(
        std::function<void()> update,
        std::function<void()> render,
        std::function<void()> tick,
        std::function<void()> start,
        std::function<void()> end);

/// Called once
void windowEnd();

bool getMouseGrabbed();
void setMouseGrabbed(bool);

