#include <iostream>
#include <vector>
#include <string>
#include "../../include/scanner.h"
#include "../../include/scanmgr.h"
#include "token.h"

#define ADD_TOKEN(token) ScanMgr::Instance().addToken(token)

template <typename T>
T Singleton<T>::instance;
template class Singleton<Scanner::ScanMgr>;

namespace Scanner
{
    Scanner::Scanner(const std::vector<std::string> &inputLines) : inputLines(inputLines), vPos(0), hPos(0) {}

    void Scanner::tokenize()
    {
        while (vPos < inputLines.size())
        {

            while (hPos < inputLines[vPos].size())
            {

                const std::string &line = inputLines[vPos];

                std::string identifierToken = findIdentifierOrPredefineToken();

                if (!identifierToken.empty())
                {
                    if (identifierToken == "program")
                    {
                        ADD_TOKEN(new Token(TokenType::PROGRAM, identifierToken, hPos - 7, vPos));
                    }
                    else if (identifierToken == "var")
                    {
                        ADD_TOKEN(new Token(TokenType::VAR, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "const")
                    {
                        ADD_TOKEN(new Token(TokenType::CONST, identifierToken, hPos - 5, vPos));
                    }
                    else if (identifierToken == "type")
                    {
                        ADD_TOKEN(new Token(TokenType::TYPE, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "function")
                    {
                        ADD_TOKEN(new Token(TokenType::FUNCTION, identifierToken, hPos - 8, vPos));
                    }
                    else if (identifierToken == "return")
                    {
                        ADD_TOKEN(new Token(TokenType::RETURN, identifierToken, hPos - 6, vPos));
                    }
                    else if (identifierToken == "begin")
                    {
                        ADD_TOKEN(new Token(TokenType::BEGIN, identifierToken, hPos - 5, vPos));
                    }
                    else if (identifierToken == "end")
                    {
                        ADD_TOKEN(new Token(TokenType::END, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "output")
                    {
                        ADD_TOKEN(new Token(TokenType::OUTPUT, identifierToken, hPos - 6, vPos));
                    }
                    else if (identifierToken == "if")
                    {
                        ADD_TOKEN(new Token(TokenType::IF, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "then")
                    {
                        ADD_TOKEN(new Token(TokenType::THEN, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "else")
                    {
                        ADD_TOKEN(new Token(TokenType::ELSE, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "while")
                    {
                        ADD_TOKEN(new Token(TokenType::WHILE, identifierToken, hPos - 5, vPos));
                    }
                    else if (identifierToken == "do")
                    {
                        ADD_TOKEN(new Token(TokenType::DO, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "case")
                    {
                        ADD_TOKEN(new Token(TokenType::CASE, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "of")
                    {
                        ADD_TOKEN(new Token(TokenType::OF, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "otherwise")
                    {
                        ADD_TOKEN(new Token(TokenType::OTHERWISE, identifierToken, hPos - 9, vPos));
                    }
                    else if (identifierToken == "repeat")
                    {
                        ADD_TOKEN(new Token(TokenType::REPEAT, identifierToken, hPos - 6, vPos));
                    }
                    else if (identifierToken == "for")
                    {
                        ADD_TOKEN(new Token(TokenType::FOR, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "until")
                    {
                        ADD_TOKEN(new Token(TokenType::UNTIL, identifierToken, hPos - 5, vPos));
                    }
                    else if (identifierToken == "loop")
                    {
                        ADD_TOKEN(new Token(TokenType::LOOP, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "pool")
                    {
                        ADD_TOKEN(new Token(TokenType::POOL, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "exit")
                    {
                        ADD_TOKEN(new Token(TokenType::EXIT, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "mod")
                    {
                        ADD_TOKEN(new Token(TokenType::MOD, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "and")
                    {
                        ADD_TOKEN(new Token(TokenType::AND, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "or")
                    {
                        ADD_TOKEN(new Token(TokenType::OR, identifierToken, hPos - 2, vPos));
                    }
                    else if (identifierToken == "not")
                    {
                        ADD_TOKEN(new Token(TokenType::NOT, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "read")
                    {
                        ADD_TOKEN(new Token(TokenType::READ, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "succ")
                    {
                        ADD_TOKEN(new Token(TokenType::SUCC, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "pred")
                    {
                        ADD_TOKEN(new Token(TokenType::PRED, identifierToken, hPos - 4, vPos));
                    }
                    else if (identifierToken == "chr")
                    {
                        ADD_TOKEN(new Token(TokenType::CHAR, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "ord")
                    {
                        ADD_TOKEN(new Token(TokenType::ORD, identifierToken, hPos - 3, vPos));
                    }
                    else if (identifierToken == "eof")
                    {
                        ADD_TOKEN(new Token(TokenType::EOF_TOKEN, identifierToken, hPos - 3, vPos));
                    }
                    else
                    {
                        ADD_TOKEN(new Token(TokenType::IDENTIFIER, identifierToken, hPos - identifierToken.size(), vPos));
                    }
                }

                std::string integerToken = findInteger();

                if (!integerToken.empty())
                {
                    ADD_TOKEN(new Token(TokenType::INTEGER, integerToken, hPos - integerToken.size(), vPos));
                }

                std::string charToken = findChar();

                if (!charToken.empty())
                {
                    ADD_TOKEN(new Token(TokenType::CHAR, charToken, hPos - charToken.size(), vPos));
                }

                std::string stringToken = findString();

                if (!stringToken.empty())
                {
                    ADD_TOKEN(new Token(TokenType::STRING, stringToken, hPos - stringToken.size(), vPos));
                }

                // swap
                if (getCurrentChar() == ':' && getCharFromShiftPosition(1) == '=' && getCharFromShiftPosition(2) == ':')
                {
                    ADD_TOKEN(new Token(TokenType::SWAP, line.substr(hPos, 3), hPos, vPos));
                    hPos += 3;
                }

                // assignment operator
                if (getCurrentChar() == ':' && getCharFromShiftPosition(1) == '=')
                {
                    ADD_TOKEN(new Token(TokenType::ASSIGN, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // dots for case expression
                if (getCurrentChar() == '.' && getCharFromShiftPosition(1) == '.')
                {
                    ADD_TOKEN(new Token(TokenType::CASE_DOTS, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // less than or equal binary operator
                if (getCurrentChar() == '<' && getCharFromShiftPosition(1) == '=')
                {
                    ADD_TOKEN(new Token(TokenType::LESS_THAN_EQUAL, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // not equal binary operator
                if (getCurrentChar() == '<' && getCharFromShiftPosition(1) == '>')
                {
                    ADD_TOKEN(new Token(TokenType::NOT_EQUAL, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // less than binary operator
                if (getCurrentChar() == '<')
                {
                    ADD_TOKEN(new Token(TokenType::LESS_THAN, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // greater than or equal binary operator
                if (getCurrentChar() == '>' && getCharFromShiftPosition(1) == '=')
                {
                    ADD_TOKEN(new Token(TokenType::GREATER_THAN_EQUAL, line.substr(hPos, 2), hPos, vPos));
                    hPos += 2;
                }

                // greater than binary operator
                if (getCurrentChar() == '>')
                {
                    ADD_TOKEN(new Token(TokenType::GREATER_THAN, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // equal binary operator
                if (getCurrentChar() == '=')
                {
                    ADD_TOKEN(new Token(TokenType::EQUAL, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // colon
                if (getCurrentChar() == ':')
                {
                    ADD_TOKEN(new Token(TokenType::COLON, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // semi colon
                if (getCurrentChar() == ';')
                {
                    ADD_TOKEN(new Token(TokenType::SEMICOLON, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // single dot
                if (getCurrentChar() == '.')
                {
                    ADD_TOKEN(new Token(TokenType::PERIOD, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // comma
                if (getCurrentChar() == ',')
                {
                    ADD_TOKEN(new Token(TokenType::COMMA, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // opening bracket
                if (getCurrentChar() == '(')
                {
                    ADD_TOKEN(new Token(TokenType::LEFT_PAREN, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // closing bracket
                if (getCurrentChar() == ')')
                {
                    ADD_TOKEN(new Token(TokenType::RIGHT_PAREN, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // plus
                if (getCurrentChar() == '+')
                {
                    ADD_TOKEN(new Token(TokenType::PLUS, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // minus
                if (getCurrentChar() == '-')
                {
                    ADD_TOKEN(new Token(TokenType::MINUS, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // multiply
                if (getCurrentChar() == '*')
                {
                    ADD_TOKEN(new Token(TokenType::MULTIPLY, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                // divide
                if (getCurrentChar() == '/')
                {
                    ADD_TOKEN(new Token(TokenType::DIVIDE, line.substr(hPos, 1), hPos, vPos));
                    hPos += 1;
                }

                std::string singleLineComment = findSingleLineComment(line.size());

                std::string multiLineComment = findMultiLineComment();

                std::string newLine = findNewLine();

                std::string whiteSpace = findWhiteSpace();

                if (getCurrentChar() == '}')
                {
                    ScanMgr::Instance().addError(new Token(TokenType::RIGHT_CURLEY, "}", hPos, vPos));
                    hPos++;
                }
            }
            hPos = 0;
            vPos++;
        }
    }

    std::string Scanner::findSingleLineComment(unsigned int size)
    {
        int start = hPos;
        if (getCurrentChar() == '#')
        {
            while (hPos < size)
            {
                hPos++;
            }
            return inputLines[vPos].substr(start, hPos - start);
        }
        return "";
    }

    std::string Scanner::findMultiLineComment()
    {
        int start_h = hPos;
        int start_v = vPos;
        if (getCurrentChar() == '{')
        {
            while (vPos < inputLines.size() && getCurrentChar() != '}')
            {
                while (hPos < inputLines[vPos].length())
                {
                    if (getCurrentChar() == '}')
                    {
                        break;
                    }
                    else
                        hPos++;
                }
                if (getCurrentChar() != '}')
                {
                    vPos++;
                    hPos = 0;
                }
            }
            if (getCurrentChar() != '}')
            {
                ScanMgr::Instance().addError(new Token(TokenType::LEFT_CURLEY, "{", start_h, start_v));
            }
            vPos++;
            hPos = 0;
        }
        return "";
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
            return inputLines[vPos].substr(start + 1, hPos - start - 1);
        }
        return "";
    }

    std::string Scanner::findString()
    {
        int start = hPos;
        if (getCurrentChar() == '\"')
        {
            hPos++;
            while (hPos < inputLines[vPos].size() && getCurrentChar() != '\"')
            {
                if (getCurrentChar() == '\n')
                    break;
                hPos++;
            }
            if (hPos == inputLines[vPos].size())
            {
                ScanMgr::Instance().addError(new Token(TokenType::DOUBLE_QUOTE, "\"", start, vPos));
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