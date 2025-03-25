/*
 * SBB_CLICK.h
 *
 * SBB_CLICK - библиотека для реализации события при долгом удержании кнопки в течении заданного количества секунд.  Для проекта MicroSB.ru
 *
 * Февраль 2016.
 */

#ifndef SBB_CLICK_h
#define SBB_CLICK_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

class SBB_CLICK
{
	// Публичные переменные
	public:
		SBB_CLICK(byte _P, byte _S); // Конструктор класса
		int click(); // Функция нажатия кнопки
		void release(); // Функция отпускания кнопки
	
	// Приватные переменные
	private:
		byte _Pin; // пин кнопки
		byte _Sek; // количество секунд
		byte _ButtomStatus; // статус кнопки
		unsigned long _EventTimeStart; // время начала нажатия кнопки
		unsigned long _EventTimeStop; // общее время нажатия кнопки
};

#endif // #ifndef SBB_CLICK