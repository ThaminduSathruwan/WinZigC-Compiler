#include <iostream>
#include <vector>
#include <stack>
#include "../../include/token.h"
#include "../../include/ast.h"

namespace Parser
{

    ASTNode::ast_node(ASTNodeType type, uint32_t childrenCnt) : type(type), childrenCnt(childrenCnt), first_child(nullptr), next_sibling(nullptr)
    {
    }

    ASTNode::~ast_node()
    {
    }

    std::string ASTNode::toString() const
    {
        std::string typeStr;
        switch (type)
        {
        case PROGRAM:
            typeStr = "program";
            break;
        case CONSTS:
            typeStr = "consts";
            break;
        case CONST:
            typeStr = "const";
            break;
        case TYPES:
            typeStr = "types";
            break;
        case TYPE:
            typeStr = "type";
            break;
        case LIT:
            typeStr = "lit";
            break;
        case SUBPROGS:
            typeStr = "subprogs";
            break;
        case FCN:
            typeStr = "fcn";
            break;
        case PARAMS:
            typeStr = "params";
            break;
        case DCLNS:
            typeStr = "dclns";
            break;
        case VAR:
            typeStr = "var";
            break;
        case BLOCK:
            typeStr = "block";
            break;
        case OUTPUT:
            typeStr = "output";
            break;
        case IF:
            typeStr = "if";
            break;
        case WHILE:
            typeStr = "while";
            break;
        case REPEAT:
            typeStr = "repeat";
            break;
        case FOR:
            typeStr = "for";
            break;
        case LOOP:
            typeStr = "loop";
            break;
        case CASE:
            typeStr = "case";
            break;
        case READ:
            typeStr = "read";
            break;
        case EXIT:
            typeStr = "exit";
            break;
        case RETURN:
            typeStr = "return";
            break;
        case NULL_:
            typeStr = "<null>";
            break;
        case INTEGER:
            typeStr = "integer";
            break;
        case STRING:
            typeStr = "string";
            break;
        case CASE_CLAUSE:
            typeStr = "case_clause";
            break;
        case CASE_DOTS:
            typeStr = "..";
            break;
        case OTHERWISE:
            typeStr = "otherwise";
            break;
        case ASSIGN:
            typeStr = "assign";
            break;
        case SWAP:
            typeStr = "swap";
            break;
        case TRUE:
            typeStr = "true";
            break;
        case LEQ:
            typeStr = "<=";
            break;
        case LT:
            typeStr = "<";
            break;
        case GEQ:
            typeStr = ">=";
            break;
        case GT:
            typeStr = ">";
            break;
        case EQ:
            typeStr = "=";
            break;
        case NEQ:
            typeStr = "<>";
            break;
        case PLUS:
            typeStr = "+";
            break;
        case NEG:
            typeStr = "-";
            break;
        case OR:
            typeStr = "or";
            break;
        case MUL:
            typeStr = "*";
            break;
        case DIV:
            typeStr = "/";
            break;
        case AND:
            typeStr = "and";
            break;
        case MOD:
            typeStr = "mod";
            break;
        case NOT:
            typeStr = "not";
            break;
        case EOF_:
            typeStr = "eof";
            break;
        case CALL:
            typeStr = "call";
            break;
        case SUCC:
            typeStr = "succ";
            break;
        case PRED:
            typeStr = "pred";
            break;
        case CHR:
            typeStr = "chr";
            break;
        case ORD:
            typeStr = "ord";
            break;
        case ID:
            typeStr = "<identifier>";
            break;
        case INT:
            typeStr = "<integer>";
            break;
        case CHAR:
            typeStr = "<char>";
            break;
        case STR:
            typeStr = "<string>";
            break;
        default:
            typeStr = "<unknown>";
            break;
        }
        return typeStr + "(" + std::to_string(childrenCnt) + ")";
    }

    AST::AST() : root(nullptr)
    {
    }

    AST::~AST()
    {
        delete_tree(root);
    }

    void AST::build_tree(ASTNodeType type, int childrenCnt)
    {
        ASTNode *p = nullptr;
        for (int i = 0; i < childrenCnt; ++i)
        {
            if (node_stack.empty())
            {
                return;
            }
            ASTNode *c = node_stack.top();
            node_stack.pop();
            c->next_sibling = p;
            p = c;
        }
        ASTNode *node = new ASTNode(type, childrenCnt);
        node->first_child = p;
        node_stack.push(node);
    }

    void AST::build_tree(std::string str, bool identifier)
    {
        ASTNode *node = nullptr;
        if (identifier)
        {
            node = new IdentifierVal(str);
        }
        else
        {
            node = new StringVal(str);
        }
        node_stack.push(node);
    }

    void AST::build_tree(int32_t integer)
    {
        ASTNode *node = new IntegerVal(integer);
        node_stack.push(node);
    }

    void AST::build_tree(char character)
    {
        ASTNode *node = new CharacterVal(character);
        node_stack.push(node);
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
            return;
        }

        for (int i = 0; i < depth; ++i)
        {
            os << ". ";
        }

        os << node->toString() << std::endl;

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

    void AST::finalize()
    {
        if (node_stack.empty())
        {
            return;
        }
        root = node_stack.top();
        node_stack.pop();
    }

    IdentifierVal::identifier_node(std::string name) : ast_node(ID_VAL, 0), name(name)
    {
    }

    IdentifierVal::~identifier_node()
    {
    }

    std::string IdentifierVal::toString() const
    {
        return name + "(0)";
    }

    IntegerVal::integer_node(int32_t value) : ast_node(INT_VAL, 0), value(value)
    {
    }

    IntegerVal::~integer_node()
    {
    }

    std::string IntegerVal::toString() const
    {
        return std::to_string(value) + "(0)";
    }

    CharacterVal::char_node(char character) : ast_node(CHAR_VAL, 0), character(character)
    {
    }

    CharacterVal::~char_node()
    {
    }

    std::string CharacterVal::toString() const
    {
        return "'" + std::string(1, character) + "'(0)";
    }

    StringVal::str_node(std::string str) : ast_node(STR_VAL, 0), str(str)
    {
    }

    StringVal::~str_node()
    {
    }

    std::string StringVal::toString() const
    {
        return "\"" + str + "\"(0)";
    }

}
