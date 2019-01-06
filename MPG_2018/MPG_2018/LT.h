#pragma once

#include "pch.h"

#define	LEXEMA_FIXSIZE   1	        //размер лексемы
#define	LT_MAXSIZE		 4096	    //максимальное количество строк в таблице лексем
#define	LT_TI_NULLDX	 0xffffffff	//нет элемента таблицы идентификаторов
#define LEX_SEPARATORS	 'S'		// сепаратор
#define	LEX_ID_TYPE    	 't'		// integer//string
#define	LEX_ID			 'i'		// идентификатор
#define	LEX_LITERAL		 'l'		// литерал
#define	LEX_FUNCTION     'f'		// функция
#define LEX_DECLARE      'd'		// объявление 
#define	LEX_GO			 'g'		// главная функция
#define	LEX_FINISH		 'e'		// возврат значения
#define	LEX_PRINT		 'p'		// вывод на экран
#define	LEX_SEMICOLON	 ';'		// разделение выражений
#define	LEX_COMMA		 ','		// для разделения параметров
#define	LEX_LEFTBRACE	 '{'		// открытие конструкции
#define	LEX_RIGHTBRACE	 '}'		// закрытие конструкции
#define	LEX_LEFTHESIS	 '('		// открытие блока параметров ф-ции
#define	LEX_RIGHTHESIS	 ')'		// закрытие блока параметров ф-ции
#define	LEX_PLUS		 '+'		// сложение
#define	LEX_MINUS		 '-'		// вычитание
#define	LEX_STAR		 '*'		// умножение
#define	LEX_DIRSLASH	 '/'		// деление	
#define	LEX_EQUAL		 '='		// равно
#define	LEX_STRLEN		 'k'		// стандартная функция
#define	LEX_ABS			 'a'	    // стандартная функция
#define	LEX_POW			 'o'	    // стандартная функция
#define	INTEGER			 "integer"	// INTEGER
#define	STRING		     "string"	// STRING
#define	LTRL			 "ltrl"		// литерал

namespace LT							//таблица лексем
{
	struct Entry
	{
		char lexema;					//лексема
		int sn;							//номер строки в исходном тексте
		int idxTI;						//индекс в таблице идентификаторов или LT_TI_NULLIDX

		Entry();
		Entry(char lexema, int snn, int idxti = LT_TI_NULLDX);
	};

	struct LexTable						//экземпляр ТЛ
	{
		int maxsize;					//емкость ТЛ
		int size;						//текущий размер ТЛ
		Entry* table;					//массив строк ТЛ
	};

	LexTable Create(int size);						//создать ТЛ
	void	 Add(LexTable &lextable, Entry entry);	//добавить строку в ТЛ
	Entry	 GetEntry(LexTable& lextable, int n);	//получить строку ТЛ
	void	 Delete(LexTable& lextable);			//удалить ТЛ
}