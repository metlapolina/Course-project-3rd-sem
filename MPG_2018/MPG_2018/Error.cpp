#include "pch.h"
#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "[SYSTEM] ������������ ��� ������"),		//��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "[SYSTEM] ��������� ����"),
		ERROR_ENTRY(2, "[SYSTEM] ������ ��� �������� ����� � �������� �����(in.txt)"),
		ERROR_ENTRY(3, "[SYSTEM] ������ ��� �������� ����� ���������(in.txt.log)"),
		ERROR_ENTRY(4, "[SYSTEM] ������ ��� �������� ����� ���������(LTable.txt)"),
		ERROR_ENTRY(5, "[SYSTEM] ������ ��� �������� ����� ���������(ITable.txt)"),
		ERROR_ENTRY(6, "[SYSTEM] ������ ��� �������� ����� ���������(MFST.txt)"),
		ERROR_ENTRY(7, "[SYSTEM] ������ ��� �������� ����� ���������(PN.txt)"),
		ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9), ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[IN] �������� -in ������ ���� �����"),
		ERROR_ENTRY(101, "[IN] ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(102, "[IN] ��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109), ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "[LEX] �������� ������ ������� ������"),
		ERROR_ENTRY(201, "[LEX] �������� ������ ������� ���������������"),
		ERROR_ENTRY(202, "[LEX] ������� ������ �����������"),
		ERROR_ENTRY(203, "[LEX] ������� ��������������� �����������"),
		ERROR_ENTRY(204, "[LEX] �������� �������� �������������� ��������"), 
		ERROR_ENTRY(205, "[LEX] ��������� ������������ ����� ���������� ��������"), 
		ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209), ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "[SYN] �������� ��������� ���������"),
		ERROR_ENTRY(301, "[SYN] ������ � ���������� ������� "),
		ERROR_ENTRY(302, "[SYN] ������ � ���������� ����������� �����"),
		ERROR_ENTRY(303, "[SYN] ������ � ���������"),
		ERROR_ENTRY(304, "[SYN] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(305, "[SYN] ������ � ���������� �������������� ���������"),
		ERROR_ENTRY_NODEF(306), ERROR_ENTRY_NODEF(307), ERROR_ENTRY_NODEF(308), ERROR_ENTRY_NODEF(309), ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360), ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY(400, "[SEM] ���������� ������� �������"),
		ERROR_ENTRY(401, "[SEM] ���������� ������ ������� �������"),
		ERROR_ENTRY(402, "[SEM] ��������� ����������� �������� �������"),
		ERROR_ENTRY(403, "[SEM] ��������� ���������� �������"),
		ERROR_ENTRY(404, "[SEM] �������� ���������� ���������� �������"),
		ERROR_ENTRY(405, "[SEM] �������������� ���� ������������� �������� �������"),
		ERROR_ENTRY(406, "[SEM] ����������� ��������������� �����������"),
		ERROR_ENTRY(407, "[SEM] ������� ���������������"),
		ERROR_ENTRY(408, "[SEM] �������� ��������"),
		ERROR_ENTRY(409, "[SEM] ������ �������������"),
		ERROR_ENTRY(410, "[SEM] �������������� ����� � ���������"),
		ERROR_ENTRY(411, "[SEM] �������� ������ ��������� ��������"),
		ERROR_ENTRY(412, "[SEM] ��������� ������� �� ����"),
		ERROR_ENTRY_NODEF(413), ERROR_ENTRY_NODEF(414), ERROR_ENTRY_NODEF(415), ERROR_ENTRY_NODEF(416), ERROR_ENTRY_NODEF(417), ERROR_ENTRY_NODEF(418), ERROR_ENTRY_NODEF(419), ERROR_ENTRY_NODEF10(420), ERROR_ENTRY_NODEF10(430), ERROR_ENTRY_NODEF10(440), ERROR_ENTRY_NODEF10(450), ERROR_ENTRY_NODEF10(460), ERROR_ENTRY_NODEF10(470), ERROR_ENTRY_NODEF10(480), ERROR_ENTRY_NODEF10(490)
	};
	ERROR GetError(int id)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY)
			return errors[0];
		else
			return errors[id];
	}

	ERROR GetError(int id, int line, int cells)
	{
		ERROR dopError = GetError(id);
		dopError.position.cells = cells;
		dopError.position.line = line;
		return dopError;
	}
}