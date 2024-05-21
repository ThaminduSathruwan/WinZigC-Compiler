#include "../../include/parsemgr.h"
#include "../../include/parser.h"
#include "../../include/ast.h"
#include "../../include/syntax_error.h"
#include "../../include/token.h"
#include "../../include/scanmgr.h"
#include "parser_utils.h"

template <typename T>
T Singleton<T>::instance;
template class Singleton<Parser::ParseMgr>;

namespace Parser
{

    Parser::Parser(std::vector<Scanner::Token *> &tokens) : tokens(tokens), nextToken(tokens.begin())
    {
    }

    void Parser::parse()
    {
        nextToken = tokens.begin();
        parseWinzig();
        assertEnd();
        ParseMgr::Instance().finalizeAST();
    }

    Scanner::Token *Parser::readToken(Scanner::TokenType type)
    {
        if (nextToken == tokens.end())
        {
            ParseMgr::Instance().addError(*(nextToken - 1), true);
            return nullptr;
        }
        if ((*nextToken)->getType() != type)
        {
            SYNTAX_ERROR();
            return nullptr;
        }
        return *(nextToken++);
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
        BUILD_TREE(ASTNodeType::PROGRAM, 7);
    }

    void Parser::parseConsts()
    {

        int i = 0;
        if ((*nextToken)->getType() == Scanner::TokenType::CONST)
        {
            readToken(Scanner::TokenType::CONST);
            parseConst();
            ++i;
            while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
            {
                readToken(Scanner::TokenType::COMMA);
                parseConst();
                ++i;
            }
            readToken(Scanner::TokenType::SEMICOLON);
        }
        BUILD_TREE(ASTNodeType::CONSTS, i);
    }

    void Parser::parseConst()
    {
        parseName();
        readToken(Scanner::TokenType::EQUAL);
        parseConstValue();
        BUILD_TREE(ASTNodeType::CONST, 2);
    }

    void Parser::parseConstValue()
    {
        Scanner::Token *t;
        switch ((*nextToken)->getType())
        {
        case Scanner::TokenType::INTEGER:
            t = readToken(Scanner::TokenType::INTEGER);
            if (t != nullptr)
            {
                ParseMgr::Instance().build_tree(std::stoi(t->getData()));
                BUILD_TREE(ASTNodeType::INT, 1);
            }
            break;
        case Scanner::TokenType::CHAR:
            t = readToken(Scanner::TokenType::CHAR);
            if (t != nullptr)
            {
                ParseMgr::Instance().build_tree(t->getData()[0]);
                BUILD_TREE(ASTNodeType::CHAR, 1);
            }
            break;
        case Scanner::TokenType::IDENTIFIER:
            parseName();
            break;
        default:
            SYNTAX_ERROR();
            break;
        }
    }

    void Parser::parseTypes()
    {
        int i = 0;
        if ((*nextToken)->getType() == Scanner::TokenType::TYPE)
        {
            readToken(Scanner::TokenType::TYPE);
            parseType();
            readToken(Scanner::TokenType::SEMICOLON);
            ++i;
            while ((*nextToken)->getType() == Scanner::TokenType::IDENTIFIER)
            {
                parseType();
                readToken(Scanner::TokenType::SEMICOLON);
                ++i;
            }
        }
        BUILD_TREE(ASTNodeType::TYPES, i);
    }

    void Parser::parseType()
    {
        parseName();
        readToken(Scanner::TokenType::EQUAL);
        parseLitList();
        BUILD_TREE(ASTNodeType::TYPE, 2);
    }

    void Parser::parseLitList()
    {
        readToken(Scanner::TokenType::LEFT_PAREN);
        parseName();
        int i = 1;
        while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
        {
            readToken(Scanner::TokenType::COMMA);
            parseName();
            ++i;
        }
        readToken(Scanner::TokenType::RIGHT_PAREN);
        BUILD_TREE(ASTNodeType::LIT, i);
    }

    void Parser::parseSubProgs()
    {
        int i = 0;
        while ((*nextToken)->getType() == Scanner::TokenType::FUNCTION)
        {
            parseFcn();
            ++i;
        }
        BUILD_TREE(ASTNodeType::SUBPROGS, i);
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
        parseName();
        readToken(Scanner::TokenType::SEMICOLON);
        BUILD_TREE(ASTNodeType::FCN, 8);
    }

    void Parser::parseParams()
    {
        parseDcln();
        int i = 1;
        while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
        {
            readToken(Scanner::TokenType::SEMICOLON);
            parseDcln();
            ++i;
        }
        BUILD_TREE(ASTNodeType::PARAMS, i);
    }

    void Parser::parseDclns()
    {
        int i = 0;
        if ((*nextToken)->getType() == Scanner::TokenType::VAR)
        {
            readToken(Scanner::TokenType::VAR);
            parseDcln();
            readToken(Scanner::TokenType::SEMICOLON);
            ++i;
            while ((*nextToken)->getType() == Scanner::TokenType::IDENTIFIER)
            {
                parseDcln();
                readToken(Scanner::TokenType::SEMICOLON);
                ++i;
            }
        }
        BUILD_TREE(ASTNodeType::DCLNS, i);
    }

    void Parser::parseDcln()
    {
        parseName();
        int i = 1;
        while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
        {
            readToken(Scanner::TokenType::COMMA);
            parseName();
            ++i;
        }
        readToken(Scanner::TokenType::COLON);
        parseName();
        ++i;
        BUILD_TREE(ASTNodeType::VAR, i);
    }

    void Parser::parseBody()
    {
        readToken(Scanner::TokenType::BEGIN);
        parseStatement();
        int i = 1;
        while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
        {
            readToken(Scanner::TokenType::SEMICOLON);
            parseStatement();
            ++i;
        }
        readToken(Scanner::TokenType::END);
        BUILD_TREE(ASTNodeType::BLOCK, i);
    }

    void Parser::parseStatement()
    {
        int i;
        switch ((*nextToken)->getType())
        {
        case Scanner::TokenType::IDENTIFIER:
            parseAssignment();
            break;
        case Scanner::TokenType::OUTPUT:
            readToken(Scanner::TokenType::OUTPUT);
            readToken(Scanner::TokenType::LEFT_PAREN);
            parseOutExp();
            i = 1;
            while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
            {
                readToken(Scanner::TokenType::COMMA);
                parseOutExp();
                ++i;
            }
            readToken(Scanner::TokenType::RIGHT_PAREN);
            BUILD_TREE(ASTNodeType::OUTPUT, i);
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
                BUILD_TREE(ASTNodeType::IF, 3);
            }
            else
            {
                BUILD_TREE(ASTNodeType::IF, 2);
            }
            break;
        case Scanner::TokenType::WHILE:
            readToken(Scanner::TokenType::WHILE);
            parseExpression();
            readToken(Scanner::TokenType::DO);
            parseStatement();
            BUILD_TREE(ASTNodeType::WHILE, 2);
            break;
        case Scanner::TokenType::REPEAT:
            readToken(Scanner::TokenType::REPEAT);
            parseStatement();
            i = 1;
            while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
            {
                readToken(Scanner::TokenType::SEMICOLON);
                parseStatement();
                ++i;
            }
            readToken(Scanner::TokenType::UNTIL);
            parseExpression();
            ++i;
            BUILD_TREE(ASTNodeType::REPEAT, i);
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
            BUILD_TREE(ASTNodeType::FOR, 4);
            break;
        case Scanner::TokenType::LOOP:
            readToken(Scanner::TokenType::LOOP);
            parseStatement();
            i = 1;
            while ((*nextToken)->getType() == Scanner::TokenType::SEMICOLON)
            {
                readToken(Scanner::TokenType::SEMICOLON);
                parseStatement();
                ++i;
            }
            readToken(Scanner::TokenType::POOL);
            BUILD_TREE(ASTNodeType::LOOP, i);
            break;
        case Scanner::TokenType::CASE:
            readToken(Scanner::TokenType::CASE);
            parseExpression();
            readToken(Scanner::TokenType::OF);
            i = parseCaseclauses() + 1;
            if (parseOtherwiseClause())
                ++i;
            readToken(Scanner::TokenType::END);
            BUILD_TREE(ASTNodeType::CASE, i);
            break;
        case Scanner::TokenType::READ:
            readToken(Scanner::TokenType::READ);
            readToken(Scanner::TokenType::LEFT_PAREN);
            parseName();
            i = 1;
            while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
            {
                readToken(Scanner::TokenType::COMMA);
                parseName();
                ++i;
            }
            readToken(Scanner::TokenType::RIGHT_PAREN);
            BUILD_TREE(ASTNodeType::READ, i);
            break;
        case Scanner::TokenType::EXIT:
            readToken(Scanner::TokenType::EXIT);
            BUILD_TREE(ASTNodeType::EXIT, 0);
            break;
        case Scanner::TokenType::RETURN:
            readToken(Scanner::TokenType::RETURN);
            parseExpression();
            BUILD_TREE(ASTNodeType::RETURN, 1);
            break;
        case Scanner::TokenType::BEGIN:
            parseBody();
            break;
        default:
            BUILD_TREE(ASTNodeType::NULL_, 0);
            break;
        }
    }

    void Parser::parseOutExp()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::STRING)
        {
            parseStringNode();
            BUILD_TREE(ASTNodeType::STRING, 1);
        }
        else
        {
            parseExpression();
            BUILD_TREE(ASTNodeType::INTEGER, 1);
        }
    }

    void Parser::parseStringNode()
    {
        Scanner::Token *t = readToken(Scanner::TokenType::STRING);
        if (t != nullptr)
        {
            ParseMgr::Instance().build_tree(t->getData(), false);
        }
    }

    int Parser::parseCaseclauses()
    {
        parseCaseclause();
        int i = 1;
        readToken(Scanner::TokenType::SEMICOLON);
        while (TOKEN_IN(CaseclauseSelectSet))
        {
            parseCaseclause();
            ++i;
            readToken(Scanner::TokenType::SEMICOLON);
        }
        return i;
    }

    void Parser::parseCaseclause()
    {
        parseCaseExpression();
        int i = 1;
        while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
        {
            readToken(Scanner::TokenType::COMMA);
            parseCaseExpression();
            ++i;
        }
        readToken(Scanner::TokenType::COLON);
        parseStatement();
        ++i;
        BUILD_TREE(ASTNodeType::CASE_CLAUSE, i);
    }

    void Parser::parseCaseExpression()
    {
        parseConstValue();
        if ((*nextToken)->getType() == Scanner::TokenType::CASE_DOTS)
        {
            readToken(Scanner::TokenType::CASE_DOTS);
            parseConstValue();
            BUILD_TREE(ASTNodeType::CASE_DOTS, 2);
        }
    }

    bool Parser::parseOtherwiseClause()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::OTHERWISE)
        {
            readToken(Scanner::TokenType::OTHERWISE);
            parseStatement();
            BUILD_TREE(ASTNodeType::OTHERWISE, 1);
            return true;
        }
        return false;
    }

    void Parser::parseAssignment()
    {
        parseName();
        switch ((*nextToken)->getType())
        {
        case Scanner::TokenType::ASSIGN:
            readToken(Scanner::TokenType::ASSIGN);
            parseExpression();
            BUILD_TREE(ASTNodeType::ASSIGN, 2);
            break;
        case Scanner::TokenType::SWAP:
            readToken(Scanner::TokenType::SWAP);
            parseName();
            BUILD_TREE(ASTNodeType::SWAP, 2);
            break;
        default:
            SYNTAX_ERROR();
            break;
        }
    }

    void Parser::parseForStat()
    {
        if ((*nextToken)->getType() == Scanner::TokenType::IDENTIFIER)
        {
            parseAssignment();
        }
        else
        {
            BUILD_TREE(ASTNodeType::NULL_, 0);
        }
    }

    void Parser::parseForExp()
    {
        if (TOKEN_IN(ExpressionSelectSet))
        {
            parseExpression();
        }
        else
        {
            BUILD_TREE(ASTNodeType::TRUE, 0);
        }
    }

    void Parser::parseExpression()
    {
        parseTerm();
        if (TOKEN_IN(ComparisonOperators))
        {
            switch ((*nextToken)->getType())
            {
            case Scanner::TokenType::LESS_THAN_EQUAL:
                readToken(Scanner::TokenType::LESS_THAN_EQUAL);
                parseTerm();
                BUILD_TREE(ASTNodeType::LEQ, 2);
                break;
            case Scanner::TokenType::LESS_THAN:
                readToken(Scanner::TokenType::LESS_THAN);
                parseTerm();
                BUILD_TREE(ASTNodeType::LT, 2);
                break;
            case Scanner::TokenType::GREATER_THAN_EQUAL:
                readToken(Scanner::TokenType::GREATER_THAN_EQUAL);
                parseTerm();
                BUILD_TREE(ASTNodeType::GEQ, 2);
                break;
            case Scanner::TokenType::GREATER_THAN:
                readToken(Scanner::TokenType::GREATER_THAN);
                parseTerm();
                BUILD_TREE(ASTNodeType::GT, 2);
                break;
            case Scanner::TokenType::EQUAL:
                readToken(Scanner::TokenType::EQUAL);
                parseTerm();
                BUILD_TREE(ASTNodeType::EQ, 2);
                break;
            case Scanner::TokenType::NOT_EQUAL:
                readToken(Scanner::TokenType::NOT_EQUAL);
                parseTerm();
                BUILD_TREE(ASTNodeType::NEQ, 2);
                break;
            default:
                break;
            }
        }
    }

    void Parser::parseTerm()
    {
        parseFactor();
        while (TOKEN_IN(AddOperators))
        {
            switch ((*nextToken)->getType())
            {
            case Scanner::TokenType::PLUS:
                readToken(Scanner::TokenType::PLUS);
                parseFactor();
                BUILD_TREE(ASTNodeType::PLUS, 2);
                break;
            case Scanner::TokenType::MINUS:
                readToken(Scanner::TokenType::MINUS);
                parseFactor();
                BUILD_TREE(ASTNodeType::NEG, 2);
                break;
            case Scanner::TokenType::OR:
                readToken(Scanner::TokenType::OR);
                parseFactor();
                BUILD_TREE(ASTNodeType::OR, 2);
                break;
            default:
                break;
            }
        }
    }

    void Parser::parseFactor()
    {
        parsePrimary();
        while (TOKEN_IN(MulOperators))
        {
            switch ((*nextToken)->getType())
            {
            case Scanner::TokenType::MULTIPLY:
                readToken(Scanner::TokenType::MULTIPLY);
                parsePrimary();
                BUILD_TREE(ASTNodeType::MUL, 2);
                break;
            case Scanner::TokenType::DIVIDE:
                readToken(Scanner::TokenType::DIVIDE);
                parsePrimary();
                BUILD_TREE(ASTNodeType::DIV, 2);
                break;
            case Scanner::TokenType::AND:
                readToken(Scanner::TokenType::AND);
                parsePrimary();
                BUILD_TREE(ASTNodeType::AND, 2);
                break;
            case Scanner::TokenType::MOD:
                readToken(Scanner::TokenType::MOD);
                parsePrimary();
                BUILD_TREE(ASTNodeType::MOD, 2);
                break;
            default:
                break;
            }
        }
    }

    void Parser::parsePrimary()
    {
        Scanner::Token *t;
        switch ((*nextToken)->getType())
        {
        case Scanner::TokenType::MINUS:
            readToken(Scanner::TokenType::MINUS);
            parsePrimary();
            BUILD_TREE(ASTNodeType::NEG, 1);
            break;
        case Scanner::TokenType::PLUS:
            readToken(Scanner::TokenType::PLUS);
            parsePrimary();
            break;
        case Scanner::TokenType::NOT:
            readToken(Scanner::TokenType::NOT);
            parsePrimary();
            BUILD_TREE(ASTNodeType::NOT, 1);
            break;
        case Scanner::TokenType::EOF_TOKEN:
            readToken(Scanner::TokenType::EOF_TOKEN);
            BUILD_TREE(ASTNodeType::EOF_, 0);
            break;
        case Scanner::TokenType::IDENTIFIER:
            parseName();
            if ((*nextToken)->getType() == Scanner::TokenType::LEFT_PAREN)
            {
                readToken(Scanner::TokenType::LEFT_PAREN);
                parseExpression();
                int i = 2;
                while ((*nextToken)->getType() == Scanner::TokenType::COMMA)
                {
                    readToken(Scanner::TokenType::COMMA);
                    parseExpression();
                    ++i;
                }
                readToken(Scanner::TokenType::RIGHT_PAREN);
                BUILD_TREE(ASTNodeType::CALL, i);
            }
            break;
        case Scanner::TokenType::INTEGER:
            t = readToken(Scanner::TokenType::INTEGER);
            if (t != nullptr)
            {
                ParseMgr::Instance().build_tree(std::stoi(t->getData()));
                BUILD_TREE(ASTNodeType::INT, 1);
            }
            break;
        case Scanner::TokenType::CHAR:
            t = readToken(Scanner::TokenType::CHAR);
            if (t != nullptr)
            {
                ParseMgr::Instance().build_tree(t->getData()[0]);
                BUILD_TREE(ASTNodeType::CHAR, 1);
            }
            break;
        case Scanner::TokenType::LEFT_PAREN:
            ExtractParenthesizedExpression();
            break;
        case Scanner::TokenType::SUCC:
            readToken(Scanner::TokenType::SUCC);
            ExtractParenthesizedExpression();
            BUILD_TREE(ASTNodeType::SUCC, 1);
            break;
        case Scanner::TokenType::PRED:
            readToken(Scanner::TokenType::PRED);
            ExtractParenthesizedExpression();
            BUILD_TREE(ASTNodeType::PRED, 1);
            break;
        case Scanner::TokenType::CHR:
            readToken(Scanner::TokenType::CHR);
            ExtractParenthesizedExpression();
            BUILD_TREE(ASTNodeType::CHR, 1);
            break;
        case Scanner::TokenType::ORD:
            readToken(Scanner::TokenType::ORD);
            ExtractParenthesizedExpression();
            BUILD_TREE(ASTNodeType::ORD, 1);
            break;
        default:
            SYNTAX_ERROR();
            break;
        }
    }

    void Parser::parseName()
    {
        Scanner::Token *t = readToken(Scanner::TokenType::IDENTIFIER);
        if (t != nullptr)
        {
            ParseMgr::Instance().build_tree(t->getData());
            BUILD_TREE(ASTNodeType::ID, 1);
        }
    }

    void Parser::ExtractParenthesizedExpression()
    {
        readToken(Scanner::TokenType::LEFT_PAREN);
        parseExpression();
        readToken(Scanner::TokenType::RIGHT_PAREN);
    }

    void Parser::assertEnd()
    {
        while (nextToken != tokens.end())
        {
            SYNTAX_ERROR();
            ++nextToken;
        }
    }

}
