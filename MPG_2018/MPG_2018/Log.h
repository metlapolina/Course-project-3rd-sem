#pragma once

#include "pch.h"
#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "LT.h"
#include "IT.h"

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE] = L" ";
		std::ofstream *stream = NULL;
	};
	bool static Eror = true;
	LOG getstream(wchar_t logfile[]);
	void writeLog(LOG &log);
	void writeParm(LOG &log, Parm::PARM &parm);
	void writeIn(LOG &log, In::IN &in);
	void writeError(std::ofstream *stream, Error::ERROR &error);
	void writeLexTable(const LT::LexTable &lextable, const char* outputFilename);
	void writeIDtable(const IT::IdTable &IDtable, const char* outputFilename);
	void writeIntermediateCode(LOG &log, LT::LexTable &lextable);
	void writeIntermediateCode(LOG &log, LT::LexTable &lextable, const char* outputFilename);
	void Close(LOG &log);
}