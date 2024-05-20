#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>

#include "token.h"
#include "syntax_error.h"

namespace Parser
{

    class Parser
    {
    public:
        Parser(std::vector<Scanner::Token *> &tokens);
        ~Parser();
        void parse();

    private:
        Scanner::Token *readToken(Scanner::TokenType type);
        void parseWinzig();
        void parseConsts();
        void parseConst();
        void parseConstValue();
        void parseTypes();
        void parseType();
        void parseLitList();
        void parseSubProgs();
        void parseFcn();
        void parseParams();
        void parseDclns();
        void parseDcln();
        void parseBody();
        void parseStatement();
        void parseOutExp();
        void parseStringNode();
        void parseCaseclauses();
        void parseCaseclause();
        void parseCaseExpression();
        void parseOtherwiseClause();
        void parseAssignment();
        void parseForStat();
        void parseForExp();
        void parseExpression();
        void parseTerm();
        void parseFactor();
        void parsePrimary();
        void NewFunction();
        void parseName();
        void ExtractParenthesizedExpression();

    private:
        std::vector<Scanner::Token *> tokens;
        std::vector<Scanner::Token *>::iterator nextToken;
        std::vector<SyntaxError> errors;
    };

}

#endif // !PARSER_H
