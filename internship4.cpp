# MULTITHREADED-FILE-COMPRESSION-TOOL

*COMPANY*: CODTECH IT SOLUTIONS

*NAME*: SOHINI MONDAL

*INTERN ID*: CT04DM429

*DOMAIN*: C++ PROGRAMMING

*DURATION*: 4 WEEKS

*MENTOR*: NELLA SANTOSH KUMAR

*DESCRIPTION*:This C++ program implements a simple arithmetic expression evaluator using a recursive descent parser approach. The evaluator takes a string input from the user, representing a mathematical expression, and computes its result while respecting operator precedence and handling nested expressions using parentheses. The parsing and evaluation logic is encapsulated in a class named Parser, which performs the recursive analysis of the expression.

The Parser class has two key private members: a std::string input, which stores the user-provided expression, and a size_t pos, which tracks the current position of parsing within the string. The constructor initializes these members by assigning the input string and setting the initial position to zero.

The main public method in the class is parse(). It initiates the parsing process by calling the expression() function, which begins evaluating the expression from left to right while honoring operator precedence. After evaluation, parse() checks if any characters are left unprocessed. If there are, it throws a std::runtime_error indicating that unexpected characters were found, signaling a malformed expression.

To support parsing, several helper functions are defined. The peek() method skips over any whitespace and returns the current character without advancing the position. This allows the parser to ignore spaces and focus only on meaningful symbols. The get() function retrieves the current character by calling peek() and moves the parsing position forward. The number() function is used to extract numeric values from the input. It collects digits and optional decimal points into a string and then converts this string to a floating-point number using the std::stod function.

The core parsing logic is implemented through three functions: factor(), term(), and expression(), each representing a level of operator precedence. The factor() function handles the most basic elements, such as numbers and expressions enclosed in parentheses. If an opening parenthesis is encountered, it recursively evaluates the subexpression and expects a matching closing parenthesis. The term() function processes multiplication and division. It starts with a factor and continues evaluating additional factors as long as * or / operators are found. The expression() function manages addition and subtraction, calling term() and applying + or - operators as needed.

The main() function prompts the user to input an arithmetic expression. It reads the full line using std::getline() and passes it to a Parser object. It then calls parse() to evaluate the expression. If parsing or evaluation fails due to syntax errors—such as missing parentheses or invalid characters—a runtime exception is caught and the error message is displayed.

In conclusion, the program supports basic arithmetic operations: addition, subtraction, multiplication, division, floating-point numbers, and parentheses for grouping. Whitespace is ignored, making it tolerant to various input styles. This program is a clear demonstration of recursive descent parsing and provides a practical example of building a calculator-like parser in C++.

*OUTPUT*:


