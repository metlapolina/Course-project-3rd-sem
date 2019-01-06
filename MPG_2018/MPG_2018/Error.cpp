#include "pch.h"
#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "[SYSTEM] Недопустимый код ошибки"),		//код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "[SYSTEM] Системный сбой"),
		ERROR_ENTRY(2, "[SYSTEM] Ошибка при открытии файла с исходным кодом(in.txt)"),
		ERROR_ENTRY(3, "[SYSTEM] Ошибка при открытии файла протокола(in.txt.log)"),
		ERROR_ENTRY(4, "[SYSTEM] Ошибка при открытии файла протокола(LTable.txt)"),
		ERROR_ENTRY(5, "[SYSTEM] Ошибка при открытии файла протокола(ITable.txt)"),
		ERROR_ENTRY(6, "[SYSTEM] Ошибка при открытии файла протокола(MFST.txt)"),
		ERROR_ENTRY(7, "[SYSTEM] Ошибка при открытии файла протокола(PN.txt)"),
		ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9), ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[IN] Параметр -in должен быть задан"),
		ERROR_ENTRY(101, "[IN] Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(102, "[IN] Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109), ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "[LEX] Превышен размер таблицы лексем"),
		ERROR_ENTRY(201, "[LEX] Превышен размер таблицы идентификаторов"),
		ERROR_ENTRY(202, "[LEX] Таблица лексем переполнена"),
		ERROR_ENTRY(203, "[LEX] Таблица идентификаторов переполнена"),
		ERROR_ENTRY(204, "[LEX] Неверное значение целочисленного литерала"), 
		ERROR_ENTRY(205, "[LEX] Превышена максимальная длина строкового литерала"), 
		ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209), ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY(300, "[SYN] Неверная структура программы"),
		ERROR_ENTRY(301, "[SYN] Ошибка в параметрах функции "),
		ERROR_ENTRY(302, "[SYN] Ошибка в построении конструкции языка"),
		ERROR_ENTRY(303, "[SYN] Ошибка в выражении"),
		ERROR_ENTRY(304, "[SYN] Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(305, "[SYN] Ошибка в построении арифметических выражений"),
		ERROR_ENTRY_NODEF(306), ERROR_ENTRY_NODEF(307), ERROR_ENTRY_NODEF(308), ERROR_ENTRY_NODEF(309), ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360), ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY(400, "[SEM] Отсутствие главной функции"),
		ERROR_ENTRY(401, "[SEM] Обнаружена вторая главная функция"),
		ERROR_ENTRY(402, "[SEM] Запрещено присваивать значение функции"),
		ERROR_ENTRY(403, "[SEM] Запрещено возвращать функцию"),
		ERROR_ENTRY(404, "[SEM] Неверное количество параметров функции"),
		ERROR_ENTRY(405, "[SEM] Несоответствие типа возвращаемого значения функции"),
		ERROR_ENTRY(406, "[SEM] Отсутствует предварительное определение"),
		ERROR_ENTRY(407, "[SEM] Попытка переопределения"),
		ERROR_ENTRY(408, "[SEM] Неверное значение"),
		ERROR_ENTRY(409, "[SEM] Ошибка инициализации"),
		ERROR_ENTRY(410, "[SEM] Несоответствие типов в выражении"),
		ERROR_ENTRY(411, "[SEM] Пропущен символ окончания литерала"),
		ERROR_ENTRY(412, "[SEM] Запрещено деление на нуль"),
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