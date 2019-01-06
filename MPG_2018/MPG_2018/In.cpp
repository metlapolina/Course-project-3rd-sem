#include "pch.h"
#include "In.h"
#include "Error.h"
#include "Log.h"

int In::StToken::tokensSize = NULL;
int countofL = 0;
namespace In
{
	IN getin(wchar_t Infile[])
	{
		std::ifstream txtfile(Infile);

		if (!txtfile.is_open())
			throw ERROR_THROW(2);

		IN in;
		in.text = new unsigned char[IN_MAX_LEN_TEXT];
		bool literalFlag = false;
		unsigned char readSymbol = IN_CODE_NULL; 

		while ((readSymbol = txtfile.get()) && (!txtfile.eof()))
		{
			if (in.code[readSymbol] == IN::L)
			{
				in.text[in.size++] = readSymbol;
				readSymbol = txtfile.get();
				while (in.code[readSymbol] != IN::L)
				{
					if (in.code[readSymbol] == IN::NS) {
						// не закрыт литерал
						break;
					}
					else {
						in.text[in.size++] = readSymbol;
						readSymbol = txtfile.get();
					}
				}
				in.text[in.size++] = readSymbol;
				continue;
			}

			switch (in.code[readSymbol])
			{
			case IN::NS:
			{
				in.text[in.size++] = readSymbol;
				in.lines++;
				break;
			}
			case IN::SPACE:
			{
				if (in.text[in.size - 1] == IN_CODE_SPACE)
					in.ignor++;
				else
					in.text[in.size++] = readSymbol;
				break;
			}
			case IN::S:
			{
				if (in.text[in.size - 1] == IN_CODE_SPACE)
					in.text[in.size - 1] = readSymbol;
				else
					in.text[in.size++] = readSymbol;
				break;
			}
			case IN::F:
			{
				throw ERROR_THROW_IN(101, in.lines, in.size);
				break;
			}
			case IN::T:
			{
				if (in.code[in.text[in.size - 2]] == IN::S && in.code[in.text[in.size - 1]] == IN::SPACE)
					in.text[in.size - 1] = readSymbol;
				else
					in.text[in.size++] = readSymbol;
				break;
			}
			}
		}

		in.text[in.size] = IN_CODE_NULL;


		return in;
	}

	void addToken(StToken *tokens, char* &buf, int &posbuf, int line)
	{
		buf[posbuf++] = IN_CODE_NULL;	//После занесённого слова выставляем конец строки
		strcpy_s((tokens[StToken::tokensSize].token), posbuf, buf);
		tokens[StToken::tokensSize].line = line;
		StToken::tokensSize++;
		buf[0] = IN_CODE_NULL;
		posbuf = NULL;
	}

	StToken* parsOfToken(StToken *tokens, unsigned char *text, int *code, std::ofstream *stream)
	{
		tokens = new StToken[IN_MAX_LEN_TEXT];
		char *buf = new char[IN_MAX_STRING_CODE];
		int posBuf = NULL;
		bool literalFlag = false;
		int line = NULL;

		for (int i = NULL; text[i] != IN_CODE_NULL; i++)
		{
			if (code[text[i]] == IN::L)
			{
				if (buf[NULL] != IN_CODE_NULL)
					addToken(tokens, buf, posBuf, line);

				buf[posBuf++] = text[i++];

				while (code[text[i]] != IN::L) {
					if (code[text[i]] == IN::NS) {
						throw ERROR_THROW(411);
						break;
					}
					buf[posBuf++] = text[i++];
				}

				buf[posBuf++] = text[i];
				addToken(tokens, buf, posBuf, line);
				continue;
			}

			switch (code[text[i]])
			{
			case IN::NS:
				line++;
			case IN::SPACE:
			{
				if (buf[NULL] != IN_CODE_NULL)
					addToken(tokens, buf, posBuf, line);
				break;
			}
			case IN::S:
			{
				if (buf[NULL] != IN_CODE_NULL)
					addToken(tokens, buf, posBuf, line);

				buf[posBuf++] = text[i];
				addToken(tokens, buf, posBuf, line);
				break;
			}
			default:
			{
				buf[posBuf++] = text[i];
				break;
			}
			}
		}



		return tokens;
	}
}
