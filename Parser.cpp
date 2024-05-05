#include "Parser.h"



void Parser::Start_syntax_analysis(string File) {
    Parse_tree = Initialization_Tree();
	if (Program(Parse_tree)) {
		Tree_Listing(File);
		cout << "Syntax analysis completed successfully" << endl;
	}
}

Parser::Parser(Lexer& object) : Lexem_Index(0), ErrorString(""), Key_Words(object.Key_Words), Lexems(object.Lexems),Check_IF(0),Check_WHILE(0)
{

}


Tree_Node* Parser::Initialization_Tree() {
	Tree_Node* root = new Tree_Node;
	root->Code = -1;
	root->Down = NULL;
	root->Row = 0;
	root->Column = 0;
	root->Is_Terminal = false;
	root->Name = "";
	root->Right = NULL;
	root->NonTerminal_name = "<signal-program>";
	return root;
}