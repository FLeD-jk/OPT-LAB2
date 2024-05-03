#include "Lexer.h"





void Lexer::INP()
{
	Input_SYMBOL();
	while (!Input_File.eof())
	{
		switch (Attributes[symbol])
		{
		case 0:
			WS();
			break;
		case 1:
			DIG();
			break;
		case 2:
			LET();
			break;
		case 3:
			DM1();
			break;
		case 4:
			DM2();
			break;
		case 5:
			BCOM();
			break;
		case 6:
			ERR("");
			break;
		}
	}
}


void Lexer::Input_SYMBOL() {
	symbol = Input_File.get();

	if (symbol == '\n')
	{
		Row++;
		Column = 0;
	}
	else if (symbol == '\t')
		Column += 4;
	else
		Column++;

}

void Lexer::WS()
{
	do
	{
		Input_SYMBOL();
	} while (Attributes[symbol] == 0);
}


void Lexer::DIG()
{
	Save_Row = Row;
	Save_Column = Column;
	string symbols_Buffer = "";
	while ((!Input_File.eof()) && (Attributes[symbol] == 1))
	{
		symbols_Buffer += symbol;
		Input_SYMBOL();
	}
	int searching_result = Search_Constants_table(symbols_Buffer);
	if (searching_result == -1)
	{
		Add_Token(Constants_Counter, Save_Row, Save_Column, symbols_Buffer);
		Constants.push_back(symbols_Buffer);
		Constants_Counter++;
	}
	else
		Add_Token(searching_result + CONST_BASE, Save_Row, Save_Column, symbols_Buffer);
}


void Lexer::LET()
{
	Save_Row = Row;
	Save_Column = Column;
	string symbols_Buffer = "";
	while ((!Input_File.eof()) && ((Attributes[symbol] == 2) || (Attributes[symbol] == 1)))
	{
		symbols_Buffer += symbol;
		Input_SYMBOL();
	}
	int searching_result = Search_Key_Words_table(symbols_Buffer);
	if (searching_result == -1)
	{
		searching_result = Search_Identifiers_table(symbols_Buffer);
		if (searching_result == -1)
		{
			Add_Token(Identifiers_Counter, Save_Row, Save_Column, symbols_Buffer);
			Identifiers.push_back(symbols_Buffer);
			Identifiers_Counter++;
		}
		else
			Add_Token(searching_result + IDN_BASE, Save_Row, Save_Column, symbols_Buffer);
	}
	else
		Add_Token(Key_Words[searching_result].Code, Save_Row, Save_Column, Key_Words[searching_result].Name);
}



void Lexer::BCOM()
{
	string symbols_Buffer;
	symbols_Buffer += symbol;
	Input_SYMBOL();
	if (symbol == '*')
		COM(symbols_Buffer);
	else
		ERR(symbols_Buffer);
}

void Lexer::COM(string Symbols_Buffer)
{
	Symbols_Buffer += symbol;
	Input_SYMBOL();
	if (symbol == '*')
	{
		ECOM(Symbols_Buffer);
	}
	else if (Input_File.eof()) {
		ERR(Symbols_Buffer);
	}
	else {
		COM(Symbols_Buffer);
	}

}

void Lexer::ECOM(string Symbols_Buffer)
{
	Symbols_Buffer += symbol;
	Input_SYMBOL();
	if (symbol == ')') {
		Input_SYMBOL();
		return;
	}
	else if (symbol == '*') {
		ECOM(Symbols_Buffer);
	}
	else if (Input_File.eof()) {
		Symbols_Buffer += symbol;
		ERR(Symbols_Buffer);
	}
	else {
		COM(Symbols_Buffer);
	}

}

void Lexer::DM1()
{
	string Symbols_Buffer = "";
	Symbols_Buffer += symbol;
	Add_Token(symbol, Row, Column, Symbols_Buffer);
	Input_SYMBOL();
	return;
}

void Lexer::DM2()
{
	Save_Row = Row;
	Save_Column = Column;
	string Symbols_Buffer = "";
	Symbols_Buffer += symbol;
	int searching_result;
	if (symbol == '<') {
		Input_SYMBOL();
		Symbols_Buffer += symbol;
		searching_result = Search_Delimiters_table(Symbols_Buffer);
		if (searching_result == -1)
			Add_Token('<', Save_Row, Save_Column, "<");
		else
		{
			Add_Token(Delimiters[searching_result].Code, Save_Row, Save_Column, Delimiters[searching_result].Name);
			Input_SYMBOL();
		}
	}
	else if (symbol == '>') {
		//Symbols_Buffer += symbol;
		Input_SYMBOL();
		Symbols_Buffer += symbol;
		searching_result = Search_Delimiters_table(Symbols_Buffer);
		if (searching_result == -1)
			Add_Token('>', Save_Row, Save_Column, ">");
		else
		{
			Add_Token(Delimiters[searching_result].Code, Save_Row, Save_Column, Delimiters[searching_result].Name);
			Input_SYMBOL();
		}
	}
}

void Lexer::ERR(string Symbols_Buffer)
{
	Add_Token(Lex_Errors_Counter, Save_Row, Save_Column, Symbols_Buffer + symbol);
	Lex_Errors_Counter++;
	ERROR_FLAG = 1;
	Input_SYMBOL();

}