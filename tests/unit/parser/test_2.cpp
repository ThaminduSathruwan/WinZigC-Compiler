#include <iostream>
#include <vector>
#include <sstream>
#include "../../../include/token.h"
#include "../../../include/parsemgr.h"

int main()
{
    std::vector<Scanner::Token *> tokens;

    /*
    {
    program TestPrimes:

    var n:integer;

    function IsPrime ( n : integer ) : boolean;
    var
        i : integer;
        Prime : boolean;
    begin

        Prime := (n=2) or (n mod 2 = 1);  # either 2 or an odd number

        i := 3;
        while Prime and (i*i <= n) do
        if n mod i = 0 then Prime := false
                else i := i + 2;
        return (Prime)

    end IsPrime;

    begin

        repeat
        read(n);
        case IsPrime ( n ) of
            true:  output(1);
            false: output(0);
        end
        until eof

    end TestPrimes.
    */
    tokens.push_back(new Scanner::Token(Scanner::TokenType::PROGRAM, "program", 1, 1));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "TestPrimes", 3, 5));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, ":", 3, 15));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::VAR, "var", 5, 5));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 6, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, ":", 6, 10));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "integer", 6, 12));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 6, 18));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::FUNCTION, "function", 8, 5));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "IsPrime", 8, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "(", 8, 21));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 8, 23));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, ":", 8, 25));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "integer", 8, 27));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, ")", 8, 34));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, ":", 8, 36));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "boolean", 8, 38));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 8, 45));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::VAR, "var", 10, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 11, 13));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, ":", 11, 15));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "integer", 11, 17));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 11, 23));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "Prime", 12, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, ":", 12, 15));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "boolean", 12, 17));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 12, 24));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::BEGIN, "begin", 14, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "Prime", 16, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::ASSIGN, ":=", 16, 15));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "(", 16, 18));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 16, 19));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::EQUAL, "=", 16, 21));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "2", 16, 23));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, ")", 16, 24));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::OR, "or", 16, 26));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "(", 16, 29));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 16, 30));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::MOD, "mod", 16, 32));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "2", 16, 36));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::EQUAL, "=", 16, 38));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "1", 16, 40));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, ")", 16, 41));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 16, 42));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 18, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::ASSIGN, ":=", 18, 11));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "3", 18, 14));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 18, 15));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::WHILE, "while", 19, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "Prime", 19, 15));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::AND, "and", 19, 21));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "(", 19, 25));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 19, 26));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::MULTIPLY, "*", 19, 28));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 19, 30));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LESS_THAN_EQUAL, "<=", 19, 32));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 19, 35));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, ")", 19, 36));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::DO, "do", 19, 38));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IF, "if", 20, 13));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 20, 16));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::MOD, "mod", 20, 18));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 20, 22));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::EQUAL, "=", 20, 24));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "0", 20, 26));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::THEN, "then", 20, 28));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "Prime", 20, 33));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::ASSIGN, ":=", 20, 39));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "false", 20, 42));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::ELSE, "else", 21, 13));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 21, 18));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::ASSIGN, ":=", 21, 20));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "i", 21, 23));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::PLUS, "+", 21, 25));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "2", 21, 27));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 21, 28));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RETURN, "return", 22, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "(", 22, 16));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "Prime", 22, 17));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, ")", 22, 22));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::END, "end", 24, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "IsPrime", 26, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 26, 19));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::BEGIN, "begin", 28, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::REPEAT, "repeat", 28, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::READ, "read", 29, 13));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "(", 29, 18));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 29, 19));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, ")", 29, 20));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 29, 21));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::CASE, "case", 30, 13));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "IsPrime", 30, 18));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "(", 30, 25));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "n", 30, 26));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, ")", 30, 27));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::OF, "of", 30, 29));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "true", 31, 17));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, ":", 31, 21));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::OUTPUT, "output", 32, 17));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "(", 32, 24));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "1", 32, 25));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, ")", 32, 26));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 32, 27));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "false", 33, 17));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::COLON, ":", 33, 22));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::OUTPUT, "output", 34, 17));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::LEFT_PAREN, "(", 34, 24));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::INTEGER, "0", 34, 25));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::RIGHT_PAREN, ")", 34, 26));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::SEMICOLON, ";", 34, 27));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::END, "end", 35, 13));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::UNTIL, "until", 35, 17));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::EOF_TOKEN, "eof", 35, 23));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::END, "end", 37, 5));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::IDENTIFIER, "TestPrimes", 37, 9));
    tokens.push_back(new Scanner::Token(Scanner::TokenType::PERIOD, ".", 37, 19));

    Parser::ParseMgr::Instance().runParser(tokens);
    Parser::ParseMgr::Instance().printAST(std::cout);

    return 0;
}
