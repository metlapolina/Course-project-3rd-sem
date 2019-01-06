#pragma once

#include "pch.h"

#define	LEXEMA_FIXSIZE   1	        //������ �������
#define	LT_MAXSIZE		 4096	    //������������ ���������� ����� � ������� ������
#define	LT_TI_NULLDX	 0xffffffff	//��� �������� ������� ���������������
#define LEX_SEPARATORS	 'S'		// ���������
#define	LEX_ID_TYPE    	 't'		// integer//string
#define	LEX_ID			 'i'		// �������������
#define	LEX_LITERAL		 'l'		// �������
#define	LEX_FUNCTION     'f'		// �������
#define LEX_DECLARE      'd'		// ���������� 
#define	LEX_GO			 'g'		// ������� �������
#define	LEX_FINISH		 'e'		// ������� ��������
#define	LEX_PRINT		 'p'		// ����� �� �����
#define	LEX_SEMICOLON	 ';'		// ���������� ���������
#define	LEX_COMMA		 ','		// ��� ���������� ����������
#define	LEX_LEFTBRACE	 '{'		// �������� �����������
#define	LEX_RIGHTBRACE	 '}'		// �������� �����������
#define	LEX_LEFTHESIS	 '('		// �������� ����� ���������� �-���
#define	LEX_RIGHTHESIS	 ')'		// �������� ����� ���������� �-���
#define	LEX_PLUS		 '+'		// ��������
#define	LEX_MINUS		 '-'		// ���������
#define	LEX_STAR		 '*'		// ���������
#define	LEX_DIRSLASH	 '/'		// �������	
#define	LEX_EQUAL		 '='		// �����
#define	LEX_STRLEN		 'k'		// ����������� �������
#define	LEX_ABS			 'a'	    // ����������� �������
#define	LEX_POW			 'o'	    // ����������� �������
#define	INTEGER			 "integer"	// INTEGER
#define	STRING		     "string"	// STRING
#define	LTRL			 "ltrl"		// �������

namespace LT							//������� ������
{
	struct Entry
	{
		char lexema;					//�������
		int sn;							//����� ������ � �������� ������
		int idxTI;						//������ � ������� ��������������� ��� LT_TI_NULLIDX

		Entry();
		Entry(char lexema, int snn, int idxti = LT_TI_NULLDX);
	};

	struct LexTable						//��������� ��
	{
		int maxsize;					//������� ��
		int size;						//������� ������ ��
		Entry* table;					//������ ����� ��
	};

	LexTable Create(int size);						//������� ��
	void	 Add(LexTable &lextable, Entry entry);	//�������� ������ � ��
	Entry	 GetEntry(LexTable& lextable, int n);	//�������� ������ ��
	void	 Delete(LexTable& lextable);			//������� ��
}