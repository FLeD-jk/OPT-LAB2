#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"

class Code_Generator {
private:
	Tree_Node* Parse_tree;
	string Code_line_string;
	string Error_String;
	int Label;
	int Label_Counter;
	int temp_label;
	string Name_of_Program;
	void Code_Generation_Listing(string File);
	void program(Tree_Node* Parser_Tree);
	void statements_list(Tree_Node* Parser_Tree);
	void statement(Tree_Node* Parser_Tree);
	void condition_statement(Tree_Node* Parser_Tree);
	void conditional_expression(Tree_Node* Parser_Tree);
	void incomplete_condition_statement(Tree_Node* Parser_Tree);
	void alternative_part(Tree_Node* Parser_Tree);
	void comparison_operator(Tree_Node* Parser_Tree);
	void expression(Tree_Node* Parser_Tree);

public:
	Code_Generator(Parser& object);
	void Start_code_generation(string File);

};