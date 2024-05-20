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
        void runParser();
        void printAST(std::ostream &os);
        void build_tree(ASTNodeType type, int childrenCnt);
        void build_tree(std::string str, bool identifier = true);
        void build_tree(int32_t integer);
        void build_tree(char character);
        void finalizeAST();
        friend class Singleton<ParseMgr>;

    private:
        ParseMgr() = default;
        AST ast;
    };
}

#endif // !PARSEMGR_H
