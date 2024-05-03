#include "Generator.h"




void CodeGenerator::program(Tree_Node* Parser_Tree)
{
	
	Tree_Node* Current_Node = Parser_Tree;
	ProgramName = Current_Node->Down->Down->Right->Down->Down->Name;
	Current_Node = Current_Node->Down->Down->Right->Right->Right->Down->Right;

	StrAsm.append("data SEGMENT\ndata ENDS\n");
	if (Current_Node->NonTerminal_name == "<statements-list>") {
		StrAsm.append("code SEGMENT\n\tASSUME cs:code, ds:data\t\n" + ProgramName + ":\n");
		statement_list(Current_Node);
		StrAsm.append("mov ah, 4ch\nint 21h\ncode ends\nend " + ProgramName);
	}
	else {
		//Error++;
		//StrError += "Code Generator Eror: line " + to_string(Current_Node->Down) + " column " + to_string(Current_Node->Down) + "\n";
		return;
	}	
}


void CodeGenerator::statement_list(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	if (Current_Node ->NonTerminal_name == "<empty>") {
		StrAsm.append("\tnop\n");
	}
	if (Current_Node->NonTerminal_name == "<statement>") {
		statement(Current_Node);
		Current_Node = Current_Node->Right;
		if (Current_Node->NonTerminal_name == "<statements-list>") {
			statement_list(Current_Node);

		}
	}


	
}

void CodeGenerator::statement(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	if (Current_Node->Code == 405) {
		Label = LabelCounter;
		StrAsm.append("?L" + to_string(Label) + ":\n");
		int whileLabel = Label;
		Label++;
		LabelCounter++;
		Current_Node = Current_Node->Right;
		if (Current_Node->NonTerminal_name == "<conditional-expression>") {
			conditional_expression(Current_Node);
			Label++;
			LabelCounter++;
			Current_Node = Current_Node->Right->Right;
			if (Current_Node->NonTerminal_name == "<statements-list>") {
				statement_list(Current_Node);
				Current_Node = Current_Node->Right;
				if (Current_Node->Code == 407) {
					Label = whileLabel;
					StrAsm.append("\tjmp ?L" + to_string(Label) + "\n");
					Label++;
					StrAsm.append("?L" + to_string(Label) + ":\tnop\n");
				}
		}
	}


	}
	if (Current_Node->NonTerminal_name == "<conditionstatement>") {
		  condition_statement(Current_Node);
		}
	/*
	if (condition_statement(Current_Node)) {
		Pos++;
		if (Lexems[Pos].Code != 404) {
			return;
		}
		Pos++;
		if (Lexems[Pos].Code != ';') {
			return;
		}
		return;
	}
	*/
}



void CodeGenerator::condition_statement(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	int ifLabel = Label;
	if (Current_Node->NonTerminal_name == "<incompletecondition-statement>") {
		incomplete_condition_statement(Current_Node);
		Label = ifLabel;
		StrAsm.append("?L" + to_string(Label) + ":\tnop\n");
		Label++;
		LabelCounter;
		Current_Node = Current_Node->Right;
		if (Current_Node->NonTerminal_name == "<alternativepart>") {
			alternative_part(Current_Node);
			StrAsm.append("?L" + to_string(Label) + ":\tnop\n");
		}
	}
}


void CodeGenerator::incomplete_condition_statement(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down->Right;
	if (Current_Node->NonTerminal_name == "<conditional-expression>") {
		conditional_expression(Current_Node);
		LabelCounter++;
		Label++;
		int tempLabel = Label;
		Label++;
		LabelCounter++;
		Current_Node = Current_Node->Right->Right;
		if (Current_Node->NonTerminal_name == "<statements-list>") {
			statement_list(Current_Node);
			tmp = Label;
			Label = tempLabel;
			StrAsm.append("\tjmp ?L" + to_string(Label) + "\n");
		}
		
	}
}

void CodeGenerator::alternative_part(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	if (Current_Node->NonTerminal_name == "<empty>") {
		StrAsm.append("\tnop\n");
	}
	else if( Current_Node->Code == 410) {
		int tempLabel = Label;
		Label = tmp;
		Current_Node = Current_Node->Right;
		if (Current_Node->NonTerminal_name == "<statements-list>") {
			statement_list(Current_Node);
			Label = tempLabel;
		}
	}
}


void CodeGenerator::conditional_expression(Tree_Node* Parser_Tree){
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	if (Current_Node->NonTerminal_name == "<expression>" && Current_Node->Right->Right->NonTerminal_name == "<expression>") {
				expression(Current_Node);
				Current_Node = Current_Node->Right;
				if (Current_Node->NonTerminal_name == "<comparison-operator>") {
					comparison_operator(Current_Node);
			}
		}
		}


void CodeGenerator::comparison_operator(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	if ((Current_Node->Name == "<") || (Current_Node->Name == "=") || (Current_Node->Name == ">") ||
		(Current_Node->Code >= DM_BASE && Current_Node->Code < KW_BASE))
	{
		switch (Current_Node->Code)
		{
		case 60:
			StrAsm.append("\tjge ?L" + to_string(Label) + "\n");
			break;
		case 61:
			StrAsm.append("\tlne ?L" + to_string(Label) + "\n");
			break;
		case 62:
			StrAsm.append("\tjle ?L" + to_string(Label) + "\n");
			break;
		case 301:
			StrAsm.append("\tjg ?L" + to_string(Label) + "\n");
			break;
		case 302:
			StrAsm.append("\tje ?L" + to_string(Label) + "\n");
			break;
		case 303:
			StrAsm.append("\tjl ?L" + to_string(Label) + "\n");
			break;
		}
	}
}


void CodeGenerator::expression(Tree_Node* Parser_Tree) {
	Tree_Node* Expression_Node_1 = Parser_Tree->Down;
	Tree_Node* Expression_Node_2 = Parser_Tree->Right->Right->Down;
	if (Expression_Node_1->NonTerminal_name == "<variable-identifier>" && Expression_Node_2->NonTerminal_name == "<variable-identifier>") {
		if (Expression_Node_1->Name != ProgramName && Expression_Node_2->Name != ProgramName) {
			StrAsm.append("\tmov ax, " + Expression_Node_1->Down->Down->Name + "\n");
			StrAsm.append("\tmov bx, " + Expression_Node_2->Down->Down->Name + "\n");
		}
	}
	else if(Expression_Node_1->NonTerminal_name == "<unsigned-integer>" && Expression_Node_2->NonTerminal_name == "<unsigned-integer>") {
			StrAsm.append("\tmov ax, " + Expression_Node_1->Down->Name + "\n");
			StrAsm.append("\tmov bx, " + Expression_Node_2->Down->Name + "\n");
		}
	else if (Expression_Node_1->NonTerminal_name == "<variable-identifier>" && Expression_Node_2->NonTerminal_name == "<unsigned-integer>") {
		if (Expression_Node_1->Name != ProgramName) {
			StrAsm.append("\tmov ax, " + Expression_Node_1->Down->Down->Name + "\n");
			StrAsm.append("\tmov bx, " + Expression_Node_2->Down->Name + "\n");
		}
	}
	else if (Expression_Node_1->NonTerminal_name == "<variable-identifier>" && Expression_Node_2->NonTerminal_name == "<unsigned-integer>") {
		if (Expression_Node_2->Name != ProgramName) {
			StrAsm.append("\tmov ax, " + Expression_Node_1->Down->Name + "\n");
			StrAsm.append("\tmov bx, " + Expression_Node_2->Down->Down->Name + "\n");
		}
	}
}
