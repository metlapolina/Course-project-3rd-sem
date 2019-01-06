#include "pch.h"
#include "Log.h"
#include "Error.h"
#include "In.h"
#include "IT.h"
#include "LT.h"



namespace Log
{

	LOG getstream(wchar_t  logfile[])
	{
		LOG stream;
		stream.stream = new std::ofstream;
		(*stream.stream).open(logfile);
		if (!(*stream.stream).is_open())
			throw ERROR_THROW(3);
		wcscpy_s(stream.logfile, logfile);
		return stream;
	}

	void writeLog(LOG &log) {
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		const char* format = "%d.%m.%Y %H:%M:%S";		
		strftime(buffer, 80, format, timeinfo);
		*log.stream << "----- Протокол ------ Дата: " << buffer << " --- \n\n";
	}

	void writeParm(LOG &log, Parm::PARM &parm)
	{
		char inTxt[PARM_MAX_SIZE],
			logTxt[PARM_MAX_SIZE];
		wcstombs(inTxt, parm.in, wcslen(parm.in) + 1);
		wcstombs(logTxt, parm.log, wcslen(parm.log) + 1);
		*log.stream << "\n----- Параметры --------";
		*log.stream << "\n-in: " << inTxt
			<< "\n-log: " << logTxt << "\n\n";
	}

	void writeIn(LOG &log, In::IN &in) {
		*log.stream << "\n---- Исходные данные ------";
		*log.stream << "\nКоличество символов: " << std::setw(3) << in.size
			<< "\nПроигнорировано: " << std::setw(3) << in.ignor
			<< "\nКоличество строк: " << std::setw(3) << in.lines << "\n\n";
	}

	void writeError(std::ofstream *stream, Error::ERROR &e)
	{
		Eror = false;

		if (stream == NULL)  // Пустой указатель
		{
			if (e.position.cells == -1 || e.position.line == -1)
				std::cout << std::endl << "Ошибка " << e.id << ": " << e.message << std::endl;
			else if (e.position.cells == NULL)
				std::cout << std::endl << "Ошибка " << e.id << ": " << e.message
				<< "\nСтрока " << e.position.line << std::endl;
			else
				std::cout << std::endl << "Ошибка " << e.id << ": " << e.message
				<< "\nСтрока " << e.position.line + 1
				<< " позиция " << e.position.cells + 1 << std::endl;
			system("pause");
		}
		else
		{
			if (e.position.cells == -1 || e.position.line == -1)
				*stream << std::endl << "Ошибка " << e.id << ": " << e.message;
			else if (e.position.cells == NULL)
				*stream << std::endl << "Ошибка " << e.id << ": " << e.message
				<< "\nСтрока " << e.position.line + 1;
			else
				*stream << std::endl << "Ошибка " << e.id << ": " << e.message
				<< "\nСтрока " << e.position.line + 1
				<< " позиция " << e.position.cells + 1;
		}
	}

	void writeLexTable(const LT::LexTable &Lextable, const char* outputFilename)
	{
		LOG logg;
		logg.stream = new std::ofstream(outputFilename, std::ofstream::out);
		if (logg.stream->fail()) {
			throw ERROR_THROW(4);
		}
		 *logg.stream<<"---------Таблица лексем---------\n"<<
			std::setw(8) << std::left << "Лексема " <<
			std::setw(9) << std::left << "№ строки " <<
			std::setw(8) << std::left << "№ в ТЛ " <<
			std::setw(8) << std::left << "№ в ТИ " << std::endl;

		for (int i = 0; i < Lextable.size; i++)
		{
			*logg.stream << std::setw(8) << std::left << Lextable.table[i].lexema <<
				std::setw(9) << std::left << Lextable.table[i].sn;
			*logg.stream << std::setw(8) << std::left << i;
			*logg.stream << std::setw(8) << std::left;
			if (Lextable.table[i].idxTI != -1)
				*logg.stream << Lextable.table[i].idxTI;
			else
				*logg.stream << '-';
			*logg.stream << std::setw(8) << std::left;
			*logg.stream << std::endl;
		}
		*logg.stream << "\n\n";
	}

	void writeIDtable(const IT::IdTable &IDtable, const char* outputFilename)
	{
		LOG loog;
		loog.stream = new std::ofstream(outputFilename, std::ofstream::out);
		if (loog.stream->fail()) {
			throw ERROR_THROW(5);
		}
		*loog.stream << "---------------Таблица идентификаторов-------------------------------\n" <<
			std::setw(10) << std::left << "Имя id " <<
			std::setw(10) << std::left << "Тип данных " <<
			std::setw(11) << std::left << "Тип id " <<
			std::setw(10) << std::left << "№ в ТЛ " <<
			std::setw(10) << std::left << "Значение" <<
			std::endl;

		for (int i = 0; i < IDtable.size; i++)
		{
			*loog.stream << std::setw(10) << std::left <<
				std::setw(10) << std::left << IDtable.table[i].id <<
				std::setw(11) << std::left;

			if (IDtable.table[i].iddatatype == IT::INT)
				*loog.stream << INTEGER;
			else
				*loog.stream << STRING;

			*loog.stream << std::setw(11) << std::left;
			switch (IDtable.table[i].idtype)
			{
			case IT::F:
				*loog.stream << "Function"; break;
			case IT::V:
				*loog.stream << "Variable"; break;
			case IT::P:
				*loog.stream << "Parameter"; break;
			case IT::L:
				*loog.stream << "Literal"; break;
			}
			*loog.stream << std::setw(10) << std::left << IDtable.table[i].idxfirstLE;
			if (IDtable.table[i].iddatatype == IT::INT)
				*loog.stream << IDtable.table[i].value.vint;
			else
			{
				if (IDtable.table[i].value.vstr.len != 0)
					*loog.stream << IDtable.table[i].value.vstr.str;
				else
					*loog.stream << "NULL";
			}
			*loog.stream << std::endl;
		}
		*loog.stream << "\n\n";
	}

	void writeIntermediateCode(LOG &log, LT::LexTable &Lextable)
	{
		int pb = NULL;
		char*buffer = new char[1024];
		*log.stream << "---------Промежуточный код----------\n---До построения польской записи---\n";
		for (int i = 0; i < Lextable.size; i++)
		{
			if (Lextable.table[i].lexema == NULL)
				continue;
			buffer[pb] = Lextable.table[i].lexema;
			pb++;
			if (Lextable.table[i + 1].sn != Lextable.table[i].sn)
			{
				buffer[pb] = '\0';
				if (Lextable.table[i].sn < 10)
				{
					*log.stream << '0';
				}

				*log.stream << Lextable.table[i].sn << ' ';
				*log.stream << buffer << std::endl;
				pb = NULL;
			}
		}
	}
	void writeIntermediateCode(LOG &log, LT::LexTable &Lextable, const char* outputFilename)
	{
		LOG llog;
		llog.stream = new std::ofstream(outputFilename, std::ofstream::out);
		if (llog.stream->fail()) {
			throw ERROR_THROW(7);
		}
		int pb = NULL;
		char*buffer = new char[1024];
		*llog.stream << "---------Промежуточный код---------\n---После построения польской записи---\n";
		for (int i = 0; i < Lextable.size; i++)
		{
			if (Lextable.table[i].lexema == NULL)
				continue;
			buffer[pb] = Lextable.table[i].lexema;
			pb++;
			if (Lextable.table[i + 1].sn != Lextable.table[i].sn)
			{
				buffer[pb] = '\0';
				if (Lextable.table[i].sn < 10)
				{
					*llog.stream << '0';
				}

				*llog.stream << Lextable.table[i].sn << ' ';
				*llog.stream << buffer << std::endl;
				pb = NULL;
			}
		}
	}

	void Close(LOG &log)
	{
		(*log.stream).close();
	}
}