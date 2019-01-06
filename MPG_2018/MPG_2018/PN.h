#pragma once
#include "pch.h"
#include "LexAnalysis.h"
#include "FST.h"

struct PN {
	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
	bool searchExpression(Lexer::LEX);
	int prior(char);
};