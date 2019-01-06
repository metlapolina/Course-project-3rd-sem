#pragma once
#include "pch.h"
#include "IT.h"

namespace FST
{
	struct RELATION				// �����:������ -> ������� ����� ��������� ��
	{
		char symbol;			// ������ ��������
		short nnode;			// ����� ������� �������
		RELATION(
			char c = 0x00,		// ������ ��������
			short ns = NULL		// ����� ���������
		);
	};

	struct NODE					// ������� ����� ���������
	{
		short n_relation;		// ���������� ����������� �����
		RELATION *relations;	// ����������� �����
		NODE();
		NODE(
			short n,			// ���������� ����������� �����
			RELATION rel, ...	// ������ �����
		);
	};

	struct FST					// ������������������� �������� �������
	{
		IT::IDDATATYPE type;
		char* string;			// �������(������, ����������� 0�00)
		short position;			// ������� ������� � �������
		short nstates;			// ���������� ��������� ��������
		NODE* nodes;			// ���� ��������� : [0] - ��������� ���������, [nstate-1] - ��������
		short* rstates;			// ��������� ��������� �������� �� ������ �������
		FST(short ns, NODE n, ...);		// ��� �������, ���������� ��������� ��������, ������ ���������(���� ���������)
		FST(char* s, FST& fst); // ������� � ����������� FST
		FST(IT::IDDATATYPE type, short ns, NODE n, ...);
	};

	bool execute(				// ��������� ����������� �������
		FST& fst				// ������������������� ��
	);
}