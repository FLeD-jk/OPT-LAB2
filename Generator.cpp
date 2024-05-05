#include "Generator.h"


void Code_Generator::Start_code_generation(string File) {

	program(Parse_tree);
	Code_Generation_Listing(File);	
}

Code_Generator::Code_Generator(Parser& object): Error_String(""), Code_line_string(""), Label_Counter(0), Label(0), Parse_tree(object.Parse_tree)
{

}


