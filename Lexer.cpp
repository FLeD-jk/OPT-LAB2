#include "Lexer.h"



Lexer::Lexer() : Row(1), Column(0), Save_Row(1), Save_Column(0), symbol(' '), ERROR_FLAG(0)
{
	 Form_Information_table();
	 Set_Symbol_Attributes();
}



void Lexer::Start_lex_analysis(string File)
{
	Input_File.open(File);
	if (!Input_File.is_open())
	{
		cout << "Failed to open!!! (" << File << ")" << endl;
		return;
	}
	else if (Input_File.peek() == '\0')
	{
		cout << "File is empty!!! (" << File << ")" << endl;
		return;
	}
	else {
		INP();
		Listing_Lexer(File);
	}
}









