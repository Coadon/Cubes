#include "common.hpp"
#include "sinks/stdout_color_sinks.h"

int main(int argc, char *argv[]) {

    spdlog::stdout_color_mt("main");
    LOGGER.set_pattern("[%H:%M:%S %z] [%n] [%^-%L-%$] [%t] %v");

    LOGGER.info("Hello World!");

    /*
    LOGGER->info(
        "Let's not put using namespace in headers anymore. ALright!? :) Helo, my bigbig World! :) "
        "Greetings!? It's now 1729 in the flight to San Francisco -- Dec 26 2023.");
    */

    return EXIT_SUCCESS;
}
