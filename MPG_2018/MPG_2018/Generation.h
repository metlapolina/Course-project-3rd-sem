#pragma once

#include "LexAnalysis.h"
#include "Graphs.h"

#define HEAD ".586 \n.model flat, stdcall \nincludelib libucrt.lib \nincludelib kernel32.lib \nincludelib ../Debug/GenLib.lib \nExitProcess PROTO: DWORD \npows\tPROTO: DWORD, : DWORD \nstrlength\tPROTO :DWORD \nabsnum\tPROTO: DWORD \noutput_int\tPROTO: DWORD \noutput_str\tPROTO: DWORD \ncatlines\tPROTO: DWORD, : DWORD, :DWORD"

bool isGenerated(Lexer::LEX);