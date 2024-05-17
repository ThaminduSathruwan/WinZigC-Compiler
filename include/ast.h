#ifndef AST_H
#define AST_H

#include <iostream>
#include <vector>
#include <stack>
#include "token.h"

namespace Parser
{
    typedef enum ASTNodeType
    {
        PROGRAM,
        CONSTS,
        CONST,
        TYPES,
        TYPE,
        LIT,
        SUBPROGS,
        FCN,
        PARAMS,
        DCLNS,
        VAR,
        BLOCK,
        OUTPUT,
        IF,
        WHILE,
        REPEAT,
        FOR,
        LOOP,
        CASE,
        READ,
        EXIT,
        RETURN,
        NULL_,
        INTEGER,
        STRING,
        CASE_CLAUSE,
        CASE_DOTS,
        OTHERWISE,
        ASSIGN,
        SWAP,
        TRUE,
        LEQ,
        LT,
        GEQ,
        GT,
        EQ,
        NEQ,
        PLUS,
        NEG,
        OR,
        MUL,
        DIV,
        AND,
        MOD,
        NOT,
        EOF_,
        CALL,
        SUCC,
        PRED,
        CHR,
        ORD,
        ID,
        INT,
        CHAR,
        STR,
        ID_VAL,
        INT_VAL,
        CHAR_VAL,
        STR_VAL
    } ASTNodeType;

    typedef struct ast_node
    {
        ast_node(ASTNodeType type, uint32_t childrenCnt);
        virtual ~ast_node();
        ASTNodeType type;
        uint32_t childrenCnt;
        struct ast_node *first_child;
        struct ast_node *next_sibling;
        virtual std::string toString() const;
    } ASTNode;

    typedef std::pair<std::string, int> BuildNode;
    typedef std::vector<BuildNode> BuildNodeList;

    class AST
    {
    public:
        AST();
        ~AST();
        void build_tree(ASTNodeType type, int childrenCnt);
        void build_tree(std::string str, bool identifier = true);
        void build_tree(int32_t integer);
        void build_tree(char character);
        friend std::ostream &operator<<(std::ostream &os, const AST &ast);

    private:
        ASTNode *root;
        std::stack<ASTNode *> node_stack;
        void preorder_traversal(ASTNode *node, int depth, std::ostream &os) const;
        void delete_tree(ASTNode *node);
    };

    typedef struct identifier_node : public ast_node
    {
        identifier_node(std::string name);
        virtual ~identifier_node();
        std::string name;
        virtual std::string toString() const override;
    } IdentifierVal;

    typedef struct integer_node : public ast_node
    {
        integer_node(int32_t value);
        virtual ~integer_node();
        int32_t value;
        virtual std::string toString() const override;
    } IntegerVal;

    typedef struct char_node : public ast_node
    {
        char_node(char character);
        virtual ~char_node();
        char character;
        virtual std::string toString() const override;
    } CharacterVal;

    typedef struct str_node : public ast_node
    {
        str_node(std::string str);
        virtual ~str_node();
        std::string str;
        virtual std::string toString() const override;
    } StringVal;
}

#endif // !AST_H
