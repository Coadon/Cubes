#include <spdlog/sinks/stdout_color_sinks.h>
#include "GLFW/glfw3.h"
#include "common.hpp"
#include "window.hpp"

int main(int argc, char *argv[]) {

    spdlog::stdout_color_mt("stdout");
    LOGGER.set_pattern("[%H:%M:%S.%e] [%n] [%^-%L-%$] [%t] %v");
    LOGGER.info("{}", "Hello World!");

    windowInit();
    windowLoop(
        [] {
            if (window.key[GLFW_KEY_ESCAPE].down) {
                windowEnd();
            }
        },
        [] {}, [] {}, [] {}, [] {});

    return EXIT_SUCCESS;
}
