#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
class Parser
{
    public:
    Parser()
    {
        std::string str;
        std::cout<<"Enter infix string: ";
        std::cin >> str;//user input gathered when class constructed
        stream = std::stringstream(str);
        lookAhead = stream.get();
    }
    void parse()
    {
        Expr();
        PrintTranslatedString();
    }
    private:
    char lookAhead;//char that is being handled
    std::string translated;//char thats being output
    std::stringstream stream;//stream of user's input
    void Display(char terminal)
    {
        translated += terminal;
    }
    void PrintTranslatedString()
    {
        std::cout<<translated<<std::endl;
    }
    std::string ErrorMessage(char lookAhead)
    {
        return "Syntax Error near: " + std::string(1,lookAhead);//identifies location of invalid char
    }
     void Match(char terminal) {
        if (terminal == lookAhead) {
            lookAhead = stream.get();
        }
        else {
            throw std::invalid_argument(ErrorMessage(lookAhead));
        }
    }
    /* digit Rules
    digit -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    */
    void Digit()
    {
        Display(lookAhead);
        Match(lookAhead);
    }
    /* factor Rules
    factor -> (expr)
             |digit
    */
    void Factor()
    {
        if(isdigit(lookAhead))
            Digit();
        else if(lookAhead == '(')
        {
            Match('(');
            Expr();
            Match(')');
        }
        else
        {
            throw std::invalid_argument(ErrorMessage(lookAhead));
        }
    }
    /* term Rules
    term -> term * factor
           |term / factor
           |factor
    */
    void Term()
    {
        Factor();
        if(lookAhead == '*')
        {
            Match('*');
            Factor();
            Display('*');
        }
        else if(lookAhead == '/')
        {
            Match('/');
            Factor();
            Display('/');
        }
    }
    /* expr Rules
    expr -> expr + term
           |expr - term
           |term
    */
    void Expr()
    {
        Term();
        while(true)
        {
            if(lookAhead == '+')
            {
                Match('+');
                Term();
                Display('+');
            }
            else if(lookAhead == '-')
            {
                Match('-');
                Term();
                Display('-');
            }
            else return;
        }
    }

};
