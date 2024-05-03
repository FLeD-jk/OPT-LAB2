#include "Lexer.h"
#include "Token.h"

void Lexer::Add_Token(int Code, int Row, int Column, string Name)
{
	Token symbol;
	symbol.Code = Code;
	symbol.Row = Row;
	symbol.Column = Column;
	symbol.Name = Name;
	Lexems.push_back(symbol);
}
