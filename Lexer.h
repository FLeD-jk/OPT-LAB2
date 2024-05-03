#pragma once


#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Token.h"

using namespace std;


#define DM_BASE  301
#define KW_BASE  401
#define CONST_BASE 501
#define IDN_BASE  1001
#define ERR_BASE  2001 



class Lexer
{
private:
	fstream Input_File;


	vector <Token> Delimiters;
	vector <string> Identifiers;
	vector <string> Constants;

    char symbol;
	int Row;
	int Save_Row;
	int Column;
	int Save_Column;
	int Lex_Errors_Counter;
	int Identifiers_Counter;
	int Constants_Counter;
	int Attributes[128];
	bool ERROR_FLAG;

private:
	void Input_SYMBOL();
	void Add_Token(int Code, int Row, int Column, string Name);
	void INP();
	void WS();
	void DIG();
	void LET();
	void BCOM();
	void COM(string Symbols_Buffer);
	void ECOM(string Symbols_Buffer);
	void DM1();
	void DM2();
	void ERR(string Symbols_Buffer);

	void Form_Information_table();
	void Set_Symbol_Attributes();

	int Search_Identifiers_table(string Identifier);
	int Search_Key_Words_table(string KKey_Word);
	int Search_Constants_table(string Constant);
	int Search_Delimiters_table(string Delimiter);

public:
    vector <Token> Lexems;
    vector <Token> Key_Words;
	Lexer();
	void Start_lex_analysis(string File);
	void Listing_Lexer(string File);
};

