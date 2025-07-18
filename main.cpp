#include <iostream>

int main() {
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string RESET = "\033[0m"; // Resets all attributes

    std::cout << RED << "This is red text." << RESET << std::endl;
    std::cout << GREEN << "This is green text." << RESET << std::endl;
    std::cout << YELLOW << "This is yellow text." << RESET << std::endl;
    std::cout << BLUE << "This is blue text." << RESET << std::endl;
    std::cout << MAGENTA << "This is magenta text." << RESET << std::endl;
    std::cout << CYAN << "This is cyan text." << RESET << std::endl;
    std::cout << RED << "Bold Red " << "\033[1m" << "and really bold!" << RESET << std::endl;
    std::cout << "Normal text." << std::endl;
    return 0;
}