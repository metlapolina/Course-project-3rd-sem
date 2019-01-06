#pragma once

#define IN_MAX_LEN_TEXT 1024*1024	//������������ ������ ��������� ���� 1 ��
#define IN_MAX_STRING_CODE 1024
#define IN_CODE_ENDL '\n'			//������ ����� ������
#define IN_CODE_SPACE ' '
#define IN_CODE_NULL '\0'

#define IN_CODE_TABLE {\
	IN::T,     IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,   IN::F,   IN::NS,   IN::F,   IN::F,   IN::F,   IN::F, IN::F,\
	IN::F,     IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,   IN::F,   IN::F,    IN::F,   IN::F,   IN::F,   IN::F, IN::F,\
	IN::SPACE, IN::T, IN::T, IN::F, IN::F, IN::T, IN::F, IN::L, IN::S,	 IN::S,   IN::S,    IN::S,   IN::S,   IN::S,   IN::T, IN::S,\
	IN::T,     IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::S,   IN::F,   IN::S,   IN::F, IN::T,\
	IN::F,     IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::T,   IN::T,   IN::T,   IN::T, IN::T,\
	IN::T,     IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::T,   IN::F,   IN::T,   IN::F, IN::F,\
	IN::F,     IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::T,   IN::T,   IN::T,   IN::T, IN::T,\
	IN::T,     IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,   IN::T,   IN::T,    IN::S,   IN::F,	  IN::S,   IN::F, IN::F,\
\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F\
}  

namespace In
{
	struct StToken
	{
		static int tokensSize;  // ���������� ����
		int  line; // ������ � ������� ��������� �����
		char token[IN_MAX_STRING_CODE];
	};

	struct IN
	{
		/*
		S - ( ) * + - = , / { } ;
		SPACE - ������
		NS - ����� ������
		F - �����������
		T - �����������
		L - '
		*/
		enum { T = 1, F, NS, S, L, SPACE };
		int code[256] = IN_CODE_TABLE;//������� ��������
		int size = NULL;//������ ��������� ����
		int lines = NULL;//���-�� �����
		int ignor = NULL;//���-�� ����� ��������	
		unsigned char *text;//�������� ���
		StToken *tokens;
	};

	IN getin(wchar_t Infile[]);//������ � ��������� ������� �����
	StToken* parsOfToken(StToken *tokens, unsigned char *text, int *code, std::ofstream *stream);
	void addToken(StToken *tokens, char* &buffer, int &posbuf, int line);
}