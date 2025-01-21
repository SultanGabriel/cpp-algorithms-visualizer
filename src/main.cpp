#include "app.h"
#include <iostream>

int main() {
    try {
        App app;
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}

