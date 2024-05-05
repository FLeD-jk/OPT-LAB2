#pragma once


#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Lexer.h"

using namespace std;

struct Tree_Node {
    int Code;
    string Name;
    int Row;
    int Column;
    string NonTerminal_name;
    bool Is_Terminal;
    Tree_Node* Right;
    Tree_Node* Down;
};


class Parser
{
private:
    vector <Token> Lexems;
    vector <Token> Key_Words;
    int Lexem_Index;
    //bool Check_IF;
    //bool Check_WHILE;
    string TreeString;
    string ErrorString;
    int Check_WHILE;
    int Check_IF;
private:
    bool Program(Tree_Node* Parser_Tree);
    bool Block(Tree_Node* Parser_Tree);
    bool Statements_list(Tree_Node* Parser_Tree);
    bool Statement(Tree_Node* Parser_Tree);
    bool Condition_statement(Tree_Node* Parser_Tree);
    bool Condition_expression(Tree_Node* Parser_Tree);
    bool Incomplete_conditionstatement(Tree_Node* Parser_Tree);
    bool Alternative_part(Tree_Node* Parser_Tree);
    bool Comparison_operator(Tree_Node* Parser_Tree);
    bool Expression(Tree_Node* Parser_Tree);
    bool Identifier(Tree_Node* Parser_Tree);
    void Check_Dot_End();
    void Check_End_Lexems();
    bool Check_After_File();
    void Errors(int Row, int Column, string message);
    void Write_Tree(Tree_Node* Root, const string space, ofstream& outputFile);
    void Tree_Listing(string File);
    Tree_Node* Initialization_Tree();
    Tree_Node* Add_New_Tree_Node(int code,int row, int column, string Name,  string Func, bool isterminal);



public:
    Tree_Node* Parse_tree;
    Parser(Lexer& object);
    void Start_syntax_analysis(string File);
};

