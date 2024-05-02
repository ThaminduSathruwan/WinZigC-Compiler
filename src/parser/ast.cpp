#include <iostream>
#include <vector>
#include <stack>
#include "../../include/token.h"
#include "../../include/ast.h"

namespace parser
{
    ASTNode::~ast_node()
    {
        if (type == LEAF)
        {
            delete static_cast<Scanner::Token *>(data);
        }
        else
        {
            delete static_cast<std::string *>(data);
        }
    }

    AST::AST(BuildNodeList &nodes, std::vector<Scanner::Token *> &tokens)
    {
        for (auto &token : tokens)
        {
            ASTNode *node = new ASTNode;
            node->type = LEAF;
            node->data = token;
            node->first_child = nullptr;
            node->next_sibling = nullptr;
            node_stack.push(node);
        }

        root = nullptr;
        for (auto &node : nodes)
        {
            build_tree(node);
        }
    }

    AST::~AST()
    {
        delete_tree(root);
    }

    void AST::build_tree(BuildNode &buildNode)
    {
        ASTNode *p = nullptr;
        for (int i = 0; i < buildNode.second; ++i)
        {
            ASTNode *c = node_stack.top();
            node_stack.pop();
            c->next_sibling = p;
            p = c;
        }
        ASTNode *node = new ASTNode;
        node->type = INTERNAL;
        node->data = new std::string(buildNode.first);
    }

    std::ostream &operator<<(std::ostream &os, const AST &ast)
    {
        ast.preorder_traversal(ast.root, 0, os);
        return os;
    }

    void AST::preorder_traversal(ASTNode *node, int depth, std::ostream &os) const
    {
        if (node == nullptr)
        {
            os << "null" << std::endl;
            return;
        }

        for (int i = 0; i < depth; ++i)
        {
            os << ".";
        }

        if (node->type == LEAF)
        {
            Scanner::Token *token = static_cast<Scanner::Token *>(node->data);
            os << token->getData() << std::endl;
        }
        else
        {
            std::string *str = static_cast<std::string *>(node->data);
            os << *str << std::endl;
        }

        preorder_traversal(node->first_child, depth + 1, os);
        preorder_traversal(node->next_sibling, depth, os);
    }

    void AST::delete_tree(ASTNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        delete_tree(node->first_child);
        delete_tree(node->next_sibling);
        delete node;
    }

}
