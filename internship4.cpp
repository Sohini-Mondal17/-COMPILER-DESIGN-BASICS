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
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back(worker, i);
    }
    
    // Wait for completion
    for (auto &t : threads) {
        t.join();
    }
    
    // Write results
    for (auto &result : results) {
        outFile << result;
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    std::cout << (compress ? "Compression" : "Decompression") 
              << " with " << threadCount << " threads took: " 
              << duration.count() << " ms\n";
}

// Single-threaded version for comparison
void processFileSingleThread(const std::string &inputPath,
                           const std::string &outputPath,
                           bool compress) {
    std::ifstream inFile(inputPath, std::ios::binary);
    if (!inFile) throw std::runtime_error("Cannot open input file");
    
    std::string input((std::istreambuf_iterator<char>(inFile)), 
                     std::istreambuf_iterator<char>());
    
    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile) throw std::runtime_error("Cannot open output file");
    
    auto startTime = std::chrono::high_resolution_clock::now();
    std::string result = compress ? rleCompress(input) : rleDecompress(input);
    auto endTime = std::chrono::high_resolution_clock::now();
    
    outFile << result;
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << (compress ? "Compression" : "Decompression") 
              << " (single-threaded) took: " 
              << duration.count() << " ms\n";
}

void validateFiles(const std::string &original, const std::string &decompressed) {
    std::ifstream origFile(original, std::ios::binary);
    std::ifstream decFile(decompressed, std::ios::binary);
    
    std::string origContent((std::istreambuf_iterator<char>(origFile)), 
                std::istreambuf_iterator<char>());
    std::string decContent((std::istreambuf_iterator<char>(decFile)), 
                std::istreambuf_iterator<char>());
    
    if (origContent == decContent) {
        std::cout << "Validation successful: files match\n";
    } else {
        std::cout << "Validation failed: files differ\n";
        std::cout << "Original size: " << origContent.size() << "\n";
        std::cout << "Decompressed size: " << decContent.size() << "\n";
    }
}

int main() {
    try {
        const std::string inputFile = "input.txt";
        const std::string compressedFile = "compressed.rle";
        const std::string decompressedFile = "decompressed.txt";
        const int threadCount = 4; // Adjust based on your CPU cores
        
        // Generate test file if needed
        {
            std::ofstream testFile(inputFile);
            for (int i = 0; i < 100000; i++) {
                testFile << "This is a test line with some repeated characters aaaaaaaand some more...\n";
            }
        }
        
        std::cout << "=== Single-threaded ===\n";
        processFileSingleThread(inputFile, compressedFile, true);
        processFileSingleThread(compressedFile, decompressedFile, false);
        validateFiles(inputFile, decompressedFile);
        
        std::cout << "\n=== Multi-threaded (" << threadCount << " threads) ===\n";
        processFile(inputFile, compressedFile, true, threadCount);
        processFile(compressedFile, decompressedFile, false, threadCount);
        validateFiles(inputFile, decompressedFile);
        
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
