#include <iostream>
#include <vector>
#include <string>
#include "../include/scanner.h"
#include "token.h"

namespace Scanner
{
    Scanner::Scanner(const std::vector<std::string> &inputLines) : inputLines(inputLines), vPos(0), hPos(0) {}

    std::vector<Token *> Scanner::tokenize()
    {
        std::vector<Token *> tokens;

        while (vPos < inputLines.size())
        {
            // const std::string &line = inputLines[vPos];
            // std::cout << "Incoming String: " << line << std::endl; // Print each string from the array.

            while (hPos < inputLines[vPos].size())
            {

                const std::string &line = inputLines[vPos];

                // std::cout << "current hPos char" << line[hPos] << std::endl;
                std::string identifierToken = findIdentifierOrPredefineToken();

                if (!identifierToken.empty())
                {
                    if (identifierToken == "program")
                    {
                        tokens.push_back(new Token(TokenType::PROGRAM, identifierToken, hPos - 6, vPos));
                    }
                    else if (identifierToken == "var")
                    {
                        tokens.push_back(new Token(TokenType::VAR, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "const")
                    {
                        tokens.push_back(new Token(TokenType::CONST, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "type")
                    {
                        tokens.push_back(new Token(TokenType::TYPE, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "function")
                    {
                        tokens.push_back(new Token(TokenType::FUNCTION, identifierToken, hPos - 7, vPos));
                    }
                    else if (identifierToken == "return")
                    {
                        tokens.push_back(new Token(TokenType::RETURN, identifierToken, hPos - 5, vPos));
                    }
                    else if (identifierToken == "begin")
                    {
                        tokens.push_back(new Token(TokenType::BEGIN, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "end")
                    {
                        tokens.push_back(new Token(TokenType::END, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "output")
                    {
                        tokens.push_back(new Token(TokenType::OUTPUT, identifierToken, hPos - 5, vPos));
                    }
                    else if (identifierToken == "if")
                    {
                        tokens.push_back(new Token(TokenType::IF, identifierToken, hPos - 1, vPos));
                    }
                    else if (identifierToken == "then")
                    {
                        tokens.push_back(new Token(TokenType::THEN, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "else")
                    {
                        tokens.push_back(new Token(TokenType::ELSE, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "while")
                    {
                        tokens.push_back(new Token(TokenType::WHILE, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "do")
                    {
                        tokens.push_back(new Token(TokenType::DO, identifierToken, hPos - 1, vPos));
                    }
                    else if (identifierToken == "case")
                    {
                        tokens.push_back(new Token(TokenType::CASE, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "of")
                    {
                        tokens.push_back(new Token(TokenType::OF, identifierToken, hPos - 1, vPos));
                    }
                    else if (identifierToken == "otherwise")
                    {
                        tokens.push_back(new Token(TokenType::OTHERWISE, identifierToken, hPos - 8, vPos));
                    }
                    else if (identifierToken == "repeat")
                    {
                        tokens.push_back(new Token(TokenType::REPEAT, identifierToken, hPos - 5, vPos));
                    }
                    else if (identifierToken == "for")
                    {
                        tokens.push_back(new Token(TokenType::FOR, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "until")
                    {
                        tokens.push_back(new Token(TokenType::UNTIL, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "loop")
                    {
                        tokens.push_back(new Token(TokenType::LOOP, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "pool")
                    {
                        tokens.push_back(new Token(TokenType::POOL, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "exit")
                    {
                        tokens.push_back(new Token(TokenType::EXIT, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "mod")
                    {
                        tokens.push_back(new Token(TokenType::MOD, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "and")
                    {
                        tokens.push_back(new Token(TokenType::AND, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "or")
                    {
                        tokens.push_back(new Token(TokenType::OR, identifierToken, hPos - 1, vPos));
                    }
                    else if (identifierToken == "not")
                    {
                        tokens.push_back(new Token(TokenType::NOT, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "read")
                    {
                        tokens.push_back(new Token(TokenType::READ, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "succ")
                    {
                        tokens.push_back(new Token(TokenType::SUCC, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "pred")
                    {
                        tokens.push_back(new Token(TokenType::PRED, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "chr")
                    {
                        tokens.push_back(new Token(TokenType::CHAR, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "ord")
                    {
                        tokens.push_back(new Token(TokenType::ORD, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "eof")
                    {
                        tokens.push_back(new Token(TokenType::EOF_TOKEN, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "true")
                    {
                        tokens.push_back(new Token(TokenType::TRUE, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "false")
                    {
                        tokens.push_back(new Token(TokenType::FALSE, identifierToken, hPos - 4, vPos));
                    }
                    else
                    {
                        tokens.push_back(new Token(TokenType::IDENTIFIER, identifierToken, hPos - identifierToken.size() + 1, vPos));
                    }
                }

                std::string integerToken = findInteger();

                if (!integerToken.empty())
                {
                    tokens.push_back(new Token(TokenType::INTEGER, integerToken, hPos - integerToken.size() + 1, vPos));
                }

                std::string charToken = findChar();

                if (!charToken.empty())
                {
                    tokens.push_back(new Token(TokenType::CHAR, charToken, hPos - charToken.size() + 1, vPos));
                }

                std::string stringToken = findString();

                if (!stringToken.empty())
                {
                    tokens.push_back(new Token(TokenType::STRING, stringToken, hPos - stringToken.size() + 1, vPos));
                }

                // swap
                if (getCurrentChar() == ':' && getCharFromShiftPosition(1) == '=' && getCharFromShiftPosition(':'))
                {
                    tokens.push_back(new Token(TokenType::SWAP, line.substr(hPos, 3), hPos, vPos));
                    hPos += 3;
                }

                // assignment operator
                if (getCurrentChar() == ':' && getCharFromShiftPosition(1) == '=')
                {
                    tokens.push_back(new Token(TokenType::ASSIGN, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // dots for case expression
                if (getCurrentChar() == '.' && getCharFromShiftPosition(1) == '.')
                {
                    tokens.push_back(new Token(TokenType::CASE_DOTS, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // less than or equal binary operator
                if (getCurrentChar() == '<' && getCharFromShiftPosition(1) == '=')
                {
                    tokens.push_back(new Token(TokenType::LESS_THAN_EQUAL, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // not equal binary operator
                if (getCurrentChar() == '<' && getCharFromShiftPosition(1) == '>')
                {
                    tokens.push_back(new Token(TokenType::NOT_EQUAL, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // less than binary operator
                if (getCurrentChar() == '<')
                {
                    tokens.push_back(new Token(TokenType::LESS_THAN, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // greater than or equal binary operator
                if (getCurrentChar() == '>' && getCharFromShiftPosition(1) == '=')
                {
                    tokens.push_back(new Token(TokenType::GREATER_THAN_EQUAL, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // greater than binary operator
                if (getCurrentChar() == '>')
                {
                    tokens.push_back(new Token(TokenType::GREATER_THAN, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // equal binary operator
                if (getCurrentChar() == '=')
                {
                    tokens.push_back(new Token(TokenType::EQUAL, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // colon
                if (getCurrentChar() == ':')
                {
                    tokens.push_back(new Token(TokenType::COLON, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // semi colon
                if (getCurrentChar() == ';')
                {
                    tokens.push_back(new Token(TokenType::SEMICOLON, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // single dot
                if (getCurrentChar() == '.')
                {
                    tokens.push_back(new Token(TokenType::PERIOD, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // comma
                if (getCurrentChar() == ',')
                {
                    tokens.push_back(new Token(TokenType::COMMA, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // opening bracket
                if (getCurrentChar() == '(')
                {
                    tokens.push_back(new Token(TokenType::LEFT_PAREN, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // closing bracket
                if (getCurrentChar() == ')')
                {
                    tokens.push_back(new Token(TokenType::RIGHT_PAREN, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // plus
                if (getCurrentChar() == '+')
                {
                    tokens.push_back(new Token(TokenType::PLUS, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // minus
                if (getCurrentChar() == '-')
                {
                    tokens.push_back(new Token(TokenType::MINUS, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // multiply
                if (getCurrentChar() == '*')
                {
                    tokens.push_back(new Token(TokenType::MULTIPLY, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // divide
                if (getCurrentChar() == '/')
                {
                    tokens.push_back(new Token(TokenType::DIVIDE, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                std::string singleLineComment = findSingleLineComment();

                std::string multiLineComment = findMultiLineComment();

                std::string newLine = findNewLine();

                std::string whiteSpace = findWhiteSpace();
            }
            hPos = 0;
            vPos++;
        }

        return tokens;
    }

    std::string Scanner::findSingleLineComment()
    {
        int start = hPos;
        if (getCurrentChar() == '#')
        {
            while (getCurrentChar() != '\n')
            {
                hPos++;
            }
            return inputLines[vPos].substr(start, hPos - start);
        }
        return "";
    }

    std::string Scanner::findMultiLineComment()
    {
        std::string multiLineComment = "";
        if (getCurrentChar() == '{')
        {
            while (getCurrentChar() != '}')
            {
                multiLineComment.append(inputLines[vPos]);
                vPos++;
            }
            multiLineComment.append(inputLines[vPos]);
            vPos++;
            hPos = 0;
        }
        return multiLineComment;
    }

    std::string Scanner::findNewLine()
    {
        if (getCurrentChar() == '\n')
        {
            hPos++;
            vPos++;
        }
        return "";
    }

    std::string Scanner::findInteger()
    {
        int start = hPos;
        if (isCharInSet(getCurrentChar(), digitChars))
        {
            while (isCharInSet(getCurrentChar(), digitChars))
            {
                hPos++;
            }
            return inputLines[vPos].substr(start, hPos - start);
        }
        return "";
    }

    std::string Scanner::findWhiteSpace()
    {
        if (isCharInSet(getCurrentChar(), spaceChars))
        {
            while (isCharInSet(getCurrentChar(), spaceChars))
            {
                hPos++;
            }
        }
        return "";
    }

    std::string Scanner::findChar()
    {
        int start = hPos;
        if (getCurrentChar() == '\'' && getCharFromShiftPosition(1) != '\'' && getCharFromShiftPosition(2) == '\'')
        {
            hPos += 3;
            return inputLines[vPos].substr(start, hPos - start);
        }
        return "";
    }

    std::string Scanner::findString()
    {
        int start = hPos;
        if (getCurrentChar() == '\"')
        {
            hPos++;
            while (getCurrentChar() != '\"')
            {
                hPos++;
            }
            hPos++;
            return inputLines[vPos].substr(start, hPos - start);
        }
        return "";
    }

    std::string Scanner::findIdentifierOrPredefineToken()
    {
        int start = hPos;
        if (isCharInSet(getCurrentChar(), identifierChars))
        {
            while (isCharInSet(getCurrentChar(), identifierChars) || isCharInSet(getCurrentChar(), digitChars))
            {
                hPos++;
            }
            return inputLines[vPos].substr(start, hPos - start);
        }
        return "";
    }

    bool Scanner::isCharInSet(char ch, const std::string &charSet)
    {
        return charSet.find(ch) != std::string::npos;
    }

    char Scanner::getCurrentChar()
    {
        // Check if vPos is within the bounds of inputLines
        if (vPos < inputLines.size())
        {
            // get line corresponding to vPos
            const std::string &line = inputLines[vPos];

            // check if hPos is within the bounds of the line
            if (hPos < line.size())
            {
                // Return the character at position (vPos, hPos)
                // std::cout << line[hPos];
                return line[hPos];
            }
        }
        // Return '\0' if indices are out of bounds
        return '\0';
    }

    char Scanner::getCharFromShiftPosition(int shift)
    {
        // Check if vPos is within the bounds of inputLines
        if (vPos < inputLines.size())
        {
            // get line corresponding to vPos
            const std::string &line = inputLines[vPos];

            // check if hPos + shift is within the bounds of the line
            if (hPos + shift < line.size())
            {
                // Return the character at position (vPos, hPos + shift)
                return line[hPos + shift];
            }
        }
        // Return '\0' if indices are out of bounds
        return '\0';
    }
}