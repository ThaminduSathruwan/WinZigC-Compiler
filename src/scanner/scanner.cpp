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
            const std::string &line = inputLines[vPos];
            std::cout << "Incoming String: " << line << std::endl; // Print each string from the array.

            while (hPos < line.size())
            {
                std::string stringToken = findIdentifierOrPredefineToken();

                if (!stringToken.empty())
                {
                    if (stringToken == "program")
                    {
                        tokens.push_back(new Token(TokenType::PROGRAM, stringToken, hPos - 6, vPos));
                    }
                    else if (stringToken == "var")
                    {
                        tokens.push_back(new Token(TokenType::VAR, stringToken, hPos - 2, vPos));
                    }
                    else if (stringToken == "const")
                    {
                        tokens.push_back(new Token(TokenType::CONST, stringToken, hPos - 4, vPos));
                    }
                    else if (stringToken == "type")
                    {
                        tokens.push_back(new Token(TokenType::TYPE, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "function")
                    {
                        tokens.push_back(new Token(TokenType::FUNCTION, stringToken, hPos - 7, vPos));
                    }
                    else if (stringToken == "return")
                    {
                        tokens.push_back(new Token(TokenType::RETURN, stringToken, hPos - 5, vPos));
                    }
                    else if (stringToken == "begin")
                    {
                        tokens.push_back(new Token(TokenType::BEGIN, stringToken, hPos - 4, vPos));
                    }
                    else if (stringToken == "end")
                    {
                        tokens.push_back(new Token(TokenType::END, stringToken, hPos - 2, vPos));
                    }
                    else if (stringToken == "output")
                    {
                        tokens.push_back(new Token(TokenType::OUTPUT, stringToken, hPos - 5, vPos));
                    }
                    else if (stringToken == "if")
                    {
                        tokens.push_back(new Token(TokenType::IF, stringToken, hPos - 1, vPos));
                    }
                    else if (stringToken == "then")
                    {
                        tokens.push_back(new Token(TokenType::THEN, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "else")
                    {
                        tokens.push_back(new Token(TokenType::ELSE, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "while")
                    {
                        tokens.push_back(new Token(TokenType::WHILE, stringToken, hPos - 4, vPos));
                    }
                    else if (stringToken == "do")
                    {
                        tokens.push_back(new Token(TokenType::DO, stringToken, hPos - 1, vPos));
                    }
                    else if (stringToken == "case")
                    {
                        tokens.push_back(new Token(TokenType::CASE, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "of")
                    {
                        tokens.push_back(new Token(TokenType::OF, stringToken, hPos - 1, vPos));
                    }
                    else if (stringToken == "otherwise")
                    {
                        tokens.push_back(new Token(TokenType::OTHERWISE, stringToken, hPos - 8, vPos));
                    }
                    else if (stringToken == "repeat")
                    {
                        tokens.push_back(new Token(TokenType::REPEAT, stringToken, hPos - 5, vPos));
                    }
                    else if (stringToken == "for")
                    {
                        tokens.push_back(new Token(TokenType::FOR, stringToken, hPos - 2, vPos));
                    }
                    else if (stringToken == "until")
                    {
                        tokens.push_back(new Token(TokenType::UNTIL, stringToken, hPos - 4, vPos));
                    }
                    else if (stringToken == "loop")
                    {
                        tokens.push_back(new Token(TokenType::LOOP, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "pool")
                    {
                        tokens.push_back(new Token(TokenType::POOL, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "exit")
                    {
                        tokens.push_back(new Token(TokenType::EXIT, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "mod")
                    {
                        tokens.push_back(new Token(TokenType::MOD, stringToken, hPos - 2, vPos));
                    }
                    else if (stringToken == "and")
                    {
                        tokens.push_back(new Token(TokenType::AND, stringToken, hPos - 2, vPos));
                    }
                    else if (stringToken == "or")
                    {
                        tokens.push_back(new Token(TokenType::OR, stringToken, hPos - 1, vPos));
                    }
                    else if (stringToken == "not")
                    {
                        tokens.push_back(new Token(TokenType::NOT, stringToken, hPos - 2, vPos));
                    }
                    else if (stringToken == "read")
                    {
                        tokens.push_back(new Token(TokenType::READ, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "succ")
                    {
                        tokens.push_back(new Token(TokenType::SUCC, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "pred")
                    {
                        tokens.push_back(new Token(TokenType::PRED, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "chr")
                    {
                        tokens.push_back(new Token(TokenType::CHAR, stringToken, hPos - 2, vPos));
                    }
                    else if (stringToken == "ord")
                    {
                        tokens.push_back(new Token(TokenType::ORD, stringToken, hPos - 2, vPos));
                    }
                    else if (stringToken == "eof")
                    {
                        tokens.push_back(new Token(TokenType::EOF_TOKEN, stringToken, hPos - 2, vPos));
                    }
                    else if (stringToken == "true")
                    {
                        tokens.push_back(new Token(TokenType::TRUE, stringToken, hPos - 3, vPos));
                    }
                    else if (stringToken == "false")
                    {
                        tokens.push_back(new Token(TokenType::FALSE, stringToken, hPos - 4, vPos));
                    }
                }

                std::string singleLineComment = findSingleLineComment();
            }
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
        }
    }

    std::string Scanner::findIdentifierOrPredefineToken()
    {
        int start = hPos;
        if (isCharInSet(getCurrentChar(), identifierChars))
        {
            std::cout << "The first one character";
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
                std::cout << line[hPos];
                return line[hPos];
            }
        }
        // Return '\0' if indices are out of bounds
        return '\0';
    }
}