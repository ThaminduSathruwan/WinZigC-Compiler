#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>

#include "token.h"

namespace Parser
{

    class Parser
    {
    public:
        Parser(std::vector<Scanner::Token *> &tokens);
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
        int parseCaseclauses();
        void parseCaseclause();
        void parseCaseExpression();
        bool parseOtherwiseClause();
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
    };

}

#endif // !PARSER_H
