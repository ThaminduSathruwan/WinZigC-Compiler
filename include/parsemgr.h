#ifndef PARSEMGR_H
#define PARSEMGR_H

#include <iostream>
#include "ast.h"
#include "parser.h"
#include "syntax_error.h"
#include "singleton.h"

namespace Parser
{
    class ParseMgr : public Singleton<ParseMgr>
    {
    public:
        bool runParser();
        void printAST(std::ostream &os);
        void build_tree(ASTNodeType type, int childrenCnt);
        void build_tree(std::string str, bool identifier = true);
        void build_tree(int32_t integer);
        void build_tree(char character);
        void finalizeAST();
        void addError(Scanner::Token *token, bool end = false);
        friend class Singleton<ParseMgr>;

    private:
        ParseMgr() = default;
        AST ast;
        std::vector<SyntaxError> errors;
        bool printErrors(std::ostream &os);
    };
}

#endif // !PARSEMGR_H
