#include "pch.h"
#include "IT.h"
#include "Error.h"
#include "In.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(201);
		}
		IdTable idtable;
		idtable.table = new Entry[size];
		idtable.size = NULL;
		idtable.maxsize = size;
		return idtable;
	}

	void Add(IdTable &idtable, Entry entry)
	{
		if (idtable.size >= idtable.maxsize)
		{
			throw ERROR_THROW(203);
		}
		strncpy_s(idtable.table[idtable.size].id, entry.id, ID_FOR_IT - 1); // 10 символов на идентификатор + 5 символов на принадлежность к ф-ии
		idtable.table[idtable.size].idxfirstLE = entry.idxfirstLE; // местонахождение в таблице лексем(первое упоминание)
		idtable.table[idtable.size].iddatatype = entry.iddatatype; // тип данных integer ...
		idtable.table[idtable.size].idtype = entry.idtype; // функции переменная ...
		idtable.table[idtable.size].value.vint = TI_INT_DEFAULT; // значение по ум-ию для int
		idtable.table[idtable.size].value.vstr.len = NULL; // длина строки 0
		idtable.table[idtable.size].value.vstr.str[0] = TI_STR_DEFAULT; // пустая строка
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable &idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == NULL)
				return i;
		}
		return TI_NULLIDX;
	}

	void SetValue(IdTable &idtable, int indTI, char* token) // установка значения переменной
	{
		if (idtable.table[indTI].iddatatype == INT)
		{
			int tempInt = atoi(token);
			if (tempInt > INT_MAXSIZE) {
				throw ERROR_THROW(204);
			}
			else if (tempInt < INT_MINUS_MAXSIZE) {
				tempInt = INT_MINUS_MAXSIZE;
			}
			idtable.table[indTI].value.vint = tempInt;
		}
		else
		{
			idtable.table[indTI].value.vstr.len = strlen(token);
			if (strlen(token) > TI_STR_MAXSIZE) {
				throw ERROR_THROW(205);
			}
			else {
				strcpy_s(idtable.table[indTI].value.vstr.str, TI_STR_MAXSIZE, token);
			}
		}
	}
	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
	}
}