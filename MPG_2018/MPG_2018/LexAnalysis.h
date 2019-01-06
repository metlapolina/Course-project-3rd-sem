#pragma once

#include "pch.h"
#include "IT.h"
#include "LT.h"
#include "In.h"
#include "Log.h"
#include "FST.h"

namespace Lexer
{
	struct LEX
	{
		LT::LexTable Lextable;
		IT::IdTable	IDtable;
		bool isLex = true;
	};

	struct Graph
	{
		char lexema;
		FST::FST graph;
	};

	LEX Run(In::IN &InStruct, Log::LOG &log, Parm::PARM &parm);
}
