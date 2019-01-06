#include "pch.h"
#include "In.h"
#include "LexAnalysis.h"
#include "Log.h"
#include "Error.h"
#include "Parm.h"
#include "IT.h"
#include "GRB.h"
#include "MFST.h"
#include "LT.h"
#include "FST.h"
#include "PN.h"
#include "Generation.h"
#include "SemAnalysis.h"

int _tmain(int argc, wchar_t *argv[])
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log;
	bool isPN = false;
	bool isSyntax = false;
	bool isSemantic = false;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getstream(parm.log);
		Log::writeLog(log);
		Log::writeParm(log, parm);
		In::IN in = In::getin(parm.in);
		in.tokens = In::parsOfToken(in.tokens, in.text, in.code, log.stream);
		Lexer::LEX tables = Lexer::Run(in, log, parm);
		if (Log::Eror)
		{
			Log::writeIn(log, in);
			Log::writeLexTable(tables.Lextable, "LTable.txt");
			std::cout << "Таблица лексем построена!" << std::endl;
			Log::writeIDtable(tables.IDtable, "ITable.txt");
			std::cout << std::endl << "Таблица идентификаторов построена!" << std::endl;
			Log::writeIntermediateCode(log, tables.Lextable);
			isSemantic = Semantic::SemanticAnaliz(tables, in);
			if (isSemantic) {
				
				MFST::Mfst mfst(tables, GRB::getGreibach());
				isSyntax = mfst.start();
				mfst.savededucation();
				mfst.printrules();
				if (isSyntax) {
					std::cout << std::endl << "Синтаксический анализ произведен!" << std::endl;
				}
				else {
					std::cout << std::endl << "Синтаксический анализ не произведен!" << std::endl;
					return 0;
				}
				PN polishNatation;
				if (polishNatation.searchExpression(tables)) 
				{
					std::cout << std::endl << "Польская запись построена!" << std::endl;
					isPN = true;
				}
				else {
					std::cout << std::endl << "Польская запись не построена!" << std::endl;
					isPN = false;
				}
				Log::writeIntermediateCode(log, tables.Lextable, "PN.txt");
			}
		}

		if (tables.isLex && isPN && isSyntax && isSemantic) {
			isGenerated(tables);
			std::cout << std::endl << "Генерация произведена!" << std::endl;
		}
		else {
			std::cout << std::endl << "Генерация не произведена!" << std::endl;
		}

	}
	catch (Error::ERROR e)
	{
		Log::writeError(log.stream, e);
		system("cls");
		std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
		if (e.position.line != -1) {
			std::cout << "Строка " << e.position.line + 1;
		}
		if (e.position.cells != -1) {
			std::cout << " позиция " << e.position.cells + 1 << std::endl << std::endl;
		}
		return 0;
	}
	system("notepad in.txt");
	system("notepad in.txt.log");
	system("notepad LTable.txt");
	system("notepad ITable.txt");
	system("notepad MFST.txt");
	system("notepad PN.txt");
}
