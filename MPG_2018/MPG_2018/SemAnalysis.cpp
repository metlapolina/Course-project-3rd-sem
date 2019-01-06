#pragma once
#include "pch.h"
#include "SemAnalysis.h"
							
bool Semantic::SemanticAnaliz(Lexer::LEX Tables, In::IN InStruct) {
	bool isSemantic = true;
	int funcBody = 0;
	int countL = 0;
	for (int i = 0; i < Tables.Lextable.size; i++) {
		switch (Tables.Lextable.table[i].lexema) {
			case LEX_DIRSLASH:
			{
				if (Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].value.vint == 0) {
					throw ERROR_THROW_IN(412, Tables.Lextable.table[i].sn, NULL);
					isSemantic = false;
				}
				break;
			}
			case LEX_PLUS:
			case LEX_MINUS:
			case LEX_STAR:
			{
				if (Tables.Lextable.table[i - 1].lexema == LEX_ID && Tables.Lextable.table[i + 1].lexema == LEX_LITERAL && Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].iddatatype == 2) {
					if (Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype != Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].iddatatype) {
						throw ERROR_THROW_IN(410, Tables.Lextable.table[i].sn, NULL);
						isSemantic = false;
					}
				}
				break;
			}
			case LEX_GO:						//проверка на единственность главной функции
			{
				funcBody++;						//считаем кол-во главных функций
				if (funcBody > 1)				
				{
					throw ERROR_THROW_IN(401, InStruct.tokens[i].line, NULL); //Обнаружена вторая главная функция
					isSemantic = false;
				}
				break;
			}
			case LEX_EQUAL:
			{
				//проверка типов ид при присваивании
				if (Tables.Lextable.table[i - 1].lexema == LEX_ID && Tables.Lextable.table[i + 1].lexema == LEX_ID) {
					if (Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype != Tables.IDtable.table[Tables.Lextable.table[i + 1].idxTI].iddatatype)
					{
						throw ERROR_THROW_IN(410, InStruct.tokens[i].line, NULL); //Несоответствие типов
						isSemantic = false;
					}
				}
				//проверка на правильную инициализацию
				if (Tables.Lextable.table[i - 1].lexema == LEX_ID && Tables.Lextable.table[i + 2].lexema == LEX_SEMICOLON) {
					if (Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype == IT::IDDATATYPE::INT) {
						if (InStruct.tokens[i + 1].token[0] == (char)39) {
							throw ERROR_THROW_IN(409, InStruct.tokens[i].line, NULL); //Ошибка инициализации
							isSemantic = false;
						}
					}
					if (Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype == IT::IDDATATYPE::STR) {
						if (InStruct.tokens[i + 1].token[0] != (char)39) {
							throw ERROR_THROW_IN(409, InStruct.tokens[i].line, NULL); //Ошибка инициализации
							isSemantic = false;
						}
					}
				} 
				//несоответствие типов в составных выражениях
				if (Tables.Lextable.table[i - 1].lexema == LEX_ID && Tables.Lextable.table[i + 2].lexema != LEX_SEMICOLON && Tables.Lextable.table[i + 1].lexema != LEX_STRLEN) {
					if (Tables.IDtable.table[Tables.Lextable.table[i - 1].idxTI].iddatatype == IT::IDDATATYPE::INT) {
						int k = i;
						while (Tables.Lextable.table[k].lexema != LEX_SEMICOLON) {
							if (Tables.Lextable.table[k].lexema == LEX_ID && Tables.IDtable.table[Tables.Lextable.table[k].idxTI].iddatatype != IT::IDDATATYPE::INT) {
								throw ERROR_THROW_IN(410, InStruct.tokens[i].line, NULL); //Несоответствие типов
								isSemantic = false;
							}
							k++;
						}
					}
				}
				break;
			}
			case LEX_ID:
			{
				if (Tables.IDtable.table[Tables.Lextable.table[i].idxTI].idtype == IT::F)
				{
					int kol2 = 0;
					int a = Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i].token)].idxfirstLE;
					while (Tables.Lextable.table[a].lexema != LEX_RIGHTHESIS)
					{
						if (Tables.Lextable.table[a].lexema == LEX_COMMA)
							kol2++;
						a++;
					}
					int kol = 0;
					while (Tables.Lextable.table[i].lexema != LEX_RIGHTHESIS)
					{
						if (Tables.Lextable.table[i].lexema == LEX_COMMA)
							kol++;
						i++;
					}
					if (kol != kol2)
					{
						throw ERROR_THROW_IN(404, Tables.Lextable.table[i].sn, NULL); //Неверное количество параметров функции
						isSemantic = false;
					}
				}
				break;
			}
		}
	}
	return isSemantic;
}