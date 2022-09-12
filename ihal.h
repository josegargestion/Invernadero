/**
 * @file hal.h
 * @brief Funciones de la capa de abstraccion de hardware.
 * Esta libreria contiene las funciones referenes al hardware del sistema, para hacer
 * que el programa funcione sin tener en cuenta factores como los pines de entrada
 * o la configuracion de sensores.
 *
 * @author Josegar1908@gmail.com
 * @version 0.0.1
 *
 * @todo	- Comprobación del sistema.
 * @copyright Copyright (c) 2021
 */
#pragma once
#ifndef IHAL_H
#define IHAL_H
#include "estructuras.h"	// Estructuras de datos.
#include <Arduino.h>		// STD de arduino.
#include "configurations.h" // Guarda los datos por defecto del equipo.

class IHAL
{
public:
	static estado_Hardware estadoHardware;
	virtual void begin() = 0;
	virtual bool GetEstado() = 0;
	virtual void Control() = 0;
	virtual bool GetEstadoIluminacion() = 0;
	virtual void EncenderIluminacion() = 0;
	virtual void EncenderCalefaccion() = 0;
	virtual void EncenderHumidificador() = 0;
	virtual void EncenderDeshumidificador() = 0;
	virtual void EncenderExtractor() = 0;
	virtual void EncenderImpulsor() = 0;
	virtual void ApagarCalefaccion() = 0;
	virtual void ApagarHumidificador() = 0;
	virtual void ApagarDeshumidificador() = 0;
	virtual void ApagarExtractor() = 0;
	virtual void ApagarImpulsor() = 0;
	virtual void ApagarIluminacion() = 0;
	virtual void GetSensores() = 0;
};
#endif
