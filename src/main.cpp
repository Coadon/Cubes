#include <iomanip>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "GLFW/glfw3.h"
#include "common.hpp"
#include "window.hpp"

void update() {
    if (window.key[GLFW_KEY_ESCAPE].down) windowEnd();
}

int main(int argc, char *argv[]) {

    spdlog::stdout_color_mt("stdout");
    LOGGER.set_pattern("[%H:%M:%S.%e] [%n] [%^-%L-%$] [%t] %v");
    LOGGER.set_level(spdlog::level::level_enum::debug);

    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
        LOGGER.info("Session of {}", oss.str());
    }

    windowInit();
    windowLoop(update, [] {}, [] {}, [] {}, [] {});

    return EXIT_SUCCESS;
}
