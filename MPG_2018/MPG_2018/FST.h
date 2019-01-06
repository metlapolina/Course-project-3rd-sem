#pragma once
#include "pch.h"
#include "IT.h"

namespace FST
{
	struct RELATION				// ребро:символ -> вершина графа переходов КА
	{
		char symbol;			// символ перехода
		short nnode;			// номер смежной вершины
		RELATION(
			char c = 0x00,		// символ перехода
			short ns = NULL		// новое состояние
		);
	};

	struct NODE					// вершина графа переходов
	{
		short n_relation;		// количество инцидентных ребер
		RELATION *relations;	// инцидентные ребра
		NODE();
		NODE(
			short n,			// количество инцидентных ребер
			RELATION rel, ...	// список ребер
		);
	};

	struct FST					// недетерминированный конечный автомат
	{
		IT::IDDATATYPE type;
		char* string;			// цепочка(строка, завершается 0х00)
		short position;			// текущая позиция в цепочке
		short nstates;			// количество состояний автомата
		NODE* nodes;			// граф переходов : [0] - начальное состояние, [nstate-1] - конечное
		short* rstates;			// возможные состояния автомата на данной позиции
		FST(short ns, NODE n, ...);		// для массива, количество состояний автомата, список состояний(граф переходов)
		FST(char* s, FST& fst); // цепочка и константный FST
		FST(IT::IDDATATYPE type, short ns, NODE n, ...);
	};

	bool execute(				// выполнить распознание цепочки
		FST& fst				// недетерминированный КА
	);
}