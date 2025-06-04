#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Parser {
    std::string input;
    size_t pos;

public:
    Parser(const std::string& str) : input(str), pos(0) {}

    double parse() {
        double result = expression();
        if (pos < input.length()) {
            throw std::runtime_error("Unexpected characters at end");
        }
        return result;
    }

private:
    char peek() {
        while (pos < input.length() && isspace(input[pos])) pos++;
        return pos < input.length() ? input[pos] : '\0';
    }

    char get() {
        char c = peek();
        if (c != '\0') pos++;
        return c;
    }

    double number() {
        std::string num;
        while (isdigit(peek()) || peek() == '.') {
            num += get();
        }
        return std::stod(num);
    }

    double factor() {
        char c = peek();
        if (c == '(') {
            get(); // skip '('
            double result = expression();
            if (get() != ')') {
                throw std::runtime_error("Missing closing parenthesis");
            }
            return result;
        } else if (isdigit(c) || c == '.') {
            return number();
        } else {
            throw std::runtime_error("Unexpected character in factor");
        }
    }

    double term() {
        double result = factor();
        while (true) {
            char op = peek();
            if (op == '*' || op == '/') {
                get(); // consume operator
                double right = factor();
                if (op == '*') result *= right;
                else if (op == '/') result /= right;
            } else {
                break;
            }
        }
        return result;
    }

    double expression() {
        double result = term();
        while (true) {
            char op = peek();
            if (op == '+' || op == '-') {
                get(); // consume operator
                double right = term();
                if (op == '+') result += right;
                else if (op == '-') result -= right;
            } else {
                break;
            }
        }
        return result;
    }
};

int main() {
    std::string line;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, line);

    try {
        Parser parser(line);
        double result = parser.parse();
        std::cout << "Result: " << result << std::endl;
    } catch (std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
