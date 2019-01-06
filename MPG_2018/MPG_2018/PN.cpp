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
	std::stack<LT::Entry> st;							//���� ��� ����������
	LT::Entry outstr[20];								//�������� ������
	int len = 0,										//����� �����
		lenout = 0,										//����� �������� ������
		semicolonid;									//�� ��� �������� ������� � ������ � �������
	char skob = 0;										//���-�� ������
	int indoffunk;										//������ ��� ������ �� ������� � ��������
	for (int i = lextable_pos; lextable.table[i].lexema != LEX_SEMICOLON; i++) {
		len = i;										//������� ����� ���������
		semicolonid = i + 1;
	}
	len++;
	for (int i = lextable_pos; i < len; i++) {
		switch (lextable.table[i].lexema)				//���������� ��������
		{
		case LEX_RIGHTHESIS:						//���� ������ ������ - ������������ ����� �� ����� ������
		{
			while (st.top().lexema != '(') {
				outstr[lenout++] = st.top();		//���������� � �������� ������ ��������� ������ ����� ��������
				skob++;
				st.pop();							//������� ������� �����
			}
			st.pop();								//������� ����� ������ � �����
			break;
		}
		case LEX_ABS:								//����������� �������
		case LEX_POW:
		case LEX_STRLEN:
		case LEX_ID:								//��
		case LEX_LITERAL:							//�������
		{
			if (lextable.table[i + 1].lexema == LEX_LEFTHESIS) {	//���� - ����� ������
				indoffunk = i;										//������, �������
				i += 2;												//��������� � ����������
				while (lextable.table[i].lexema != LEX_RIGHTHESIS) {//���� ������ ���������� �������, ������������ �� � ������
					if (lextable.table[i].lexema != LEX_COMMA) {
						outstr[lenout++] = lextable.table[i++];
					}
					else
					{
						skob++;
						i++;						//���������� �������
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
			st.push(lextable.table[i]);							//�������� � ���� ����� ������
			skob++;
			break;
		}

		case LEX_PLUS:
		case LEX_MINUS:
		case LEX_STAR:
		case LEX_DIRSLASH:
		{
			if (!st.size())						//���� ������ ����
				st.push(lextable.table[i]);		//������ ���������� � �������� ������
			else {
				int pr, id;
				id = st.top().lexema;
				pr = prior(id);				//���������� ��������� �������� � �����
				if (prior(lextable.table[i].lexema) > pr)//���� ��������� ����������� �������� ������ �������� �� ������� �����
					st.push(lextable.table[i]);			 //��������� �������� � ����
				else {									 //���� ������, �� ���������� �� ����� � �������� ������ ��� �������� 
														 //� ������� ��� ������ �����������
					while (st.size() && prior(lextable.table[i].lexema) <= prior(id))
					{
						outstr[lenout] = st.top();
						st.pop();
						lenout++;
					}
					st.push(lextable.table[i]);			 //��������� � ���� ������� ��������
				}
			}
			break;
		}
		}
	}
	while (st.size()) {
		outstr[lenout++] = st.top();									//����� � ������ ���� ������ �� �����
		st.pop();
	}
	for (int i = lextable_pos, k = 0; i < lextable_pos + lenout; i++) {
		if ((lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == 2) || lextable.table[i].lexema == LEX_POW || lextable.table[i].lexema == LEX_STRLEN || lextable.table[i].lexema == LEX_ABS) {}
		else {
			lextable.table[i] = outstr[k];									//������ � ������� ������ �������� ������
			k++;
		}
	}
	lextable.table[lextable_pos + lenout] = lextable.table[semicolonid];//������� �������� � ������ � �������
	for (int i = 0; i < skob; i++)
	{
		for (int j = lextable_pos + lenout + 1; j < lextable.size; j++)	//�������� �� ������ �����, ���������� �� ������
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
