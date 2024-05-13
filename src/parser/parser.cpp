#include <iostream>
#include <array>
#include <algorithm>
#include "../include/parser.h"
#include "parser.h"

#define TOKEN_IN(x) std::find(x.begin(), x.end(), (*nextToken)->getType()) != x.end()

namespace Parser
{

    std::array<Scanner::TokenType, 3> CaseclauseStart = {
        Scanner::TokenType::INTEGER,
        Scanner::TokenType::CHAR,
        Scanner::TokenType::IDENTIFIER};

    std::array<Scanner::TokenType, 12> ExpressionStart = {
        Scanner::TokenType::MINUS,
        Scanner::TokenType::PLUS,
        Scanner::TokenType::NOT,
        Scanner::TokenType::EOF_TOKEN,
        Scanner::TokenType::IDENTIFIER,
        Scanner::TokenType::INTEGER,
        Scanner::TokenType::CHAR,
        Scanner::TokenType::LEFT_PAREN,
        Scanner::TokenType::SUCC,
        Scanner::TokenType::PRED,
        Scanner::TokenType::CHR,
        Scanner::TokenType::ORD};

    std::array<Scanner::TokenType, 6> ComparisonOperators = {
        Scanner::TokenType::LESS_THAN_EQUAL,
        Scanner::TokenType::LESS_THAN,
        Scanner::TokenType::GREATER_THAN_EQUAL,
        Scanner::TokenType::GREATER_THAN,
        Scanner::TokenType::EQUAL,
        Scanner::TokenType::NOT_EQUAL};

    std::array<Scanner::TokenType, 3> AddOperators = {
        Scanner::TokenType::PLUS,
        Scanner::TokenType::MINUS,
        Scanner::TokenType::OR};

    std::array<Scanner::TokenType, 4> MulOperators = {
        Scanner::TokenType::MULTIPLY,
        Scanner::TokenType::DIVIDE,
        Scanner::TokenType::AND,
        Scanner::TokenType::MOD};

    Parser::Parser(std::vector<Scanner::Token *> &tokens) : tokens(tokens), nextToken(tokens.begin())
    {
    }

    Parser::~Parser()
    {
        for (auto &token : tokens)
        {
            delete token;
        }
    }

    void Parser::parse()
    {
        nextToken = tokens.begin();
        parseWinzig();
    }

    Scanner::Token *Parser::readToken(Scanner::TokenType type)
    {
        if (nextToken == tokens.end())
        {
            errors.push_back(SyntaxError(*nextToken, "Unexpected end of file"));
            return nullptr;
        }
        if ((*nextToken)->getType() != type)
        {
            errors.push_back(SyntaxError(*nextToken, "Unexpected token"));
            return nullptr;
        }
        return *nextToken++;
    }

    void Parser::parseWinzig()
    {
        readToken(Scanner::TokenType::PROGRAM);
        parseName();
        readToken(Scanner::TokenType::COLON);
        parseConsts();
        parseTypes();
        parseDclns();
        parseSubProgs();
        parseBody();
        parseName();
        readToken(Scanner::TokenType::PERIOD);
    }

    void Parser::parseConsts()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::CONST)
        {
            readToken(Scanner::TokenType::CONST);
            parseConst();
            while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
            {
                readToken(Scanner::TokenType::COMMA);
                parseConst();
            }
            readToken(Scanner::TokenType::SEMICOLON);
        }
    }

    void Parser::parseConst()
    {
        parseName();
        readToken(Scanner::TokenType::EQUAL);
        parseConstValue();
    }

    void Parser::parseConstValue()
    {
        switch ((*nextToken)->getType())
        {
        case Scanner::TokenType::INTEGER:
            readToken(Scanner::TokenType::INTEGER);
            break;
        case Scanner::TokenType::CHAR:
            readToken(Scanner::TokenType::CHAR);
            break;
        case Scanner::TokenType::IDENTIFIER:
            parseName();
            break;
        default:
            errors.push_back(SyntaxError(*nextToken, "Unexpected token in constant declaration"));
            break;
        }
    }

    void Parser::parseTypes()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::TYPE)
        {
            readToken(Scanner::TokenType::TYPE);
            parseType();
            while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
            {
                readToken(Scanner::TokenType::SEMICOLON);
                parseType();
            }
            readToken(Scanner::TokenType::SEMICOLON);
        }
    }

    void Parser::parseType()
    {
        parseName();
        readToken(Scanner::TokenType::EQUAL);
        parseLitList();
    }

    void Parser::parseLitList()
    {
        readToken(Scanner::TokenType::LEFT_PAREN);
        parseName();
        while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
        {
            readToken(Scanner::TokenType::COMMA);
            parseName();
        }
        readToken(Scanner::TokenType::RIGHT_PAREN);
    }

    void Parser::parseSubProgs()
    {
        while ((*nextToken)->getType() == Scanner::TokenType::FUNCTION)
        {
            parseFcn();
        }
    }

    void Parser::parseFcn()
    {
        readToken(Scanner::TokenType::FUNCTION);
        parseName();
        readToken(Scanner::TokenType::LEFT_PAREN);
        parseParams();
        readToken(Scanner::TokenType::RIGHT_PAREN);
        readToken(Scanner::TokenType::COLON);
        parseName();
        readToken(Scanner::TokenType::SEMICOLON);
        parseConsts();
        parseTypes();
        parseDclns();
        parseBody();
        readToken(Scanner::TokenType::SEMICOLON);
    }

    void Parser::parseParams()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::IDENTIFIER)
        {
            parseDcln();
            while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
            {
                readToken(Scanner::TokenType::SEMICOLON);
                parseDcln();
            }
        }
    }

    void Parser::parseDclns()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::VAR)
        {
            readToken(Scanner::TokenType::VAR);
            parseDcln();
            while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
            {
                readToken(Scanner::TokenType::SEMICOLON);
                parseDcln();
            }
            readToken(Scanner::TokenType::SEMICOLON);
        }
    }

    void Parser::parseDcln()
    {
        parseName();
        while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
        {
            readToken(Scanner::TokenType::COMMA);
            parseName();
        }
        readToken(Scanner::TokenType::COLON);
        parseName();
    }

    void Parser::parseBody()
    {
        readToken(Scanner::TokenType::BEGIN);
        parseStatement();
        while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
        {
            readToken(Scanner::TokenType::SEMICOLON);
            parseStatement();
        }
        readToken(Scanner::TokenType::END);
    }

    void Parser::parseStatement()
    {
        switch ((*nextToken)->getType())
        {
        case Scanner::TokenType::IDENTIFIER:
            parseAssignment();
            break;
        case Scanner::TokenType::OUTPUT:
            readToken(Scanner::TokenType::OUTPUT);
            readToken(Scanner::TokenType::LEFT_PAREN);
            parseOutExp();
            while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
            {
                readToken(Scanner::TokenType::COMMA);
                parseOutExp();
            }
            readToken(Scanner::TokenType::RIGHT_PAREN);
            break;
        case Scanner::TokenType::IF:
            readToken(Scanner::TokenType::IF);
            parseExpression();
            readToken(Scanner::TokenType::THEN);
            parseStatement();
            if ((*nextToken)->getType() == Scanner::TokenType::ELSE)
            {
                readToken(Scanner::TokenType::ELSE);
                parseStatement();
            }
            break;
        case Scanner::TokenType::WHILE:
            readToken(Scanner::TokenType::WHILE);
            parseExpression();
            readToken(Scanner::TokenType::DO);
            parseStatement();
            break;
        case Scanner::TokenType::REPEAT:
            readToken(Scanner::TokenType::REPEAT);
            parseStatement();
            while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
            {
                readToken(Scanner::TokenType::SEMICOLON);
                parseStatement();
            }
            readToken(Scanner::TokenType::UNTIL);
            break;
        case Scanner::TokenType::FOR:
            readToken(Scanner::TokenType::FOR);
            readToken(Scanner::TokenType::LEFT_PAREN);
            parseForStat();
            readToken(Scanner::TokenType::SEMICOLON);
            parseForExp();
            readToken(Scanner::TokenType::SEMICOLON);
            parseForStat();
            readToken(Scanner::TokenType::RIGHT_PAREN);
            parseStatement();
            break;
        case Scanner::TokenType::LOOP:
            readToken(Scanner::TokenType::LOOP);
            parseStatement();
            while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
            {
                readToken(Scanner::TokenType::SEMICOLON);
                parseStatement();
            }
            readToken(Scanner::TokenType::POOL);
            break;
        case Scanner::TokenType::CASE:
            readToken(Scanner::TokenType::CASE);
            parseExpression();
            readToken(Scanner::TokenType::OF);
            parseCaseclauses();
            parseOtherwiseClause();
            readToken(Scanner::TokenType::END);
            break;
        case Scanner::TokenType::READ:
            readToken(Scanner::TokenType::READ);
            readToken(Scanner::TokenType::LEFT_PAREN);
            parseName();
            while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
            {
                readToken(Scanner::TokenType::COMMA);
                parseName();
            }
            readToken(Scanner::TokenType::RIGHT_PAREN);
            break;
        case Scanner::TokenType::EXIT:
            readToken(Scanner::TokenType::EXIT);
            break;
        case Scanner::TokenType::BEGIN:
            parseBody();
            break;
        default:
            break;
        }
    }

    void Parser::parseOutExp()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::STRING)
        {
            parseStringNode();
        }
        else
        {
            parseExpression();
        }
    }

    void Parser::parseStringNode()
    {
        readToken(Scanner::TokenType::STRING);
    }

    void Parser::parseCaseclauses()
    {
        parseCaseclause();
        readToken(Scanner::TokenType::SEMICOLON);
        while (TOKEN_IN(CaseclauseStart))
        {
            parseCaseclause();
            readToken(Scanner::TokenType::SEMICOLON);
        }
    }

    void Parser::parseCaseclause()
    {
        parseCaseExpression();
        while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
        {
            readToken(Scanner::TokenType::COMMA);
            parseCaseExpression();
        }
        readToken(Scanner::TokenType::COLON);
        parseStatement();
    }

    void Parser::parseCaseExpression()
    {
        parseConstValue();
        while ((*nextToken)->getType() == Scanner::TokenType::CASE_DOTS)
        {
            readToken(Scanner::TokenType::CASE_DOTS);
            parseConstValue();
        }
    }

    void Parser::parseOtherwiseClause()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::OTHERWISE)
        {
            readToken(Scanner::TokenType::OTHERWISE);
            parseStatement();
        }
    }

    void Parser::parseAssignment()
    {
        parseName();
        switch ((*nextToken)->getType())
        {
        case Scanner::TokenType::ASSIGN:
            readToken(Scanner::TokenType::ASSIGN);
            parseExpression();
            break;
        case Scanner::TokenType::SWAP:
            readToken(Scanner::TokenType::SWAP);
            parseName();
            break;
        default:
            errors.push_back(SyntaxError(*nextToken, "Unexpected token"));
            break;
        }
    }

    void Parser::parseForStat()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::IDENTIFIER)
        {
            parseAssignment();
        }
    }

    void Parser::parseForExp()
    {
        if (TOKEN_IN(ExpressionStart))
        {
            parseExpression();
        }
    }

    void Parser::parseExpression()
    {
        parseTerm();
        if (TOKEN_IN(ComparisonOperators))
        {
            readToken((*nextToken)->getType());
            parseTerm();
        }
    }

    void Parser::parseTerm()
    {
        parseFactor();
        while (TOKEN_IN(AddOperators))
        {
            readToken((*nextToken)->getType());
            parseFactor();
        }
    }

    void Parser::parseFactor()
    {
        parsePrimary();
        while (TOKEN_IN(MulOperators))
        {
            readToken((*nextToken)->getType());
            parsePrimary();
        }
    }

    void Parser::parsePrimary()
    {
        switch ((*nextToken)->getType())
        {
        case Scanner::TokenType::MINUS:
            readToken(Scanner::TokenType::MINUS);
            parsePrimary();
            break;
        case Scanner::TokenType::PLUS:
            readToken(Scanner::TokenType::PLUS);
            parsePrimary();
            break;
        case Scanner::TokenType::NOT:
            readToken(Scanner::TokenType::NOT);
            parsePrimary();
            break;
        case Scanner::TokenType::EOF_TOKEN:
            readToken(Scanner::TokenType::EOF_TOKEN);
            break;
        case Scanner::TokenType::IDENTIFIER:
            parseName();
            if ((*nextToken)->getType() == Scanner::TokenType::LEFT_PAREN)
            {
                readToken(Scanner::TokenType::LEFT_PAREN);
                parseExpression();
                while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
                {
                    readToken(Scanner::TokenType::COMMA);
                    parseExpression();
                }
                readToken(Scanner::TokenType::RIGHT_PAREN);
            }
            break;
        case Scanner::TokenType::INTEGER:
            readToken(Scanner::TokenType::INTEGER);
            break;
        case Scanner::TokenType::CHAR:
            readToken(Scanner::TokenType::CHAR);
            break;
        case Scanner::TokenType::LEFT_PAREN:
            ExtractParenthesizedExpression();
            break;
        case Scanner::TokenType::SUCC:
            readToken(Scanner::TokenType::SUCC);
            ExtractParenthesizedExpression();
            break;
        case Scanner::TokenType::PRED:
            readToken(Scanner::TokenType::PRED);
            ExtractParenthesizedExpression();
            break;
        case Scanner::TokenType::CHR:
            readToken(Scanner::TokenType::CHR);
            ExtractParenthesizedExpression();
            break;
        case Scanner::TokenType::ORD:
            readToken(Scanner::TokenType::ORD);
            ExtractParenthesizedExpression();
            break;
        default:
            errors.push_back(SyntaxError(*nextToken, "Unexpected token"));
            break;
        }
    }

    void Parser::parseName()
    {
        readToken(Scanner::TokenType::IDENTIFIER);
    }

    void Parser::ExtractParenthesizedExpression()
    {
        readToken(Scanner::TokenType::LEFT_PAREN);
        parseExpression();
        readToken(Scanner::TokenType::RIGHT_PAREN);
    }

}
