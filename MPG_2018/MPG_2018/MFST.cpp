#include "pch.h"
#include "GRB.h"
#include "MFST.h"
#include "Error.h"
#include "LexAnalysis.h"

int FST_TRACE_n = -1;

char rbuf[205], sbuf[205], lbuf[1024];

namespace MFST
{
	std::ofstream mfststream;
	MfstState::MfstState() // конструктор по умолчанию
	{
		lenta_position = 0; //позиция на ленте
		nrule = -1; //номер текущего правила
		nrulechain = -1; //номер текущей цепочки
	};
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain) //конструктор (позиция на ленте, стек автомата, номер текущей цепочки и текущего правила)
	{
		lenta_position = pposition; //позиция на ленте
		st = pst; //стек автомата
		nrulechain = pnrulechain;//номер текущего правила и цепочки
	};
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain) //конструктор (позиция на ленте, стек автомата,номер текущего правила, номер текущей цепочки)
	{
		lenta_position = pposition;//позиция в ленте
		st = pst;//стек автомата
		nrule = pnrule;//номер текущего правила
		nrulechain = pnrulechain;//номер текущей цепочки
	};
	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SURPRISE;
		nrule = -1;
		nrule_chain = -1;
	};
	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)//диагностика
	{                                                     //(позиция на ленте, код завершения шага, номер правила, номер цепочки правила)
		lenta_position = plenta_position; //позиция на ленте
		rc_step = prc_step;//код завершения шага
		nrule = pnrule;//номер правила
		nrule_chain = pnrule_chain;//номер цепочки правила
	};
	Mfst::Mfst() { lenta = 0; lenta_size = lenta_position = 0; }; //конструктор по умолчанию 
	Mfst::Mfst(Lexer::LEX plex, GRB::Greibach pgrebach)//(результат работы лексического анализатора, грамматика Грейбах)
	{
		grebach = pgrebach; //Грейбах
		lex = plex; //рез работы лекс анализатора
		lenta = new short[lenta_size = lex.Lextable.size];//размер ленты = текущий размер таблицы лексем
		for (int k = 0; k < lenta_size; k++)lenta[k] = GRB::TS(lex.Lextable.table[k].lexema);//заносит в ленту терминалы
		lenta_position = 0;
		st.push(grebach.stbottomT);//добавляет дно стека
		st.push(grebach.startN);//добавляет стартовый символ
		nrulechain = -1;//изначально правило равно -1
	};
	Mfst::RC_STEP Mfst::step() //выполнить шаг автомата
	{
		RC_STEP rc = SURPRISE; //код возврата = ошибка возврата
		if (lenta_position < lenta_size)
		{
			if (GRB::ISNS(st.top())) //извлекаем последний элемент стека и проверяем нетерминал ли он
			{
				GRB::Rule rule;
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0)//смотрим, если такое правило есть идём дальше, если нет то елсе
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)//получаем следующую цепочку и выводим её номер, илбо возвращаем -1
					{
						MFST_TRACE1//вывод
							savestate();//сохранить состояние автомата
						st.pop();//извлекаем верхушку стека.
						push_chain(chain); //поместить цепочку правила в стек
						rc = NS_OK; //найдено правило и цепочка... цепочка записана в стек
						MFST_TRACE2//вывод
					}
					else
					{
						MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE")//вывод
							savediagnois(NS_NORULECHAIN); //код завершения
						rc = reststate() ? NS_NORULECHAIN : NS_NORULE; //восстановить состояние автомата
					};
				}
				else rc = NS_ERROR;//неизвестный нетерминальный символ грамматики
			}
			else if ((st.top() == lenta[lenta_position]))//если текущий символ ленты равен вершине стека
			{
				lenta_position++; //продвигаем ленту
				st.pop();//вершина стека
				nrulechain = -1; //номер текущего правила равен -1
				rc = TS_OK;
				MFST_TRACE3
			}
			else { MFST_TRACE4("TS_NOK/NS_NORULECHIN") rc = reststate() ? TS_NOK : NS_NORULECHAIN; };
		}
		else { rc = LENTA_END; MFST_TRACE4("LENTA_END") };
		return rc;
	};

	bool Mfst::push_chain(GRB::Rule::Chain chain) //поместить цепочку правила в стек (цепочка правила)
	{
		for (int k = chain.size - 1; k >= 0; k--)st.push(chain.nt[k]); //к = длинне цепочке-1. заносим цепочку в стек
		return true;
	};
	bool Mfst::savestate() //сохранить состояние автомата
	{
		storestate.push(MfstState(lenta_position, st, nrule, nrulechain)); //стек для сохранения состояния. заносим сохраняемое состояние
		MFST_TRACE6("SAVESTATE:", storestate.size());
		return true;
	};
	bool Mfst::reststate() //восстановить состояние автомата
	{
		bool rc = false;
		MfstState state;
		if (rc = (storestate.size() > 0))
		{
			state = storestate.top();
			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;
			storestate.pop();
			MFST_TRACE5("RESSTATE")

		};
		return rc;
	};
	bool Mfst::savediagnois(RC_STEP prc_step)
	{
		bool rc = false;
		short k = 0;
		while (k < MFST_DIAGN_NUMBER&&lenta_position <= diagnosis[k].lenta_position)k++;
		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++)diagnosis[j].lenta_position = -1;
		};
		return rc;
	};
	bool Mfst::start()
	{
		
		mfststream.open("MFST.txt", std::fstream::out);
		if (mfststream.fail()) {
			throw ERROR_THROW(6);
		}
		MFST_TRACE_START
		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step();
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)rc_step = step();
		switch (rc_step)
		{
		case LENTA_END:         MFST_TRACE4("------>LENTA_END")
			mfststream << "-------------------------------------------------------------------------------------" << std::endl;
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d:всего строк %d, синтаксический анализ выполнен без ошибок ", 0, lenta_size);
			mfststream << std::setw(4) << std::left << 0 << ":всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок " << std::endl;
			rc = true;
			mfststream.close();
			break;
		case NS_NORULE:         MFST_TRACE4("------>NS_NORULE")
			mfststream << "-------------------------------------------------------------------------------------" << std::endl;
			mfststream << getDiagnosis(0, buf) << std::endl;
			mfststream << getDiagnosis(1, buf) << std::endl;
			mfststream << getDiagnosis(2, buf) << std::endl;
			mfststream.close();
			break;
		case NS_NORULECHAIN:       MFST_TRACE4("------>NS_NORULECHAIN") 
			mfststream.close(); 
			break;
		case NS_ERROR:             MFST_TRACE4("------>NS_ERROR") 
			mfststream.close(); 
			break;
		case SURPRISE:             MFST_TRACE4("------>SURPRISE") 
			mfststream.close(); 
			break;
		};
		return rc;

	};

	char* Mfst::getCSt(char*buf)
	{
		for (int k = (signed)st.size() - 1; k >= 0; --k)
		{
			short p = st._Get_container()[k];
			buf[st.size() - 1 - k] = GRB::Rule::Chain::alphabet_to_char(p);
		};
		buf[st.size()] = 0x00;
		return buf;
	};
	char *Mfst::getCLenta(char*buf, short pos, short n)
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; i++)buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		buf[i - pos] = 0x00;
		return buf;
	};
	char* Mfst::getDiagnosis(short n, char*buf)
	{
		char *rc = 0;				//=""
		int errid = 0;
		int lpos = -1;
		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			errid = grebach.getRule(diagnosis[n].nrule).iderror;
			Error::ERROR err = Error::GetError(errid);
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: строка %d,%s", err.id, lex.Lextable.table[lpos].sn, err.message);
			rc = buf;
		};
		return rc;
	};
	void Mfst::printrules()
	{
		mfststream.open("MFST.txt", std::fstream::app);
		MfstState state;
		GRB::Rule rule;
		mfststream << "---Дерево разбора---" << std::endl;
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			rule = grebach.getRule(state.nrule);
			MFST_TRACE7
		};
		mfststream.close();
	};
	bool Mfst::savededucation()
	{
		MfstState state;
		GRB::Rule rule;
		deducation.nrules = new short[deducation.size = storestate.size()];
		deducation.nrulechains = new short[deducation.size];
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate._Get_container()[k];
			deducation.nrules[k] = state.nrule;
			deducation.nrulechains[k] = state.nrulechain;
		};
		return true;
	};
};