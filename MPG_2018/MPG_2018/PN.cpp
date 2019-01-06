#include "pch.h"
#include "PN.h"

bool PN::searchExpression(Lexer::LEX Tables) {
	bool fl = false;
	for (int i = 0; i < Tables.Lextable.size; i++) {
		if (Tables.Lextable.table[i].lexema == LEX_EQUAL) {
			fl = PolishNotation(++i, Tables.Lextable, Tables.IDtable);
		}
	}
	return fl;
}
bool PN::PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {
	std::stack<LT::Entry> st;							//стек для операторов
	LT::Entry outstr[20];								//выходная строка
	int len = 0,										//общая длина
		lenout = 0,										//длина выходной строки
		semicolonid;									//ид для элемента таблицы с точкой с запятой
	char skob = 0;										//кол-во скобок
	int indoffunk;										//индекс для замены на элемент с функцией
	for (int i = lextable_pos; lextable.table[i].lexema != LEX_SEMICOLON; i++) {
		len = i;										//подсчёт длины выражения
		semicolonid = i + 1;
	}
	len++;
	for (int i = lextable_pos; i < len; i++) {
		switch (lextable.table[i].lexema)				//определяем операцию
		{
		case LEX_RIGHTHESIS:						//если правая скобка - выталкивание всего до левой скобки
		{
			while (st.top().lexema != '(') {
				outstr[lenout++] = st.top();		//записываем в выходную строку очередной символ между скобками
				skob++;
				st.pop();							//удаляем вершину стека
			}
			st.pop();								//удаляем левую скобку в стеке
			break;
		}
		case LEX_ABS:								//стандартные функции
		case LEX_POW:
		case LEX_STRLEN:
		case LEX_ID:								//ид
		case LEX_LITERAL:							//литерал
		{
			if (lextable.table[i + 1].lexema == LEX_LEFTHESIS) {	//след - левая скобка
				indoffunk = i;										//значит, функция
				i += 2;												//переходим к параметрам
				while (lextable.table[i].lexema != LEX_RIGHTHESIS) {//пока внутри аргументов функции, переписываем их в строку
					if (lextable.table[i].lexema != LEX_COMMA) {
						outstr[lenout++] = lextable.table[i++];
					}
					else
					{
						skob++;
						i++;						//игнорируем запятые
					}
				}
				outstr[lenout++] = lextable.table[indoffunk];
				skob += 2;

			}
			else {
				outstr[lenout++] = lextable.table[i];
			}
			break;
		}
		case LEX_LEFTHESIS:
		{
			st.push(lextable.table[i]);							//помещаем в стек левую скобку
			skob++;
			break;
		}

		case LEX_PLUS:
		case LEX_MINUS:
		case LEX_STAR:
		case LEX_DIRSLASH:
		{
			if (!st.size())						//если пустой стек
				st.push(lextable.table[i]);		//просто записываем в выходную строку
			else {
				int pr, id;
				id = st.top().lexema;
				pr = prior(id);				//определяем приоритет операции в стеке
				if (prior(lextable.table[i].lexema) > pr)//если приоритет добавляемой операции больше операции на вершине стека
					st.push(lextable.table[i]);			 //добавляем операции в стек
				else {									 //если меньше, то записываем из стека в выходную строку все операции 
														 //с большим или равным приоритетом
					while (st.size() && prior(lextable.table[i].lexema) <= prior(id))
					{
						outstr[lenout] = st.top();
						st.pop();
						lenout++;
					}
					st.push(lextable.table[i]);			 //добавляем в стек текущую операцию
				}
			}
			break;
		}
		}
	}
	while (st.size()) {
		outstr[lenout++] = st.top();									//вывод в строку всех знаков из стека
		st.pop();
	}
	for (int i = lextable_pos, k = 0; i < lextable_pos + lenout; i++) {
		if ((lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == 2) || lextable.table[i].lexema == LEX_POW || lextable.table[i].lexema == LEX_STRLEN || lextable.table[i].lexema == LEX_ABS) {}
		else {
			lextable.table[i] = outstr[k];									//запись в таблицу лексем польской записи
			k++;
		}
	}
	lextable.table[lextable_pos + lenout] = lextable.table[semicolonid];//вставка элемента с точкой с запятой
	for (int i = 0; i < skob; i++)
	{
		for (int j = lextable_pos + lenout + 1; j < lextable.size; j++)	//сдвигаем на лишнее место, оставшееся от скобок
		{
			lextable.table[j] = lextable.table[j + 1];
		}
		lextable.size--;
	}
	return 1;
}
int PN::prior(char l) {
	if (l == ')' || l == '(')
		return 1;
	if (l == '+' || l == '-')
		return 2;
	if (l == '*' || l == '/')
		return 3;
}
