#include <iostream>
#include <regex>
#include <string>

std::string reverse_non_identifiers(const std::string& line) {
    // Regular expression to match identifiers
    std::regex identifier_pattern(R"(\b[a-zA-Z_]\w*\b)");

    // Split the line into words
    std::stringstream ss(line);
    std::string word, new_line;
    while (ss >> word) {
        std::smatch match;
        if (std::regex_match(word, match, identifier_pattern)) {
            new_line += word + " ";
        } else {
            std::string reversed_word(word.rbegin(), word.rend());
            new_line += reversed_word + " ";
        }
    }

    // Remove trailing space and return the reversed line
    new_line.pop_back();
    return new_line;
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::string reversed_line = reverse_non_identifiers(line);
        std::cout << reversed_line << std::endl;
    }
    return 0;
}

