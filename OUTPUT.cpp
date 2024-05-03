#include "Lexer.h"
#include "Parser.h"
#include "Generator.h"

void Lexer::Listing_Lexer(string File)
{
	File = "Lexer_Listing_" + File;
	ofstream File_Output(File);
    File_Output << setw(10) << left << "Row" << setw(10) << left << "Column" << setw(10) << left << "Code" << setw(20) << left << "Lexem" << endl << endl;
	for (int i = 0; i < Lexems.size(); i++)
	{
		if (Lexems[i].Code < ERR_BASE)
			File_Output << setw(10) << left << Lexems[i].Row << setw(10) << left << Lexems[i].Column << setw(10) << left << Lexems[i].Code << setw(20) << left << Lexems[i].Name << endl;
	}
    File_Output << endl << endl;

	if (ERROR_FLAG == 1)
		for (int i = 0; i < Lexems.size(); i++)
			for (int j = ERR_BASE; j < Lex_Errors_Counter; j++)
				if (Lexems[i].Code == j)
                    File_Output << "Lexer: Error " << Lexems[i].Code << "(Row " << Lexems[i].Row << ", Column " << Lexems[i].Column << "): ImLexem_Indexible characters combination: " << Lexems[i].Name << endl;

    File_Output.close();
}


void Parser::Tree_Listing(string File) {
    TreeString = "";
    File = "Syntax_Listing_" + File;
    ofstream File_Output(File);
    if (!ErrorString.empty())
        File_Output << ErrorString << endl;
    else {
        Write_Tree(Parse_tree, "", File_Output);
        File_Output << TreeString << endl;
    }
}

void Parser::Write_Tree(Tree_Node* Root, const string space, ofstream& File_Output) {
    while (Root != nullptr) {
        if (Root->Is_Terminal)
            File_Output << space << to_string(Root->Code) << " " << Root->Name << "\n";
        else
            File_Output << space << Root->NonTerminal_name << "\n";
        if (Root->Down != nullptr) {
            string newSpace = space + "    ";
            Write_Tree(Root->Down, newSpace, File_Output);
        }
        Root = Root->Right;
    }
}


void CodeGenerator::Listing(string File)
{
    File += "generated.txt";
    ofstream f;
    f.open(File, std::ios::app);
    if (Err != "") {
        cout << "Code Generator completed with error" << endl << Err << endl << endl;
        f << "Code Generator completed with error" << endl << Err << endl;
    }
    else {
        cout << "code generator completed successfuly" << endl << endl;
        f << StrAsm << endl << endl;
    }
}
