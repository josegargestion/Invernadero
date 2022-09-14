/**
 * @file CTiempos.h
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @brief Biblioteca gestion horas de encendido - apagado.
 * La biblioteca proporciona una estructura base set_Horaio, sobre la que aplicar la comprobación
 * asi como metodos para modificar los datos de esta estructura con diferentes sobrecargas.
 * @version 0.1
 * @date 2022-09-13
 * @todo Crear una funcion - estructura virtual que pueda ser empleada 
 * para implementar una funcion aplicable a otros programas.
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CTIEMPOS_H
#define CTIEMPOS_H
#include <Arduino.h> // STD de arduino.
#include "estructuras.h"
class Control_Tiempos
{
public:
	/**
	 *
	 * @brief Variables de horario.
	 *
	 */
	set_Horario setOn, setOff;
	set_Ambiente setAOn, setAOff;
	Control_Tiempos();
	/**
	 * @brief Genera un set_Horario a partir de una Hora y un Minuto dados.
	 * @param Hora uint8_t Hora a asignar.
	 * @param minuto uint8_t Minuto a asignar.
	 * @return estructura set_Horario.
	 **/
	set_Horario SetTime(uint8_t Hora, uint8_t Minuto);
	/**
	 * @brief Genera un set_Ambiente a partir de cada dato individual.
	 * @param Hora uint8_t Hora a asignar.
	 * @param Minuto unit8_t Minuto a asignar.
	 * @param Temp float Temperatura a asignar.
	 * @param HR float Humedad a asignar.
	 * @return estructura set_Ambiente.
	 */
	set_Ambiente SetTime(uint8_t Hora, uint8_t Minuto, float Temp, float HR);
	/**
	 * @brief Genera un set_Ambiente a partir de una hora y unos datos de sensor.
	 * @param Hora uint8_t Hora a asignar.
	 * @param Minuto Minuto a asignar.
	 * @param sensores datos_sensores estructura de datos.
	 * @return estructura set_Ambiente.
	 */
	set_Ambiente SetTime(uint8_t Hora, uint8_t Minuto, datos_sensores sensores);
	/**
	 * @brief Configura el tiempo de encendido
	 *
	 * @param Hora Hora de inicio del encendido.
	 * @param Minuto Minuto de inicio del encendido.
	 */
	void SetTimeOn(uint8_t Hora, uint8_t Minuto);
	/**
	 * @brief Configura el tiempo de encendido
	 *
	 * @param Hora Hora de inicio del encendido.
	 * @param Minuto Minuto de inicio del encendido.
	 * @param setOn Set a modificar.
	 */
	void SetTimeOn(set_Horario set);
	/**
	 * @brief Configura el tiempo de apagado.
	 *
	 * @param Hora Hora de inicio del apagado.
	 * @param Minuto Minutor de inicio del apagado.
	 */
	void SetTimeOff(uint8_t Hora, uint8_t Minuto);
	/**
	 * @brief Configura el tiempo de apagado.
	 *
	 * @param Hora Hora de inicio del apagado.
	 * @param Minuto Minutor de inicio del apagado.
	 * @param setOff Set a modificar.
	 */
	void SetTimeOff(set_Horario set);
	/**
	 * @brief Configura el tiempo de encendido
	 *
	 * @param Hora Hora de inicio del encendido.
	 * @param Minuto Minuto de inicio del encendido.
	 * @param Temp Temperatura durante este periodo.
	 * @param Hr Humedad durante este periodo.
	 */
	void SetTimeOn(set_Ambiente setA);
	/**
	 * @brief Configura el tiempo de apagado.
	 *
	 * @param Hora Hora de inicio del apagado.
	 * @param Minuto Minutor de inicio del apagado.
	 * @param Temp Temperatura durante este perido.
	 * @param Hr Temperatura durante el periodo.
	 */
	void SetTimeOff(set_Ambiente setA);
	/**
	 * @brief En funcion de setOn y setOff devuelve estado esperado en funcion del teimpo actual.
	 *
	 * @param setOn Hora y minuto de encendido.
	 * @param setOff Hora y minuto de apagado.
	 * @return true Encendido.
	 * @return false Apagado.
	 */
	bool ControlOnOff(set_Ambiente setAOn, set_Ambiente setAOff);
	bool ControlOnOff(set_Horario setOn, set_Horario setOff);
	bool ControlOnOff();
};
#endif