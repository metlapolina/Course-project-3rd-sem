#include "pch.h"
#include "LT.h"
#include "Error.h"

namespace LT
{
	Entry::Entry()
	{
		this->lexema = NULL;
		this->sn = NULL;
		this->idxTI = LT_TI_NULLDX;
	}

	Entry::Entry(char lexema, int snn, int idxti)
	{
		this->lexema = lexema;
		this->sn = snn;
		this->idxTI = idxti;
	}

	LexTable Create(int size)
	{
		LexTable lextable;
		if (size <= LT_MAXSIZE)
			lextable.maxsize = size;
		else
			throw ERROR_THROW(200);
		lextable.size = NULL;
		lextable.table = new Entry[size];
		return  lextable;
	}

	void Add(LexTable &lextable, Entry entry)
	{
		lextable.table[lextable.size].idxTI = entry.idxTI;
		lextable.table[lextable.size].lexema = entry.lexema;
		lextable.table[lextable.size].sn = entry.sn;

		if (lextable.size < LT_MAXSIZE)
			lextable.size++;
		else
			throw ERROR_THROW(202);
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
	}
}