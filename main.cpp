#include "parser.hpp"

int main()
{
    Parser parser;
    try
    {
        parser.parse();
    }
    catch(const std::invalid_argument ia)
    {
        std::cout << ia.what() << '\n';
    }
    return 0;
    
}
