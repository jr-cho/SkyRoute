#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <iostream>
#include <cstring>

inline void getAirportCode(char* code) {
    std::string input;
    std::cin >> input;
    strncpy(code, input.c_str(), 3);
    code[3] = '\0';
}

inline int getChoice() {
    int option;
    std::cout << "\nEnter choice: ";
    std::cin >> option;
    return option;
}

#endif // INPUT_HANDLER_H

