#include "Parser.h"


bool Parser::Program(Tree_Node* Parser_Tree) {

	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down = Add_New_Tree_Node(-1, "","<program>", false);

	if (Lexems[Lexem_Index].Code != 401) {
		Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column, ": Keyword \"PROGRAM\" is missed\n");
	}

	Current_Node->Down = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
	Current_Node = Current_Node->Down;
	Lexem_Index++;
	Check_End_Lexems();

	Current_Node->Right = Add_New_Tree_Node(-1, "", "<procedureidentifier>",false);
	Current_Node = Current_Node->Right;

	Identifier(Current_Node);

	Lexem_Index++;
	Check_End_Lexems();

	if (Lexems[Lexem_Index].Code != ';') {
		Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column, ": \";\" is missed\n");
	}

	Current_Node->Right = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
	Current_Node = Current_Node->Right;
	Lexem_Index++;
	Check_End_Lexems();

	Current_Node->Right = Add_New_Tree_Node(-1, "", "<block>",false);
	Current_Node = Current_Node->Right;
	Check_End_Lexems();

	Block(Current_Node);

	Lexem_Index++;
	Check_Dot_End();

	if (Lexems[Lexem_Index].Code != '.') {
		Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": \".\" is missed\n");
	}

	Current_Node->Right = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);

	Lexem_Index++;
	if (Check_After_File()) {
		Errors(-1, -1, "Unexpected symbol out the program!\n");
	}
	else {
		return true;
	}
}


bool Parser::Block(Tree_Node* Parser_Tree) {

	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;

	if (Lexems[Lexem_Index].Code != 402) {
		Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Keyword \"BEGIN\" is missed\n");
	}

	Current_Node->Down = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
	Current_Node = Current_Node->Down;
	Lexem_Index++;
	Check_End_Lexems();

	Current_Node->Right = Add_New_Tree_Node(-1, "", "<statements-list>",false);
	Current_Node = Current_Node->Right;

	Statements_list(Current_Node);

	Lexem_Index++;
	Check_End_Lexems();

	if (Lexems[Lexem_Index].Code != 403) {
		Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Keyword \"END\" ismissed\n");
	}

	Current_Node->Right = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
	return true;
}


bool Parser::Statements_list(Tree_Node* Parser_Tree) {

	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;
	Tree_Node* empty_Current_Node = Current_Node;
	Current_Node->Down = Add_New_Tree_Node(-1, "", "<statement>",false);
	Current_Node = Current_Node->Down;

	if (Statement(Current_Node)) {
		Lexem_Index++;
		Check_End_Lexems();
		Current_Node->Right = Add_New_Tree_Node(-1, "","<statements-list>", false);
		Current_Node = Current_Node->Right;
		Statements_list(Current_Node);
		return true;	
	}
	else {
		empty_Current_Node->Down = Add_New_Tree_Node(-1, "","<empty>", false);
		empty_Current_Node = empty_Current_Node->Down;
		Lexem_Index--;
		return true;
	}
}


bool Parser::Statement(Tree_Node* Parser_Tree) {

	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;
	int currentCode = Lexems[Lexem_Index].Code;

	if (currentCode == 405) { // while
		//Check_WHILE = true;
		Check_WHILE++;
		Current_Node->Down = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Down;
		Lexem_Index++;
		Check_End_Lexems();

		Current_Node->Right = Add_New_Tree_Node(-1, "","<conditional-expression>", false);
		Current_Node = Current_Node->Right;

		Condition_expression(Current_Node);

		Lexem_Index++;
		Check_End_Lexems();

		if (Lexems[Lexem_Index].Code != 406) {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Keyword \"DO\" is missed\n");
		}

		Current_Node->Right = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Right;
		Lexem_Index++;
		Check_End_Lexems();
		Current_Node->Right = Add_New_Tree_Node(-1, "","<statements-list>", false);
		Current_Node = Current_Node->Right;

		Statements_list(Current_Node);

		Lexem_Index++;
		Check_End_Lexems();

		if (Lexems[Lexem_Index].Code != 407) {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Keyword \"ENDWHILE\" is missed\n");
		}

		//Check_WHILE = false;
		Check_WHILE--;
		Current_Node->Right = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Right;
		Lexem_Index++;
		Check_End_Lexems();

		if (Lexems[Lexem_Index].Code != ';') {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": \";\" is missed\n");
		}
		else {
			Current_Node->Right = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
			Current_Node = Current_Node->Right;
			return true;
		}
	}
	else if (currentCode == 408) { // if
		//Check_IF = true;
		Check_IF++;
		Current_Node->Down = Add_New_Tree_Node(-1, "", "<conditionstatement>",false);
		Current_Node = Current_Node->Down;

		Condition_statement(Current_Node);

		Lexem_Index++;
		Check_End_Lexems();

		if (Lexems[Lexem_Index].Code != 404) {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column, ": Keyword \"ENDIF\" is missed\n");
		}

		//Check_IF = false;
		Check_IF--;
		Current_Node->Right =Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Right;
		Lexem_Index++;
		Check_End_Lexems();

		Current_Node->Right = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Right;

		if (Lexems[Lexem_Index].Code != ';') {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": \";\" is missed\n");
		}
		else {
			return true;
		}
	}

	else if (Lexems[Lexem_Index].Code == 410) { // ELSE
		if (Check_IF == false) {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Incorrect syntax for statement block\n");
		}
		return false;
	}
	else if (Lexems[Lexem_Index].Code == 407) { //ENDWHILE
		if (Check_WHILE == false) {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Incorrect syntax for statement block\n");
		}
		return false;
	}
	else if (Lexems[Lexem_Index].Code == 404) { // ENDIF
		if (Check_IF == false) {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Incorrect syntax for statement block\n");
		}
		return false;
	}
	else if (Lexems[Lexem_Index].Code == 403) { // END
		return false;
	}
	else if (Lexems[Lexem_Index].Code == ';') {
		if (Check_IF == false || Check_WHILE == false) {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Incorrect syntax for statement block\n");
		}
		return false;
	}
	else if (Lexems[Lexem_Index].Code != '.') {
		Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column, ": Incorrect syntax for statement block\n");
	}
	else return false;
}


bool Parser::Condition_statement(Tree_Node* Parser_Tree) {
	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node->Down = Add_New_Tree_Node(-1, "", "<incompletecondition-statement>", false);
		Current_Node = Current_Node->Down;

	Incomplete_conditionstatement(Current_Node);


	Lexem_Index++;
	Current_Node->Right = Add_New_Tree_Node(-1, "", "<alternativepart>",false);
	Current_Node = Current_Node->Right;

	Alternative_part(Current_Node);

	return true;
}


bool Parser::Incomplete_conditionstatement(Tree_Node* Parser_Tree)
{
	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;


		Current_Node->Down = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Down;
		Lexem_Index++;
		Check_End_Lexems();

		Current_Node->Right = Add_New_Tree_Node(-1, "","<conditional-expression>", false);
		Current_Node = Current_Node->Right;

		Condition_expression(Current_Node);

		Lexem_Index++;
		Check_End_Lexems();

		if (Lexems[Lexem_Index].Code != 409) {
			Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Keyword \"THEN\" is missed\n");
		}

		Current_Node->Right = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Right;
		Lexem_Index++;
		Check_End_Lexems();

		Current_Node->Right = Add_New_Tree_Node(-1, "","<statements-list>", false);
		Current_Node = Current_Node->Right;

		Statements_list(Current_Node);
		return true;

}


bool Parser::Alternative_part(Tree_Node* Parser_Tree) {
	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;

	if (Lexems[Lexem_Index].Code == 410) {
		Current_Node->Down =Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Down;
		Lexem_Index++;
		Check_End_Lexems();

		Current_Node->Right = Add_New_Tree_Node(-1, "","<statements-list>", false);
		Current_Node = Current_Node->Right;

		Statements_list(Current_Node);
		return true;
	
	}
	else {
		Current_Node->Down = Add_New_Tree_Node(-1, "", "<empty>",false);
		Lexem_Index--;
		return true;
	}
}


bool Parser::Condition_expression(Tree_Node* Parser_Tree) {
	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node->Down = Add_New_Tree_Node(-1, "", "<expression>",false);
	Current_Node = Current_Node->Down;

		Expression(Current_Node);
		Lexem_Index++;
		Current_Node->Right = Add_New_Tree_Node(-1, "", "<comparison-operator>", false);
		Current_Node = Current_Node->Right;
		Comparison_operator(Current_Node);
		Lexem_Index++;
		Current_Node->Right = Add_New_Tree_Node(-1, "", "<expression>", false);
		Current_Node = Current_Node->Right;
		Expression(Current_Node);
		return true;
		
	}

bool Parser::Expression(Tree_Node* Parser_Tree) {
	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;
	int lexemCode = Lexems[Lexem_Index].Code;
	if ((lexemCode >= CONST_BASE && lexemCode < IDN_BASE) || (lexemCode >= IDN_BASE && lexemCode < ERR_BASE)) {
		string nodeType = (lexemCode >= CONST_BASE && lexemCode < IDN_BASE) ? "<unsigned-integer>" : "<variable-identifier>";
		Current_Node->Down = Add_New_Tree_Node(-1, "", nodeType,false);
		Current_Node = Current_Node->Down;
		if (lexemCode >= IDN_BASE && lexemCode < ERR_BASE) {
			Current_Node->Down = Add_New_Tree_Node(-1, "","<identifier>", false);
			Current_Node = Current_Node->Down;
		}
		Current_Node->Down = Add_New_Tree_Node(lexemCode,Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Down;
		return true;
	}
	Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Variable identifier or unsigned integer ismissed\n");
}


bool Parser::Comparison_operator(Tree_Node* Parser_Tree) {
	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;
	if ((Lexems[Lexem_Index].Code == '<') || (Lexems[Lexem_Index].Code == '=') || (Lexems[Lexem_Index].Code == '>') || (Lexems[Lexem_Index].Code >= DM_BASE && Lexems[Lexem_Index].Code < KW_BASE)) {
		Current_Node->Down = Add_New_Tree_Node(Lexems[Lexem_Index].Code, Lexems[Lexem_Index].Name, "", true);
		Current_Node = Current_Node->Down;
		return true;
	}
	Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Comparison operator is missed\n");
}


bool Parser::Identifier(Tree_Node* Parser_Tree) {
	Check_End_Lexems();
	Tree_Node* Current_Node = Parser_Tree;
	if ((Lexems[Lexem_Index].Code >= IDN_BASE) && (Lexems[Lexem_Index].Code < ERR_BASE)) {
		Current_Node->Down = Add_New_Tree_Node(-1, "", "<identifier>", false);
		Current_Node = Current_Node->Down;
		Current_Node->Down = Add_New_Tree_Node(Lexems[Lexem_Index].Code,Lexems[Lexem_Index].Name, "", true);
		return true;
	}
	Errors(Lexems[Lexem_Index].Row, Lexems[Lexem_Index].Column,  ": Identifier is missed\n");
}


Tree_Node* Parser::Add_New_Tree_Node(int code, string name, string
	NonTerminal_name, bool Is_Terminal) {
	Tree_Node* newTree_Node = new Tree_Node;
	newTree_Node->Code = code;
	newTree_Node->Down = NULL;
	newTree_Node->Is_Terminal = Is_Terminal;
	newTree_Node->Name = name;
	newTree_Node->Right = NULL;
	newTree_Node->NonTerminal_name = new char[255];
	newTree_Node->NonTerminal_name = NonTerminal_name;
	return newTree_Node;
}


void Parser::Errors(int Row = -1, int Column = -1, string message = "") {
	if (Row == -1 && Column == -1) {
		ErrorString = "Syntactic error: " + message; 
	}
	else {
		ErrorString = "Line " + to_string(Row) + " Column " + to_string(Column) + message;
	}
	cout << ErrorString << endl;
	exit(1);
}

void Parser::Check_End_Lexems() {
	if (Lexem_Index >= Lexems.size()) {
		Errors(-1, -1 ,"Unexpected end of the file!\n"); 
	}
}

bool Parser::Check_After_File() {
	return Lexem_Index < Lexems.size();
}


void Parser::Check_Dot_End() {
	if (Lexem_Index >= Lexems.size()) {
		Errors(-1, -1, ": \".\" is missed\n");
	}
}