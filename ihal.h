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
#include "estructuras.h"
class IHAL
{
public:
	struct IHAL_DATA
	{
		bool estadoIluminacion;
		float temperatura;
		float humedadAire;
		float humedadTierra;
	};
	virtual void begin() = 0;
	virtual IHAL_DATA GetEstado(IHAL_DATA set) = 0;
	virtual bool SetEstado(IHAL_DATA set) = 0;
	virtual void Control() = 0;
	virtual bool GetIluminacion() = 0;
	virtual void SetIluminacion(bool set) = 0;
	virtual void ControlIluminacion() = 0;
	virtual void GetTemperatura() = 0;
	virtual void SetTemperatura() = 0;
	virtual void ControlTemperatura() = 0;
	virtual void GetHumedadAire() = 0;
	virtual void SetHumedadAire() = 0;
	virtual void ControlHumedadAire() = 0;
	virtual void GetHumedadTierra() = 0;
	virtual void SetHumedadTierra() = 0;
	virtual void ControlHumedadTierra() = 0;
};
#endif
