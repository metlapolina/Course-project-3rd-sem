#pragma once

#include "pch.h"

#define ID_MAXSIZE	15				//���� ����� �������� ��������������
#define ID_FOR_IT   20              //���� ����� �������� ������������� + �������������� �-��
#define TI_MAXSIZE	256				//���� ����� ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT	0x00000000	//�������� �� ��������� ��� integer
#define TI_STR_DEFAULT	0x00		//�������� �� ��������� ��� string
#define TI_NULLIDX		0xffffffff	//��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255
#define INT_MAXSIZE     65536
#define INT_MINUS_MAXSIZE   -65536

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2 };				//���� ������ ���������������
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };	//���� ���������������: ����������, �������, ��������, 
																				//�������, ����������� �������
	struct Entry
	{
		int	idxfirstLE;									//������ � ������� ������		
		char		id[ID_MAXSIZE];						//�������������, ��������� ��������� �� ID_MAXSIZE
		IDDATATYPE	iddatatype;							//��� ������
		IDTYPE		idtype;								//��� ��������������
		union
		{
			int	vint;            						//�������� integer
			struct
			{
				int len;								//���������� �������� � string
				char str[TI_STR_MAXSIZE - 1];			//������� string
			}vstr;										//�������� string
		}value;											//�������� ��������������
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
	struct IdTable										//��������� ��
	{
		int maxsize;									//������� ��
		int size;										//������� ������ ��
		Entry* table;									//������ ����� ��
	};
	IdTable Create(int size = NULL);					//������� ��
	void Add(IdTable &idtable, Entry entry);			//�������� ������ � ��			
	int IsId(IdTable &idtable,char id[ID_MAXSIZE]);		//������� ������ ������, ���� �������������
	void SetValue(IdTable &idtable, int, char*);		//������ �������� ��������������
	Entry GetEntry(IdTable& idtable, int n);			//�������� ������ ��
	void Delete(IdTable& idtable);						//������� ��
}