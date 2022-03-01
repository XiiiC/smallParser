#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>

class Parser {
public:
    // take input and convert to stringstream
    Parser() {
        std::string str;
        std::cout << "Enter infix string: ";
        std::cin >> str; //user input gathered when class constructed
        stream = std::stringstream(str);
        lookAhead = stream.get();
    }

    // parse input and output result
    void parse() {
        Expr();
        PrintTranslatedString();
    }

private:
    char lookAhead; //char that is being handled
    std::string translated; //string that is being outputted
    std::stringstream stream; //stream of user's input

    // add character that's being handled to terminal
    void Display(char terminal) {
        translated += terminal;
    }

    // output final string after translation
    void PrintTranslatedString() {
        std::cout << translated << std::endl;
    }

    // show error message
    std::string ErrorMessage(char lookAhead) {
        return "Syntax Error near: " + std::string(1,lookAhead); //identifies location of invalid char
    }

    // check next value is expected and move along input
    void Match(char terminal) {
        if (terminal == lookAhead) {
            lookAhead = stream.get();
        }

        // if value unexpected, throw error
        else {
            throw std::invalid_argument(ErrorMessage(lookAhead));
        }
    }

    /* digit Rules
    digit -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    */
    // add digit to translated string and move to next value
    void Digit() {
        Display(lookAhead);
        Match(lookAhead);
    }

    /* factor Rules
    factor -> (expr)
             |digit
    */
    // handle characters inputted
    void Factor() {
        // if char is a digit, use Digit() to store and move to next char
        if (isdigit(lookAhead)) {
            Digit();
        }

        // if char is a bracket, recurse through its contents and evaluate
        // check for closing bracket and then move onto next char
        else if (lookAhead == '(') {
            Match('(');
            Expr();
            Match(')');
        }

        // otherwise, throw a syntax error
        else {
            throw std::invalid_argument(ErrorMessage(lookAhead));
        }
    }

    /* term Rules
    term -> term * factor
           |term / factor
           |factor
    */
    // handle factor
    void Term() {
        Factor();

        // if next char is * or /, move to next character, validate and add to output
        if (lookAhead == '*' || lookAhead == '/') {
            Match(lookAhead);
            Factor();
            Display(lookAhead);
        }
    }
    /* expr Rules
    expr -> expr + term
           |expr - term
           |term
    */
    // handle terms first
    void Expr() {
        Term();

        // cache lookAhead's current value for reference
        while (true) {
            char cachedLookAhead = lookAhead;

            // if next char is + or -, move to next character, validate and add to output
            if (cachedLookAhead == '+' || cachedLookAhead == '-') {
                Match(cachedLookAhead);
                Term();
                Display(cachedLookAhead);
                continue;
            }
            
            // if next char isn't + or -, expression is complete
            return;
        }
    }
};
