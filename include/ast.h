#ifndef AST_H
#define AST_H

#include <iostream>
#include <vector>
#include <stack>
#include "token.h"

namespace parser
{
    typedef enum ASTNodeType
    {
        INTERNAL,
        LEAF
    } ASTNodeType;

    typedef struct ast_node
    {
        ASTNodeType type;
        void *data;
        struct ast_node *first_child;
        struct ast_node *next_sibling;
        ~ast_node();
    } ASTNode;

    typedef std::pair<std::string, int> BuildNode;
    typedef std::vector<BuildNode> BuildNodeList;

    class AST
    {
    public:
        AST(BuildNodeList &nodes, std::vector<Scanner::Token *> &tokens);
        ~AST();
        void build_tree(BuildNode &node);
        friend std::ostream &operator<<(std::ostream &os, const AST &ast);

    private:
        ASTNode *root;
        std::stack<ASTNode *> node_stack;
        void preorder_traversal(ASTNode *node, int depth, std::ostream &os) const;
        void delete_tree(ASTNode *node);
    };
}

#endif // !AST_H
