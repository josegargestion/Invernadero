/**
 * @file deposito.cpp
 * @brief Codigo de la biblioteca deposito.h
 * 
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @version 0.5.0
 * @date 2022-06-23
 * @copyright Copyright (c) 2021
 * 
 */
#include "hardware.h"
#include "deposito.h"		// Control sistema de deposito de liquidos
#include "configurations.h" // Guarda los datos por defecto del equipo.
#include "debug.h"			// Necesario para las llamadas de depuración.
#include "Time.h"			// Control de horas y tiempos, ademas del rtc.
#include "CTiempos.h" // Personal de control de tiempos del procesador y horarios.
#include "cAPPconfig.h"		// Guardado de datos a EEPROM.
extern Hardware Sistema1;
Deposito::Deposito()
{
}
void Deposito::begin()
{
	DTIME;
	DPRINTLN(F(" Inicializando Deposito."));
	depositoMillis.lastmillis = 0;
}
void Deposito::Control()
{
	DTIME;
	DPRINTLN(F(" Ejecutando Control de Deposito."));
	depositoMillis.currentmillis = millis();
	if (depositoMillis.currentmillis - depositoMillis.lastmillis >= depositoMillis.period)
	{
		UpdateSondas();
		if (estadoDeposito.SensorMax && estadoDeposito.SensorMin)
		{
#ifdef DEBUG
			DTIME;
			DPRINT(" Sensor Max : ");
			DPRINT(estadoDeposito.SensorMax);
			DPRINT(" Sensor Min : ");
			DPRINT(estadoDeposito.SensorMin);
			DPRINTLN();
#endif
			Vaciado(OFF);
			LLenado(OFF);
		}
		else if (estadoDeposito.SensorMax && !estadoDeposito.SensorMin)
		{
#ifdef DEBUG
			DTIME;
			DPRINT(" Sensor Max : ");
			DPRINT(estadoDeposito.SensorMax);
			DPRINT(" Sensor Min : ");
			DPRINT(estadoDeposito.SensorMin);
			DPRINTLN();
#endif
			DTIME;
			DPRINTLN(F(" Ejecutando Control error Deposito."));
			Sistema1.ControlErrorDeposito();
		}
		else if (!estadoDeposito.SensorMax && estadoDeposito.SensorMin)
		{
#ifdef DEBUG
			DTIME;
			DPRINT(" Sensor Max : ");
			DPRINT(estadoDeposito.SensorMax);
			DPRINT(" Sensor Min : ");
			DPRINT(estadoDeposito.SensorMin);
			DPRINTLN();
#endif
			Vaciado(OFF);
			LLenado(ON);
		}
		else if (!estadoDeposito.SensorMax && !estadoDeposito.SensorMin)
		{
#ifdef DEBUG
			DTIME;
			DPRINT(" Sensor Max : ");
			DPRINT(estadoDeposito.SensorMax);
			DPRINT(" Sensor Min : ");
			DPRINT(estadoDeposito.SensorMin);
			DPRINTLN();
#endif
			Vaciado(OFF);
			LLenado(ON);
		}
		depositoMillis.lastmillis = millis();
	}
}
void Deposito::UpdateSondas()
{
	Sistema1.UpdateSondas();
	estadoDeposito.SensorMax = Sistema1.GetSondaMaximo();
	estadoDeposito.SensorMin = Sistema1.GetSondaMinimo();
#ifdef DEBUG
	DTIME;
	DPRINT(" Sensor Max : ");
	DPRINT(estadoDeposito.SensorMax);
	DPRINT(" Sensor Min : ");
	DPRINT(estadoDeposito.SensorMin);
	DPRINTLN();
#endif
}
void Deposito::Vaciado(bool estado)
{
	if (estado)
	{
		Sistema1.EncenderBomba();
	}
	else if (!estado)
	{
		Sistema1.ApagarBomba();
	}
}
void Deposito::LLenado(bool estado)
{
	if (estado)
	{
		Sistema1.EncenderValvula();
	}
	else if (!estado)
	{
		Sistema1.ApagarValvula();
	}
}
