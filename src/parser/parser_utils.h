#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <iostream>
#include <array>
#include <algorithm>
#include "../../include/parsemgr.h"
#include "../../include/token.h"

#define TOKEN_IN(x) std::find(x.begin(), x.end(), (*nextToken)->getType()) != x.end()
#define BUILD_TREE(type, children_count) ParseMgr::Instance().build_tree(type, children_count)
#define SYNTAX_ERROR() ParseMgr::Instance().addError(*nextToken)

namespace Parser
{
    std::array<Scanner::TokenType, 3> CaseclauseSelectSet = {
        Scanner::TokenType::INTEGER,
        Scanner::TokenType::CHAR,
        Scanner::TokenType::IDENTIFIER};

    std::array<Scanner::TokenType, 12> ExpressionSelectSet = {
        Scanner::TokenType::MINUS,
        Scanner::TokenType::PLUS,
        Scanner::TokenType::NOT,
        Scanner::TokenType::EOF_TOKEN,
        Scanner::TokenType::IDENTIFIER,
        Scanner::TokenType::INTEGER,
        Scanner::TokenType::CHAR,
        Scanner::TokenType::LEFT_PAREN,
        Scanner::TokenType::SUCC,
        Scanner::TokenType::PRED,
        Scanner::TokenType::CHR,
        Scanner::TokenType::ORD};

    std::array<Scanner::TokenType, 3> TypesFollowSet = {
        Scanner::TokenType::VAR,
        Scanner::TokenType::FUNCTION,
        Scanner::TokenType::BEGIN};

    std::array<Scanner::TokenType, 2> DclnsFollowSet = {
        Scanner::TokenType::BEGIN,
        Scanner::TokenType::FUNCTION};

    std::array<Scanner::TokenType, 6> ComparisonOperators = {
        Scanner::TokenType::LESS_THAN_EQUAL,
        Scanner::TokenType::LESS_THAN,
        Scanner::TokenType::GREATER_THAN_EQUAL,
        Scanner::TokenType::GREATER_THAN,
        Scanner::TokenType::EQUAL,
        Scanner::TokenType::NOT_EQUAL};

    std::array<Scanner::TokenType, 3> AddOperators = {
        Scanner::TokenType::PLUS,
        Scanner::TokenType::MINUS,
        Scanner::TokenType::OR};

    std::array<Scanner::TokenType, 4> MulOperators = {
        Scanner::TokenType::MULTIPLY,
        Scanner::TokenType::DIVIDE,
        Scanner::TokenType::AND,
        Scanner::TokenType::MOD};
}

#endif // !PARSER_UTILS_H
