#include "Generator.h"


void Code_Generator::program(Tree_Node* Parser_Tree)
{
	
	Tree_Node* Current_Node = Parser_Tree;
	Name_of_Program = Current_Node->Down->Down->Right->Down->Down->Name;
	Current_Node = Current_Node->Down->Down->Right->Right->Right->Down->Right;

	if (Current_Node->NonTerminal_name == "<statements-list>") {
		Code_line_string.append("code SEGMENT\n\tASSUME cs:code\t\n" + Name_of_Program + ":\n");
		statements_list(Current_Node);
		Code_line_string.append("mov ah, 4ch\nint 21h\ncode ends\nend " + Name_of_Program);
		return;
	}

	Error_String = "Code Generation Error: Row " + to_string(Current_Node->Row) + " column " + to_string(Current_Node->Column) + "\n";
	return;

}

void Code_Generator::statements_list(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	if (Current_Node ->NonTerminal_name == "<empty>") {
		Code_line_string.append("\tnop\n");
	}
	if (Current_Node->NonTerminal_name == "<statement>") {
		statement(Current_Node);
		Current_Node = Current_Node->Right;
		if (Current_Node->NonTerminal_name == "<statements-list>") {
			statements_list(Current_Node);
		}
	}	
}

void Code_Generator::statement(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	if (Current_Node->Code == 405) {
		Label = Label_Counter;
		Code_line_string.append("?L" + to_string(Label) + ":\n");
		int while_Label = Label;
		Label++;
		Label_Counter++;
		Current_Node = Current_Node->Right;
		if (Current_Node->NonTerminal_name == "<conditional-expression>") {
			conditional_expression(Current_Node);
			Label++;
			Label_Counter++;
			Current_Node = Current_Node->Right->Right;
			if (Current_Node->NonTerminal_name == "<statements-list>") {
				statements_list(Current_Node);
				Current_Node = Current_Node->Right;
				if (Current_Node->Code == 407) {
					Label = while_Label;
					Code_line_string.append("\tjmp ?L" + to_string(Label) + "\n");
					Label++;
					Code_line_string.append("?L" + to_string(Label) + ":\tnop\n");
				}
			}
		}
	}
	if (Current_Node->NonTerminal_name == "<conditionstatement>") {
		  condition_statement(Current_Node);
		}

}

void Code_Generator::condition_statement(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	Label = Label_Counter;
	int if_Label = Label;
	if (Current_Node->NonTerminal_name == "<incompletecondition-statement>") {
		incomplete_condition_statement(Current_Node);
		Label = if_Label;
		Code_line_string.append("?L" + to_string(Label) + ":\tnop\n");
		Label++;
		Current_Node = Current_Node->Right;
		if (Current_Node->NonTerminal_name == "<alternativepart>") {
			alternative_part(Current_Node);
			Code_line_string.append("?L" + to_string(Label) + ":\tnop\n");
		}
	}
}

void Code_Generator::incomplete_condition_statement(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down->Right;
	if (Current_Node->NonTerminal_name == "<conditional-expression>") {
		conditional_expression(Current_Node);
		Label_Counter++;
		Label++;
		int inc_temp_Label = Label;
		Label++;
		Label_Counter++;
		Current_Node = Current_Node->Right->Right;
		if (Current_Node->NonTerminal_name == "<statements-list>") {
			statements_list(Current_Node);
			//temp_label = Label_Counter;
			Label = inc_temp_Label;
			Code_line_string.append("\tjmp ?L" + to_string(Label) + "\n");
		}
		
	}
}

void Code_Generator::alternative_part(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	if (Current_Node->NonTerminal_name == "<empty>") {
		Code_line_string.append("\tnop\n");
	}
	else if( Current_Node->Code == 410) {
		int ap_temp_label = Label;
		//Label = temp_label;
		Label = Label_Counter;
		Current_Node = Current_Node->Right;
		if (Current_Node->NonTerminal_name == "<statements-list>"){
			statements_list(Current_Node);
			Label = ap_temp_label;
		}
	}
}

void Code_Generator::conditional_expression(Tree_Node* Parser_Tree){
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

void Code_Generator::comparison_operator(Tree_Node* Parser_Tree) {
	Tree_Node* Current_Node = Parser_Tree;
	Current_Node = Current_Node->Down;
	int find = 0;

	if (Current_Node->Name == "<")
	{
		Code_line_string.append("\tjge ?L" + to_string(Label) + "\n");
		find = 1;
	}
	if (Current_Node->Name == "=")
	{
		Code_line_string.append("\tlne ?L" + to_string(Label) + "\n");
		find = 1;
	}
	if (Current_Node->Name == ">")
	{
		Code_line_string.append("\tjle ?L" + to_string(Label) + "\n");
		find = 1;
	}
	if (Current_Node->Name == "<=")
	{
		Code_line_string.append("\tjg ?L" + to_string(Label) + "\n");
		find = 1;
	}
	if (Current_Node->Name == "<>")
	{
		Code_line_string.append("\tje ?L" + to_string(Label) + "\n");
		find = 1;
	}
	if (Current_Node->Name == ">=")
	{
		Code_line_string.append("\tjl ?L" + to_string(Label) + "\n");
		find = 1;
	}
	else if (find == 0) {
		Error_String = "Error generate comparation operator : Row " + to_string(Current_Node->Row) + " column " + to_string(Current_Node->Column) + "\n";
		exit(-1);
	}
}

void Code_Generator::expression(Tree_Node* Parser_Tree) {
	Tree_Node* Expression_Node_1 = Parser_Tree->Down;
	Tree_Node* Expression_Node_2 = Parser_Tree->Right->Right->Down;

	if (Expression_Node_1->NonTerminal_name == "<variable-identifier>" && Expression_Node_2->NonTerminal_name == "<variable-identifier>") {
		if (Expression_Node_1->Down->Down->Name != Name_of_Program && Expression_Node_2->Down->Down->Name != Name_of_Program) {
			Code_line_string.append("\tmov ax, " + Expression_Node_1->Down->Down->Name + "\n");
			Code_line_string.append("\tmov bx, " + Expression_Node_2->Down->Down->Name + "\n");
			Code_line_string.append("\tcmp ax, bx\n");
		}
		else {
			Code_line_string.append("\terror: <variable-identifier> can`t equal name of program \n");
			Error_String = "Error generate comparation operator : Row " + to_string(Expression_Node_1->Row) + " column " + to_string(Expression_Node_1->Column) + "\n";
			return;
		}
	}
	else if(Expression_Node_1->NonTerminal_name == "<unsigned-integer>" && Expression_Node_2->NonTerminal_name == "<unsigned-integer>") {
		Code_line_string.append("\tmov ax, " + Expression_Node_1->Down->Name + "\n");
		Code_line_string.append("\tmov bx, " + Expression_Node_2->Down->Name + "\n");
		Code_line_string.append("\tcmp ax, bx\n");
		}
	else if (Expression_Node_1->NonTerminal_name == "<variable-identifier>" && Expression_Node_2->NonTerminal_name == "<unsigned-integer>") {
		if (Expression_Node_1->Down->Down->Name != Name_of_Program) {
			Code_line_string.append("\tmov ax, " + Expression_Node_1->Down->Down->Name + "\n");
			Code_line_string.append("\tmov bx, " + Expression_Node_2->Down->Name + "\n");
			Code_line_string.append("\tcmp ax, bx\n");
		}
		else {
			Code_line_string.append("\terror: <variable-identifier> can`t equal name of program \n");
			Error_String = "Error generate comparation operator : Row " + to_string(Expression_Node_1->Row) + " column " + to_string(Expression_Node_1->Column) + "\n";
			return;
		}
	}
	else if (Expression_Node_1->NonTerminal_name == "<unsigned-integer>" && Expression_Node_2->NonTerminal_name == "<variable-identifier>") {
		if (Expression_Node_2->Down->Down->Name != Name_of_Program) {
			Code_line_string.append("\tmov ax, " + Expression_Node_1->Down->Name + "\n");
			Code_line_string.append("\tmov bx, " + Expression_Node_2->Down->Down->Name + "\n");
			Code_line_string.append("\tcmp ax, bx\n");
		}
		else {
			Code_line_string.append("\terror: <variable-identifier> can`t equal name of program \n");
			Error_String = "Error generate comparation operator : Row " + to_string(Expression_Node_2->Row) + " column " + to_string(Expression_Node_2->Column) + "\n";
			return;
		}

	}
}
