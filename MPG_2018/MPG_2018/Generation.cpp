#pragma once
#include "pch.h"
#include "Generation.h"
std::ofstream f("D:\\MPG2018\\Generation\\Generation\\Gen.asm");
bool isFunction = false;
int idFunc;
int buf;
int equal;
int rhesis;
void DotConst(Lexer::LEX Tables) {
	f << "\n.const";
	for (int i = 0; i < Tables.Lextable.size; i++) {
		if (Tables.Lextable.table[i].lexema == LEX_ID) {
			int buf = Tables.Lextable.table[i].idxTI;
			if (Tables.IDtable.table[buf].iddatatype == 2 && Tables.Lextable.table[i - 2].lexema == LEX_DECLARE && Tables.Lextable.table[i + 1].lexema == LEX_EQUAL) {
				if (Tables.Lextable.table[i+4].lexema == LEX_PLUS) {}
				else {
					f << "\n " << Tables.IDtable.table[buf].id << "\tbyte " << Tables.IDtable.table[buf].value.vstr.str << ", 0";
				}
			}
			else if (Tables.IDtable.table[buf].iddatatype == 2 && Tables.Lextable.table[i - 1].lexema != LEX_DECLARE) {}
		}
		if (Tables.Lextable.table[i].lexema == LEX_LITERAL && Tables.IDtable.table[Tables.Lextable.table[i].idxTI].iddatatype == 2) {
			int buf = Tables.Lextable.table[i].idxTI;
			if (Tables.Lextable.table[i - 1].lexema == LEX_PRINT) {
				f << "\n " << Tables.IDtable.table[buf].id << "\tbyte " << Tables.IDtable.table[buf].value.vstr.str << ", 0";
			}
		}
		else if (Tables.Lextable.table[i].lexema == LEX_LITERAL && Tables.IDtable.table[Tables.Lextable.table[i].idxTI].iddatatype == 1) {
			int buf = Tables.Lextable.table[i].idxTI;
			if (Tables.Lextable.table[i - 1].lexema == LEX_PRINT) {
				f << "\n " << Tables.IDtable.table[buf].id << "\tdword " << Tables.IDtable.table[buf].value.vint;
			}
		}
	}
}
void DotData(Lexer::LEX Tables) {
	f << "\n.data";
	f << "\nbuffer\tbyte 256 dup(0)";
	for (int i = 0; i < Tables.Lextable.size; i++) {
		if (Tables.Lextable.table[i].lexema == LEX_ID) {
			int buf = Tables.Lextable.table[i].idxTI;
			if (Tables.IDtable.table[buf].iddatatype == 2 && Tables.Lextable.table[i - 2].lexema == LEX_DECLARE && Tables.Lextable.table[i + 1].lexema == LEX_EQUAL) {
				if (Tables.Lextable.table[i + 4].lexema == LEX_PLUS) {
					f << "\n" << Tables.IDtable.table[buf].id << "\tdword 0";
				}
			}
			if (Tables.IDtable.table[buf].idtype == 3) {}
			else
				if (Tables.IDtable.table[buf].iddatatype == 1 && Tables.Lextable.table[i - 2].lexema == LEX_DECLARE) {
					if (Tables.Lextable.table[i + 1].lexema == LEX_EQUAL && Tables.Lextable.table[i + 2].lexema == LEX_LITERAL && Tables.Lextable.table[i + 3].lexema == LEX_MINUS && Tables.Lextable.table[i + 4].lexema == LEX_SEMICOLON) {
						Tables.IDtable.table[buf].value.vint = -Tables.IDtable.table[Tables.Lextable.table[i + 2].idxTI].value.vint;
					}
						if (Tables.IDtable.table[buf].value.vint == 0) {
							f << "\n" << Tables.IDtable.table[buf].id << "\tdword 0";
						}
						else {
							f << "\n" << Tables.IDtable.table[buf].id << "\tdword " << Tables.IDtable.table[buf].value.vint;
						}
				}
				else if (Tables.IDtable.table[buf].iddatatype == 2 && Tables.Lextable.table[i - 2].lexema == LEX_DECLARE && Tables.Lextable.table[i + 1].lexema == LEX_SEMICOLON) {
					f << "\n" << Tables.IDtable.table[buf].id << "\tdword 0";
				}
		}
	}
	f << "\n.code";
}

bool isGenerated(Lexer::LEX Tables) {
	bool fl = false;
	f << HEAD;
	f << "\n";
	f << "\n.stack 4096\n";
	DotConst(Tables);
	f << "\n";
	DotData(Tables);
	f << "\n";
	for (int i = 0; i < Tables.Lextable.size; i++) {
		switch (Tables.Lextable.table[i].lexema)
		{
		case LEX_GO:
			isFunction = false;
			f << "\nmain PROC";
			break;
		case LEX_FUNCTION:
			isFunction = true;
			idFunc = Tables.Lextable.table[i + 1].idxTI;
			buf = Tables.Lextable.table[i + 1].idxTI;
			f << "\n" << Tables.IDtable.table[buf].id << " PROC ";
			i++;
			while (Tables.Lextable.table[i].lexema != ')')
			{
				rhesis = i;
				i++;
			}
			while (Tables.Lextable.table[i].lexema != '(')
			{
				if (Tables.Lextable.table[i].lexema == 'i')
				{
					if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].iddatatype == 1)
					{
						f << Tables.IDtable.table[Tables.Lextable.table[i].idxTI].id << ":DWORD";
						if (Tables.Lextable.table[i - 2].lexema != '(')
							f << ", ";
					}
				}
				i--;
			}
			break;

		case LEX_RIGHTBRACE:
			if (isFunction) {
				f << "\n" << Tables.IDtable.table[idFunc].id << " ENDP\n";
			}
			else {
				f << "\n\n push 0";
				f << "\n call ExitProcess";
				f << "\nmain ENDP";
			}
			break;

		case LEX_PRINT:
			if (Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].iddatatype == 2) {
				if (fl) {
					f << "\n push " << Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].id;
					fl = false;
				}
				else {
					f << "\n push offset " << Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].id;
				}
				f << "\n call output_str";
			}
			if (Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].iddatatype == 1) {
				f << "\n push " << Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].id;
				f << "\n call output_int";
			}
			break;

		case LEX_EQUAL:
			equal = i;
			while (Tables.Lextable.table[i].lexema != LEX_SEMICOLON) {
				
				if (Tables.Lextable.table[i].lexema == LEX_ID) {
					if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].iddatatype == 1 && (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == 1 || Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == 3)) {
							f << "\n push " << Tables.IDtable.table[Tables.Lextable.table[i].idxTI].id;
					}
					else if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].iddatatype == 2 && Tables.Lextable.table[i+1].lexema == LEX_PLUS) {
						f << "\n push offset " << Tables.IDtable.table[Tables.Lextable.table[i].idxTI].id;
						f << "\n push offset buffer";
						f << "\n call catlines";
						fl = true;
						break;
					}
					else if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].iddatatype == 2 && (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == 1 || Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == 3)) {
							f << "\n push offset " << Tables.IDtable.table[Tables.Lextable.table[i].idxTI].id;
					}
				}
				if (Tables.Lextable.table[i].lexema == LEX_LITERAL && Tables.Lextable.table[i + 1].lexema != LEX_SEMICOLON /*&& (Tables.Lextable.table[i + 1].lexema != LEX_MINUS && Tables.Lextable.table[i + 2].lexema != LEX_SEMICOLON && Tables.Lextable.table[i - 1].lexema != LEX_EQUAL)*/) {
					f << "\n push " << Tables.IDtable.table[Tables.Lextable.table[i].idxTI].value.vint;
				}
				if (Tables.Lextable.table[i].lexema == LEX_PLUS) {
					f << "\n pop eax \n pop ebx \n add eax, ebx \n push eax \n";
				}
				if (Tables.Lextable.table[i].lexema == LEX_MINUS) {
					if (Tables.Lextable.table[i-1].lexema == LEX_LITERAL && Tables.Lextable.table[i - 2].lexema == LEX_EQUAL && Tables.Lextable.table[i + 1].lexema == LEX_SEMICOLON) {

					}
					else {
						f << "\n pop ebx \n pop eax \n sub eax, ebx \n push eax \n ";
					}
				}
				if (Tables.Lextable.table[i].lexema == LEX_STAR) {
					f << "\n pop eax \n pop ebx \n imul ebx \n push eax \n ";
				}
				if (Tables.Lextable.table[i].lexema == LEX_DIRSLASH) {
					f << "\n pop ebx \n mov edx, 0 \n pop eax \n idiv ebx \n push eax \n ";
				}
				i++;
			}

			if (Tables.Lextable.table[equal + 1].lexema == LEX_ID && Tables.IDtable.table[Tables.Lextable.table[equal + 1].idxTI].idtype == 2) {
				f << "\n call " << Tables.IDtable.table[Tables.Lextable.table[equal + 1].idxTI].id;
			}
			if (Tables.Lextable.table[equal + 1].lexema == LEX_POW) {
				if (Tables.Lextable.table[equal + 3].lexema == LEX_LITERAL) {
					f << "\n push " << Tables.IDtable.table[Tables.Lextable.table[equal+3].idxTI].value.vint;
				}
				f << "\n call pows";
			}
			if (Tables.Lextable.table[equal + 1].lexema == LEX_STRLEN) {
				f << "\n call strlength";
			}
			if (Tables.Lextable.table[equal + 1].lexema == LEX_ABS) {
				f << "\n call absnum";
			}
			if (Tables.Lextable.table[equal + 2].lexema != ';') {
				if(Tables.Lextable.table[equal + 2].lexema == LEX_MINUS && Tables.Lextable.table[equal + 3].lexema == ';'){}
				else {
					f << "\n mov " << Tables.IDtable.table[Tables.Lextable.table[equal - 1].idxTI].id << ", eax";
				}
			}
			break;

		case LEX_FINISH:
			if (isFunction) {
				if (Tables.Lextable.table[i + 1].lexema == LEX_LITERAL) {
					f << "\n mov eax, " << Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].value.vint;
				}
				else {
					f << "\n pop eax";
				}
				f << "\n ret";
			}
			break;
		}
	}
	f << "\nend main";
	f.close();
	return true;
}