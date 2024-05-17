#ifndef PARSEMGR_H
#define PARSEMGR_H

#include <iostream>
#include "ast.h"
#include "parser.h"
#include "singleton.h"

namespace Parser
{
    class ParseMgr : public Singleton<ParseMgr>
    {
    public:
        void runParser(std::vector<Scanner::Token *> &tokens);
        AST &getAST() { return ast; }
        friend class Singleton<ParseMgr>;

    private:
        ParseMgr() = default;
        AST ast;
    };
}

#endif // !PARSEMGR_H
