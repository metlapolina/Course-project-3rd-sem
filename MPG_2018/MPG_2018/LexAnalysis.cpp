#include "pch.h"
#include "Graphs.h"
#include "FST.h"
#include "LexAnalysis.h"
#include "Error.h"

char templiteral[5] = "ltrl";
int forltrl = 0;

namespace Lexer
{        
	Graph graph[N_GRAPHS] =					// графы переходов в массиве
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
	char tempTokenFunction[ID_FOR_IT] = "";// массив для имен переменных

	LEX Run(In::IN &InStruct, Log::LOG &log, Parm::PARM &parm)
	{
		LEX Tables;
		Tables.Lextable = LT::Create(LT_MAXSIZE);
		Tables.IDtable = IT::Create(TI_MAXSIZE);
		Tables.isLex = true;
		bool isParam = false;			//устанавливаем флаг параметров
		int funcBody = NULL;			// определение кол-ва GO function
		IT::IDDATATYPE funcType;		// тип функции
		IT::IDDATATYPE idType;			// тип переменной

		for (int i = 0; i < In::StToken::tokensSize; i++)         // проходимся до конца in файла по фразам
		{
			for (int j = 0; j < N_GRAPHS; j++)
			{
				FST::FST fstex(InStruct.tokens[i].token, graph[j].graph);
				if (FST::execute(fstex))
				{
					switch (graph[j].lexema)    // проходимся по встречаемой лексеме
					{
					case LEX_GO:   // главная функция
					{
						funcBody++; 
						funcType = graph[j].graph.type;			// определяем тип функции
						strncpy_s(tempTokenFunction, "", 1);	// копируем первую букву имени функции
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);  // заносим ее в структуру ТЛ
						LT::Add(Tables.Lextable, entrylt);		// добавляем в ТЛ
						break;
					}
					case LEX_ID:      // идентификатор
					{
						strncpy_s(tempToken, InStruct.tokens[i].token, ID_MAXSIZE - 1);    // копируем имя в буфер 10 символов
						strncpy_s(InStruct.tokens[i].token, InStruct.tokens[i].token, ID_FOR_IT - 1);
						strcat_s(InStruct.tokens[i].token, tempTokenFunction);  // добавляем к переменной имя функции

						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token) == -1) // если нет в ТИ
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // если это функция
							{
								strncpy_s(InStruct.tokens[i].token, InStruct.tokens[i].token, ID_MAXSIZE - 1);
								strncpy_s(tempTokenFunction, InStruct.tokens[i].token, ID_FOR_IT - 1);  // копируем усеченную длину функции
								funcType = idType;  // устанавливаем тип данных
								IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::F); // добавляем в ИТ
								IT::Add(Tables.IDtable, entryit);
								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token)); // заносим в ЛТ
								LT::Add(Tables.Lextable, entrylt);
								isParam = true;  // есть параметры
								break;
							}
							else if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE)  // тип данных
							{
								if (isParam == false) // если параметров нет
								{

									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::V);
									IT::Add(Tables.IDtable, entryit); // добавляем тип в ИТ
								}
								else if (isParam == true)   // если передаются параметры
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, idType, IT::P);
									IT::Add(Tables.IDtable, entryit); // добавляем в ИТ параметр
									if (InStruct.tokens[i + 1].token[0] == LEX_RIGHTHESIS)
										isParam = false; // конец блока параметров
								}
								LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token));
								LT::Add(Tables.Lextable, entrylt);  // заносим в ЛТ
								break;
							}
							throw ERROR_THROW_IN(406, InStruct.tokens[i].line, NULL);
							Tables.isLex = false;
							break;
						}
						else // есть в ТИ
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_ID_TYPE || Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION) // кидаем 407 ошибку
							{
								throw ERROR_THROW_IN(407, InStruct.tokens[i].line, NULL);
								Tables.isLex = false;
							}
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token));
							LT::Add(Tables.Lextable, entrylt); // Добавляем в ЛТ
							break;
						}
						break;
					}
					case LEX_LITERAL: // если это литерал
					{
						switch (Tables.Lextable.table[i - 1].lexema) // смотрим предыдущую лексему
						{
						case LEX_EQUAL: // равно
						{
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
							LT::Add(Tables.Lextable, entrylt); // пишем в ЛТ
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::F) {
								throw ERROR_THROW_IN(402, InStruct.tokens[i].line, NULL);
								Tables.isLex = false;
							}
							if (Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::V ||
								Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::P)	// если арифм. знак 
								IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token), InStruct.tokens[i].token); // уст знач для идент - 2
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
							IT::Add(Tables.IDtable, entryit); // добавляем в ИТ
							IT::SetValue(Tables.IDtable, Tables.IDtable.size - 1, InStruct.tokens[i].token);
							LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
							LT::Add(Tables.Lextable, entrylt); // добавляем в ЛТ
							ind[4] = '\0';
							break;
						}
						default:
							throw ERROR_THROW_IN(408, InStruct.tokens[i].line, NULL);
							Tables.isLex = false;
						}
						break;
					}
					case LEX_SEPARATORS: // сепаратор
					{
						switch (InStruct.tokens[i].token[0])
						{
						case LEX_SEMICOLON: // ;
						{
							if (Tables.Lextable.table[i - 2].lexema == LEX_FINISH) // если сепаратор-2 стоял finish
							{
								IT::IDDATATYPE retType;
								retType = IT::IDDATATYPE::INT;
								if (Tables.Lextable.table[i - 1].lexema == LEX_LITERAL) // а сеп-1 литерал
									retType = Tables.IDtable.table[Tables.IDtable.size - 1].iddatatype; // присвоить возвр типу тип данных литерала

								else {
									if (IT::IsId(Tables.IDtable, InStruct.tokens[i - 1].token) == -1) {
										throw ERROR_THROW_IN(403, InStruct.tokens[i].line, NULL);
									}
									else {
										retType = Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 1].token)].iddatatype; //присв тип в ИТ-1 
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
							LT::Add(Tables.Lextable, entrylt); // добавить в ЛТ
						}
						}
						break;
					}
					case LEX_ID_TYPE:
						idType = graph[j].graph.type; // присв тип данных как у сраб. графа
					default:
					{
						LT::Entry entrylt(graph[j].lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt); // кидаем в ЛТ
						break;
					}
					}
					break;
				}
			}
		}

		if (!funcBody) // если не обнаружили главную функцию
		{
			throw ERROR_THROW(400);
			Tables.isLex = false;
		}

		return Tables;
	}
}