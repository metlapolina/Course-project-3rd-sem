#include "pch.h"
#include "Graphs.h"
#include "FST.h"
#include "LexAnalysis.h"
#include "Error.h"

char templiteral[5] = "ltrl";
int forltrl = 0;

namespace Lexer
{        
	Graph graph[N_GRAPHS] =					// ����� ��������� � �������
	{
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL) },
		{ LEX_SEPARATORS, FST::FST(GRAPH_SEPARATORS) },
		{ LEX_DECLARE, FST::FST(GRAPH_DECLARE) },
		{ LEX_STRLEN, FST::FST(GRAPH_STRLEN) },
		{ LEX_ABS, FST::FST(GRAPH_ABS) },
		{ LEX_POW, FST::FST(GRAPH_POW) },
		{ LEX_LITERAL, FST::FST(GRAPH_STRING_LITERAL) },
		{ LEX_GO, FST::FST(GRAPH_GO) },
		{ LEX_ID_TYPE, FST::FST(GRAPH_INTEGER) },
		{ LEX_ID_TYPE, FST::FST(GRAPH_STRING) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_FINISH, FST::FST(GRAPH_FINISH) },
		{ LEX_PRINT, FST::FST(GRAPH_PRINT) },
		{ LEX_ID, FST::FST(GRAPH_ID) } 
	};

	char tempToken[ID_MAXSIZE] = "";
	char tempTokenFunction[ID_FOR_IT] = "";// ������ ��� ���� ����������

	LEX Run(In::IN &InStruct, Log::LOG &log, Parm::PARM &parm)
	{
		LEX Tables;
		Tables.Lextable = LT::Create(LT_MAXSIZE);
		Tables.IDtable = IT::Create(TI_MAXSIZE);
		Tables.isLex = true;
		bool isParam = false;			//������������� ���� ����������
		int funcBody = NULL;			// ����������� ���-�� GO function
		IT::IDDATATYPE funcType;		// ��� �������
		IT::IDDATATYPE idType;			// ��� ����������

		for (int i = 0; i < In::StToken::tokensSize; i++)         // ���������� �� ����� in ����� �� ������
		{
			for (int j = 0; j < N_GRAPHS; j++)
			{
				FST::FST fstex(InStruct.tokens[i].token, graph[j].graph);
				if (FST::execute(fstex))
				{
					switch (graph[j].lexema)    // ���������� �� ����������� �������
					{
					case LEX_GO:   // ������� �������
					{
						funcBody++; 
						funcType = graph[j].graph.type;			// ���������� ��� �������
						strncpy_s(tempTokenFunction, "", 1);	// �������� ������ ����� ����� �������
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);  // ������� �� � ��������� ��
						LT::Add(Tables.Lextable, entrylt);		// ��������� � ��
						break;
					}
					case LEX_ID:      // �������������
					{
						strncpy_s(tempToken, InStruct.tokens[i].token, ID_MAXSIZE - 1);    // �������� ��� � ����� 10 ��������
						strncpy_s(InStruct.tokens[i].token, InStruct.tokens[i].token, ID_FOR_IT - 1);
						strcat_s(InStruct.tokens[i].token, tempTokenFunction);  // ��������� � ���������� ��� �������

						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token) == -1) // ���� ��� � ��
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // ���� ��� �������
							{
								strncpy_s(InStruct.tokens[i].token, InStruct.tokens[i].token, ID_MAXSIZE - 1);
								strncpy_s(tempTokenFunction, InStruct.tokens[i].token, ID_FOR_IT - 1);  // �������� ��������� ����� �������
								funcType = idType;  // ������������� ��� ������
								IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::F); // ��������� � ��
								IT::Add(Tables.IDtable, entryit);
								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // ������� � ��
								LT::Add(Tables.Lextable, entrylt);
								isParam = true;  // ���� ���������
								break;
							}
							else if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE)  // ��� ������
							{
								if (isParam == false) // ���� ���������� ���
								{

									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::V);
									IT::Add(Tables.IDtable, entryit); // ��������� ��� � ��
								}
								else if (isParam == true)   // ���� ���������� ���������
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::P);
									IT::Add(Tables.IDtable, entryit); // ��������� � �� ��������
									if (InStruct.tokens[i + 1].token[0] == LEX_RIGHTHESIS)
										isParam = false; // ����� ����� ����������
								}
								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token));
								LT::Add(Tables.Lextable, entrylt);  // ������� � ��
								break;
							}
							throw ERROR_THROW_IN(406, InStruct.tokens[i].line, NULL);
							Tables.isLex = false;
							break;
						}
						else // ���� � ��
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE || Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // ������ 407 ������
							{
								throw ERROR_THROW_IN(407, InStruct.tokens[i].line, NULL);
								Tables.isLex = false;
							}
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token));
							LT::Add(Tables.Lextable, entrylt); // ��������� � ��
							break;
						}
						break;
					}
					case LEX_LITERAL: // ���� ��� �������
					{
						switch (Tables.Lextable.table[i - 1].lexema) // ������� ���������� �������
						{
						case LEX_EQUAL: // �����
						{
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
							LT::Add(Tables.Lextable, entrylt); // ����� � ��
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::F) {
								throw ERROR_THROW_IN(402, InStruct.tokens[i].line, NULL);
								Tables.isLex = false;
							}
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::V ||
								Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::P)	// ���� �����. ���� 
								IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token), InStruct.tokens[i].token); // ��� ���� ��� ����� - 2
							break;
						}
						case LEX_LEFTHESIS:
						case LEX_COMMA:
						case LEX_PRINT:
						case LEX_FINISH:
						case LEX_PLUS:
						case LEX_MINUS:
						case LEX_STAR:
						case LEX_DIRSLASH:
						{
							char* ind = templiteral;
							strcat(ind, std::to_string(forltrl).c_str());
							forltrl++;

							IT::Entry entryit(ind, i, graph[j].graph.type, IT::L);
							IT::Add(Tables.IDtable, entryit); // ��������� � ��
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.tokens[i].token);
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
							LT::Add(Tables.Lextable, entrylt); // ��������� � ��
							ind[4] = '\0';
							break;
						}
						default:
							throw ERROR_THROW_IN(408, InStruct.tokens[i].line, NULL);
							Tables.isLex = false;
						}
						break;
					}
					case LEX_SEPARATORS: // ���������
					{
						switch (InStruct.tokens[i].token[0])
						{
						case LEX_SEMICOLON: // ;
						{
							if (Tables.Lextable.table[i - 2].lexema == LEX_FINISH) // ���� ���������-2 ����� finish
							{
								IT::IDDATATYPE retType;
								retType = IT::IDDATATYPE::INT;
								if (Tables.Lextable.table[i - 1].lexema == LEX_LITERAL) // � ���-1 �������
									retType = Tables.IDtable.table[Tables.IDtable.size - 1].iddatatype; // ��������� ����� ���� ��� ������ ��������

								else {
									if (IT::IsId(Tables.IDtable, InStruct.tokens[i - 1].token) == -1) {
										throw ERROR_THROW_IN(403, InStruct.tokens[i].line, NULL);
									}
									else {
										retType = Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 1].token)].iddatatype; //����� ��� � ��-1 
									}
								}
								if (funcType != retType) {
									throw ERROR_THROW_IN(405, InStruct.tokens[i].line, NULL);
									Tables.isLex = false;
								}
							}
						}
						default:
						{
							LT::Entry entrylt(InStruct.tokens[i].token[0], InStruct.tokens[i].line);
							LT::Add(Tables.Lextable, entrylt); // �������� � ��
						}
						}
						break;
					}
					case LEX_ID_TYPE:
						idType = graph[j].graph.type; // ����� ��� ������ ��� � ����. �����
					default:
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt); // ������ � ��
						break;
					}
					}
					break;
				}
			}
		}

		if (!funcBody) // ���� �� ���������� ������� �������
		{
			throw ERROR_THROW(400);
			Tables.isLex = false;
		}

		return Tables;
	}
}