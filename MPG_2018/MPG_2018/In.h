#pragma once

#define IN_MAX_LEN_TEXT 1024*1024	//максимальный размер исходного кода 1 МБ
#define IN_MAX_STRING_CODE 1024
#define IN_CODE_ENDL '\n'			//символ конца строки
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
		static int tokensSize;  // Количество фраз
		int  line; // строка в которой находится фраза
		char token[IN_MAX_STRING_CODE];
	};

	struct IN
	{
		/*
		S - ( ) * + - = , / { } ;
		SPACE - пробел
		NS - новая строка
		F - запрещённый
		T - разрешённый
		L - '
		*/
		enum { T = 1, F, NS, S, L, SPACE };
		int code[256] = IN_CODE_TABLE;//таблица проверки
		int size = NULL;//размер исходного кода
		int lines = NULL;//кол-во строк
		int ignor = NULL;//кол-во игнор символов	
		unsigned char *text;//исходный код
		StToken *tokens;
	};

	IN getin(wchar_t Infile[]);//ввести и проверить входной поток
	StToken* parsOfToken(StToken *tokens, unsigned char *text, int *code, std::ofstream *stream);
	void addToken(StToken *tokens, char* &buffer, int &posbuf, int line);
}