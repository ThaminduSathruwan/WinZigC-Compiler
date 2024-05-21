#include <iostream>
#include "../../include/scanner.h"
#include "../../include/token.h"

namespace Scanner
{
    Token::Token(TokenType type, std::string data, unsigned int hPos, unsigned int vPos)
        : type(type), data(std::move(data)), hPos(hPos), vPos(vPos) {}

    // Get the type of the token
    TokenType Token::getType()
    {
        return type;
    }

    // Get the data associated with the token
    std::string Token::getData()
    {
        return data;
    }

    // Get the location of the token
    Location Token::getLocation()
    {
        return std::make_pair(hPos, vPos);
    }

    // Overload the << operator to print the token
    std::ostream &operator<<(std::ostream &os, const Token &token)
    {
        os << "\"" << token.data << "\" <"
           << token.hPos << ", " << token.vPos << "> {"
           << tokenTypeToString(token.type) << "}";
        return os;
    }

    // Convert the token type to a string
    std::string tokenTypeToString(TokenType type)
    {
        switch (type)
        {
        case TokenType::NEW_LINE:
            return "LF";
        case TokenType::PROGRAM:
            return "PROGRAM";
        case TokenType::VAR:
            return "VAR";
        case TokenType::CONST:
            return "CONST";
        case TokenType::TYPE:
            return "TYPE";
        case TokenType::FUNCTION:
            return "FUNCTION";
        case TokenType::RETURN:
            return "RETURN";
        case TokenType::BEGIN:
            return "BEGIN";
        case TokenType::END:
            return "END";
        case TokenType::SWAP:
            return "SWAP";
        case TokenType::ASSIGN:
            return "ASSIGN";
        case TokenType::OUTPUT:
            return "OUTPUT";
        case TokenType::IF:
            return "IF";
        case TokenType::THEN:
            return "THEN";
        case TokenType::ELSE:
            return "ELSE";
        case TokenType::WHILE:
            return "WHILE";
        case TokenType::DO:
            return "DO";
        case TokenType::CASE:
            return "CASE";
        case TokenType::OF:
            return "OF";
        case TokenType::CASE_DOTS:
            return "CASE_DOTS";
        case TokenType::OTHERWISE:
            return "OTHERWISE";
        case TokenType::REPEAT:
            return "REPEAT";
        case TokenType::UNTIL:
            return "UNTIL";
        case TokenType::FOR:
            return "FOR";
        case TokenType::LOOP:
            return "LOOP";
        case TokenType::POOL:
            return "POOL";
        case TokenType::EXIT:
            return "EXIT";
        case TokenType::LESS_THAN:
            return "LESS_THAN";
        case TokenType::LESS_THAN_EQUAL:
            return "LESS_THAN_EQUAL";
        case TokenType::GREATER_THAN:
            return "GREATER_THAN";
        case TokenType::GREATER_THAN_EQUAL:
            return "GREATER_THAN_EQUAL";
        case TokenType::EQUAL:
            return "EQUAL";
        case TokenType::NOT_EQUAL:
            return "NOT_EQUAL";
        case TokenType::MOD:
            return "MOD";
        case TokenType::AND:
            return "AND";
        case TokenType::OR:
            return "OR";
        case TokenType::NOT:
            return "NOT";
        case TokenType::READ:
            return "READ";
        case TokenType::SUCC:
            return "SUCC";
        case TokenType::PRED:
            return "PRED";
        case TokenType::CHR:
            return "CHR";
        case TokenType::ORD:
            return "ORD";
        case TokenType::EOF_TOKEN:
            return "EOF";
        case TokenType::COLON:
            return "COLON";
        case TokenType::SEMICOLON:
            return "SEMICOLON";
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::PERIOD:
            return "PERIOD";
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::PLUS:
            return "PLUS";
        case TokenType::MINUS:
            return "MINUS";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::DIVIDE:
            return "DIVIDE";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::INTEGER:
            return "INTEGER";
        case TokenType::WHITE_SPACE:
            return "WHITE_SPACE";
        case TokenType::CHAR:
            return "CHAR";
        case TokenType::STRING:
            return "STRING";
        case TokenType::SINGLE_LINE_COMMENT:
            return "SINGLE_LINE_COMMENT";
        case TokenType::MULTI_LINE_COMMENT:
            return "MULTI_LINE_COMMENT";
        case TokenType::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
    }
}
