#include "parser.hpp"

int main()
{
    Parser parser;

    // attempt to parse
    try {
        parser.parse();
    }

    // in event of invalid arg, output relevant error
    catch (const std::invalid_argument ia) {
        std::cout << ia.what() << std::endl;
    }

    return 0;
}