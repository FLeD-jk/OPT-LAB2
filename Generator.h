#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"

class CodeGenerator {
public:
	CodeGenerator(Parser& object);
	vector<Token> Lexems;
	string StrAsm;
	string Err;
	int Label;
	int LabelCounter;
	int tmp;
	int Pos;
	Tree_Node* Parse_tree;
	string ProgramName;
	void Listing(string File);
	void Start_code_generation(string File);
	void program(Tree_Node* Parser_Tree);
	void block(Tree_Node* Parser_Tree);
	void statement_list(Tree_Node* Parser_Tree);
	void statement(Tree_Node* Parser_Tree);
	void condition_statement(Tree_Node* Parser_Tree);
	void conditional_expression(Tree_Node* Parser_Tree);
	void incomplete_condition_statement(Tree_Node* Parser_Tree);
	void alternative_part(Tree_Node* Parser_Tree);
	void comparison_operator(Tree_Node* Parser_Tree);
	void expression(Tree_Node* Parser_Tree);
	void integer(Tree_Node* Parser_Tree);
	void identifier(Tree_Node* Parser_Tree);
};