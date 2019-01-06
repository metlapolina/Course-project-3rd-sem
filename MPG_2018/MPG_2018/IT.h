#pragma once

#include "pch.h"

#define ID_MAXSIZE	15				//макс число символов идентификатора
#define ID_FOR_IT   20              //макс число символов идентификатор + принадлежность ф-ии
#define TI_MAXSIZE	256				//макс число количество строк в таблице идентификаторов
#define TI_INT_DEFAULT	0x00000000	//значение по умолчанию для integer
#define TI_STR_DEFAULT	0x00		//значение по умолчанию для string
#define TI_NULLIDX		0xffffffff	//нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255
#define INT_MAXSIZE     65536
#define INT_MINUS_MAXSIZE   -65536

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2 };				//типы данных идентификаторов
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };	//типы идентификаторов: переменная, функция, параметр, 
																				//литерал, стандартная функция
	struct Entry
	{
		int	idxfirstLE;									//индекс в таблице лексем		
		char		id[ID_MAXSIZE];						//идентификатор, автоматом усекается до ID_MAXSIZE
		IDDATATYPE	iddatatype;							//тип данных
		IDTYPE		idtype;								//тип идентификатора
		union
		{
			int	vint;            						//значение integer
			struct
			{
				int len;								//количество символов в string
				char str[TI_STR_MAXSIZE - 1];			//символы string
			}vstr;										//значение string
		}value;											//значение идентификатора
		Entry()
		{
			this->value.vint = TI_INT_DEFAULT;
			this->value.vstr.len = NULL;
		};
		Entry(char* id, int idxLT, IDDATATYPE datatype, IDTYPE idtype)
		{
			strncpy_s(this->id, id, ID_FOR_IT - 1);
			this->idxfirstLE = idxLT;
			this->iddatatype = datatype;
			this->idtype = idtype;
		};
	};
	struct IdTable										//экземпляр ТИ
	{
		int maxsize;									//емкость ТИ
		int size;										//текущий размер ТИ
		Entry* table;									//массив строк ТИ
	};
	IdTable Create(int size = NULL);					//создать ТИ
	void Add(IdTable &idtable, Entry entry);			//добавить строку в ТИ			
	int IsId(IdTable &idtable,char id[ID_MAXSIZE]);		//возврат номера строки, если идентификатор
	void SetValue(IdTable &idtable, int, char*);		//задать значение идентификатора
	Entry GetEntry(IdTable& idtable, int n);			//получить строку ТИ
	void Delete(IdTable& idtable);						//удалить ТИ
}