#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "token.h"

namespace Scanner
{

    class Scanner
    {
    public:
        Scanner(const std::vector<std::string> &inputLines);
        std::vector<Token *> tokenize();

    private:
        const std::vector<std::string> &inputLines; // Reference to input lines
        unsigned int vPos;                          // vertical position
        unsigned int hPos;                          // horizontal position
        std::string currentToken;                   // Current token being constructed

        char getCurrentChar();                                 // Helper function to get the current character
        bool isCharInSet(char ch, const std::string &charSet); // Helper function to check if character is in the character set
        std::string findIdentifierOrPredefineToken();          // function to find identifier or pre-define token
        std::string findSingleLineComment();                   // function to find single line comment
        std::string findMultiLineComment();                    // function to find multi line comment

        // Define character sets
        const std::string spaceChars = " \f\r\t";                                                    // Space characters
        const std::string digitChars = "0123456789";                                                 // Digit characters
        const std::string identifierChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"; // Identifier characters
    };
}

#endif // SCANNER_H
