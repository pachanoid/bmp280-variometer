/*
 * SBB_CLICK.cpp 
 *
 * SBB_CLICK - библиотека для реализации события при долгом удержании кнопки в течении заданного количества секунд.  Для проекта MicroSB.ru
 *
 * Февраль 2016.
 */

#ifndef SBB_CLICK_cpp
#define SBB_CLICK_cpp
#include "SBB_CLICK.h"

// конструктор - вызывается всегда при создании экземпляра класса SBB_CLICK
// 1 параметр: номер пона кнопки
// 2 параметр - количество секунд
SBB_CLICK::SBB_CLICK(byte _P, byte _S)
{
	this->_Pin = _P; // пин кнопки
	this->_Sek = _S; // количество секунд
	this->_ButtomStatus = 0; // статус кнопки
	this->_EventTimeStart = 0; // время начала нажатия кнопки
	this->_EventTimeStop = 0; // общее время нажатия кнопки
}

// Функция нажатия кнопки
int SBB_CLICK::click()
{
  // Если кнопка нажата и при этом статус кнопки пустой (0)
  if(digitalRead(this->_Pin)==HIGH && !this->_ButtomStatus)
  {
    // Проверяем что время нажатия на кнопку отстуствует и задаём его
    if(!this->_EventTimeStart)
    {
      this->_EventTimeStart=millis(); // время начала нажатия кнопки
    }

    // Проверяем чтобы время нажатия кнопки было
    if(this->_EventTimeStart)
    {
      this->_EventTimeStop=millis(); // считаем общее время нажатия кнопки
    }

    // Условие выполняется (кнопка нажата более 2 секунд)
    if(this->_EventTimeStop - this->_EventTimeStart>this->_Sek*1000)
    {
      _ButtomStatus = 1; // Изменяем статус кнопки, чтобы повторно не возвращать результат
	  return 1; // условие выполнелось, возвращаем результат 1
    }
  }
	return 0;
}

// Функция отпускания кнопки
// Обязательное условие - ставить её после вызова click()
void SBB_CLICK::release()
{
	// ничего не делаем - просто для условия, которе выполнялось в методе click
  if(digitalRead(this->_Pin)==HIGH && !this->_ButtomStatus)
  {}
  // если кнопка выключена и статус кнопки 1
  else if(digitalRead(this->_Pin)==LOW && this->_ButtomStatus)
  {
    // Обнуляем статус кнопки
    this->_ButtomStatus = 0;
  }
  else
  {
    // если время нажатия кнопки менее 2 сек (по - умолчанию, а вообще это время задаётся в конструкторе), то обнуляем значения
    if(this->_EventTimeStart)
    {
      this->_EventTimeStart = 0; // обнуляем время начала нажатия кнопки
      this->_EventTimeStop = 0; // обнуляем общее время нажатия кнопки
    }
  }
}



#endif // #ifndef SBB_CLICK_cpp