#include <iostream>
#include <vector>
#include <sstream>
#include "../../../include/token.h"
#include "../../../include/parsemgr.h"

int main()
{
    std::vector<Scanner::Token *> tokens;

    /*
    program Fibonacci:
    var i:integer;

    function fibonacci(n:integer):integer;
    begin
    if n=0 then return (0)
    else if n = 1 then return (1)
    else return (fibonacci ( n-1 ) + fibonacci ( n-2 ))
    end fibonacci;

    begin
    for (i:=1; i<=7; i:=i+1)
    begin
    output (fibonacci ( i ))
    end
    end Fibonacci.
    */
    tokens.push_back(new Scanner::Token(Scanner::TokenType::PROGRAM, "", 1, 1));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "Fibonacci", 9, 1));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, "", 18, 1));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::VAR, "", 1, 2));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 5, 2));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, "", 6, 2));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "integer", 7, 2));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, "", 14, 2));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::FUNCTION, "", 1, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "fibonacci", 9, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "", 18, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 19, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, "", 20, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "integer", 21, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, "", 28, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, "", 29, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "integer", 30, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, "", 37, 4));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::BEGIN, "", 1, 5));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IF, "", 5, 6));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 8, 6));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::EQUAL, "", 10, 6));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "0", 12, 6));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::THEN, "", 14, 6));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RETURN, "", 5, 7));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "", 12, 7));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "0", 13, 7));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, "", 14, 7));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::ELSE, "", 5, 8));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IF, "", 9, 8));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 12, 8));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::EQUAL, "", 14, 8));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "1", 16, 8));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::THEN, "", 18, 8));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RETURN, "", 5, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "", 12, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "1", 13, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, "", 14, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::ELSE, "", 5, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RETURN, "", 9, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "", 16, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "fibonacci", 17, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "", 26, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 27, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::MINUS, "", 29, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "1", 30, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, "", 31, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::PLUS, "", 33, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "fibonacci", 35, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "", 44, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 45, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::MINUS, "", 46, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "2", 47, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, "", 48, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, "", 49, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::END, "", 1, 11));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "fibonacci", 5, 11));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, "", 14, 11));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::BEGIN, "", 1, 13));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::FOR, "", 5, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "", 9, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 10, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::ASSIGN, "", 11, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "1", 13, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, "", 14, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 16, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LESS_THAN_EQUAL, "", 18, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "7", 21, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, "", 22, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 24, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::ASSIGN, "", 26, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 28, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::PLUS, "", 29, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "1", 31, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, "", 32, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::BEGIN, "", 1, 15));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::OUTPUT, "", 5, 16));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "", 12, 16));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "fibonacci", 13, 16));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "", 22, 16));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 23, 16));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, "", 24, 16));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, "", 25, 16));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::END, "", 1, 17));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::END, "", 1, 18));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "Fibonacci", 5, 18));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::PERIOD, "", 14, 18));

    Parser::ParseMgr::Instance().runParser(tokens);
    Parser::ParseMgr::Instance().printAST(std::cout);

    return 0;
}
