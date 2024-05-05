#include "Lexer.h"
#include "parser.h"
#include "Generator.h"
using namespace std;



int main()
{
	string filename = "test_true3.sig";
	Lexer Lab1;
	Lab1.Start_lex_analysis(filename);
	Parser RGR(Lab1);
	RGR.Start_syntax_analysis(filename);
	Code_Generator Lab2(RGR);
	Lab2.Start_code_generation(filename);

	return 0;
}