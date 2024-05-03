#include "Generator.h"


void CodeGenerator::Start_code_generation(string File) {

	program(Parse_tree);

		Listing(File);
		cout << "Code generation completed successfully" << endl;
	
}

CodeGenerator::CodeGenerator(Parser& object): Pos(0), Err(""), LabelCounter(0), Label(0), Parse_tree(object.Parse_tree)
{

}


