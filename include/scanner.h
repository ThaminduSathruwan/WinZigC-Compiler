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
        char getCharFromShiftPosition(int shift);              // Helper function to get char in a position by giving shift to current position
        bool isCharInSet(char ch, const std::string &charSet); // Helper function to check if character is in the character set
        std::string findIdentifierOrPredefineToken();          // function to find identifier or pre-define token
        std::string findSingleLineComment();                   // function to find single line comment
        std::string findMultiLineComment();                    // function to find multi line comment
        std::string findNewLine();                             // function find new line
        std::string findInteger();                             // function to find integer
        std::string findWhiteSpace();                          // function to find white spaces
        std::string findChar();                                // function to find char
        std::string findString();                              // function to find string

        // Define character sets
        const std::string spaceChars = " \f\r\t";                                                    // Space characters
        const std::string digitChars = "0123456789";                                                 // Digit characters
        const std::string identifierChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"; // Identifier characters
    };
}

#endif // SCANNER_H
