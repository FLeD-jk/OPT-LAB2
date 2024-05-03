#include "Lexer.h"


int Lexer::Search_Identifiers_table(string Identifier)
{
	for (int i = 0; i < Identifiers.size(); i++)
	{
		if (Identifiers[i] == Identifier)
			return i;
	}
	return -1;
}

int Lexer::Search_Key_Words_table(string Key_Word)
{
	for (int i = 0; i < Key_Words.size(); i++)
	{
		if (Key_Words[i].Name == Key_Word)
			return i;
	}
	return -1;
}

int Lexer::Search_Delimiters_table(string Delimiter)
{
	for (int i = 0; i < Delimiters.size(); i++)
	{
		if (Delimiters[i].Name == Delimiter)
			return i;
	}
	return -1;
}

int Lexer::Search_Constants_table(string Constant)
{
	for (int i = 0; i < Constants.size(); i++)
	{
		if (Constants[i] == Constant)
			return i;
	}
	return -1;
}

void Lexer::Form_Information_table()
{

	Identifiers_Counter = IDN_BASE;
	Constants_Counter = CONST_BASE;
	Lex_Errors_Counter = ERR_BASE;

	Token  symbol;

	string Key_Words_Array[]{ "PROGRAM", "BEGIN", "END", "ENDIF", "WHILE", "DO", "ENDWHILE", "IF", "THEN", "ELSE" };
	for (int i = 0; i < size(Key_Words_Array); i++)
	{
		symbol.Name = Key_Words_Array[i];
		symbol.Code = KW_BASE + i;
		Key_Words.push_back(symbol);
	}

	string Double_Delimiters_Array[]{ "<=", "<>", ">=" };
	for (int i = 0; i < size(Double_Delimiters_Array); i++)
	{
		symbol.Name = Double_Delimiters_Array[i];
		symbol.Code = DM_BASE + i;
		Delimiters.push_back(symbol);
	}
}


void Lexer::Set_Symbol_Attributes()
{
	for (int i = 0; i < 128; i++)
	{
		if ((i == 8) || (i == 9) || (i == 10) || (i == 13) || (i == 32))
			Attributes[i] = 0;
		else if ((i > 47) && (i < 58))
			Attributes[i] = 1;
		else if ((i > 64) && (i < 91))
			Attributes[i] = 2;
		else if ((i == '=') || (i == '.') || (i == ';'))
			Attributes[i] = 3;
		else if ((i == '<') || (i == '>'))
			Attributes[i] = 4;
		else if (i == '(')
			Attributes[i] = 5;
		else
			Attributes[i] = 6;
	}
}
