#include "note_secure/core.hpp"

#include <iostream>

int main() {
    std::cout << "Note Secure v" << note_secure::application_version() << '\n';
    std::cout << "Project setup is ready.\n";
    return 0;
}
