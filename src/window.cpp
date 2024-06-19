#include <iostream>

#include <glad.h>
#include "glm/common.hpp"
#include "window.hpp"
#include "common.hpp"

using namespace std;

struct Window window;

bool windowInit() {
    glfwSetErrorCallback(
        [](int code, const char *desc) { LOGGER.error("GLFW Error {0}: {1}", code, desc); });

    if (!glfwInit()) {
        LOGGER.critical("Failed to initialize GLFW!");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window.handle = glfwCreateWindow(window.width, window.height, "Hello World", NULL, NULL);
    if (window.handle == NULL) {
        LOGGER.critical("Failed to create GLFW window!");
        glfwTerminate();
        return false;
    }

    glfwShowWindow(window.handle);
    glfwMakeContextCurrent(window.handle);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        LOGGER.critical("Failed to initialize GLAD!");
        glfwTerminate();
        return false;
    }

    LOGGER.debug("Initialized graphics services");
    LOGGER.info("Backend Graphics: Using GL {}", (char*) glGetString(GL_VERSION));

    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window.handle, [](GLFWwindow *, int width, int height) {
        window.width = width;
        window.height = height;
        glViewport(0, 0, width, height);
    });

    glfwSetCursorPosCallback(window.handle, [](GLFWwindow *, double xpos, double ypos) {
        window.mouse.position.x = xpos;
        window.mouse.position.y = ypos;

        // Reversed since y-coords range from bottom to top
        window.mouse.delta.x = xpos - window.mouse.last.x;
        window.mouse.delta.y = window.mouse.last.y - ypos;

        window.mouse.last.x = xpos;
        window.mouse.last.y = ypos;
    });

    glfwSetScrollCallback(window.handle, [](GLFWwindow *, double xoffset, double yoffset) {
        window.mouse.scroll = yoffset;
    });

    glfwSetMouseButtonCallback(window.handle, [](GLFWwindow *, int button, int action, int mods) {
        if (button < 0) {
            return;
        }

        switch (action) {
        case GLFW_PRESS:
            window.mouse.buttons[button].down = true;
            break;
        case GLFW_RELEASE:
            window.mouse.buttons[button].down = false;
            break;
        default:
            break;
        }
    });

    // clang-format off
    glfwSetKeyCallback(window.handle, [](GLFWwindow *, int key, int scancode, int action, int mods) {
        if (key < 0) {
            return;
        }

        switch (action) {
        case GLFW_PRESS:
            window.key[key].down = true;
            break;
        case GLFW_RELEASE:
            window.key[key].down = false;
            break;
        default:
            break;
        }
    });
    // clang-format on

    return true;
}

static void _buttonArrayUpdate(size_t n, struct Window::Button *buttons) {
    for (size_t i = 0; i < n; i++) {
        buttons[i].pressed = buttons[i].down && !buttons[i].last;
        buttons[i].last = buttons[i].down;
    }
}

#define SEC_PER_TICK 0.05
#define COUNTERS_RESET_TIME 1
void windowLoop(function<void()> update, function<void()> render, function<void()> tick,
                function<void()> start, function<void()> end) {
    f32 lastFrame = 0.0f;
    f32 curntFrame = 0.0f;

    f32 lapsesec = 0.0f;
    u32 frmctrsec = 0;
    u32 tikctrsec = 0;

    f32 ticktime = 0.0f;
    f32 tickleft = 0.0f;

    start();

    // Render Loop
    while (!glfwWindowShouldClose(window.handle)) {
        curntFrame = glfwGetTime();
        window.dt = curntFrame - lastFrame;
        lastFrame = curntFrame;

        lapsesec += window.dt;
        if (lapsesec >= COUNTERS_RESET_TIME) {
            window.fps = frmctrsec;
            window.tps = tikctrsec;
            frmctrsec = 0;
            tikctrsec = 0;
            lapsesec = 0;
        } else
            frmctrsec++;

        ticktime = window.dt + tickleft;
        while (ticktime > SEC_PER_TICK) {
            tikctrsec++;
            tick();
            ticktime -= SEC_PER_TICK;
        }
        tickleft = std::max(ticktime, 0.0f);


        update();
        render();

        _buttonArrayUpdate(GLFW_MOUSE_BUTTON_LAST, window.mouse.buttons);
        _buttonArrayUpdate(GLFW_KEY_LAST, window.key);
        window.mouse.delta = glm::vec2(0.0f);
        window.mouse.scroll = 0.0f;

        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }

    LOGGER.debug("{}", "Terminating Routine");

    end();

    // Destroy sequence
    glfwDestroyWindow(window.handle);
    glfwTerminate();
}

void windowEnd() {
    glfwSetWindowShouldClose(window.handle, true);
}

bool getMouseGrabbed() {
    return glfwGetInputMode(window.handle, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void setMouseGrabbed(bool grabbed) {
    glfwSetInputMode(window.handle, GLFW_CURSOR,
                     grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

