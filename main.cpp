#include "Lexer.h"
#include "Parser.h"
using namespace std;



int main()
{
	Lexer Lab1;
	Lab1.Start_lex_analysis("test_false1.sig");
    Parser RGR(Lab1);
    RGR.Start_syntax_analysis();
}