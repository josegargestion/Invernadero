/**
 * @brief Funciones de la capa de abstraccion de hardware
 * Esta libreria contiene las funciones referenes al hardware del sistema, para hacer
 * que el programa funcione sin teenr en cuenta factores como los pines de entrada
 * o la configuracion de sensores.
 * que lo mantiene entre el maximo y el minimo, vaciandolo o rellenandolo cuando sea preciso.
 *
 * @author Josegar1908@gmail.com
 * @version 0.0.0
 *
 * @todo	- Comprobación del sistema.
 * @copyright Copyright (c) 2021
 */
#ifndef HARDWARE_H
#define HARDWARE_H

#include "DHT.h"			// Control sensores DHT.
#include "estructuras.h"	// Estructuras de datos.
#include <Arduino.h>		// STD de arduino.
#include "configurations.h" // Guarda los datos por defecto del equipo.
#include "Debug.h"			// Necesario para las llamadas de depuración.
#include "cAPPconfig.h"		// Guardado de datos a EEPROM.
#include "ihal.h"			// Abstracion de hardware
class Hardware : public IHAL
{
public:
	static estado_Hardware estadoHardware;
	/**
	 * @brief Construct a new Hardware object.
	 *
	 */
	Hardware();
	/**
	 * @brief Inicializador del hardware.
	 *
	 */
	void begin();
	/**
	 * @brief Estado de la Hardware.
	 *
	 * @return true Encendia
	 * @return false Apagada
	 */
	bool GetEstado();
	/**
	 * @brief Gestion automatica de la iluminación, para controlar desde la aplicacion principal.
	 *
	 */
	void Control();
	bool GetEstadoIluminacion();
	void EncenderIluminacion();
	void EncenderCalefaccion();
	void EncenderHumidificador();
	void EncenderDeshumidificador();
	void EncenderExtractor();
	void EncenderImpulsor();
	void ApagarCalefaccion();
	void ApagarHumidificador();
	void ApagarDeshumidificador();
	void ApagarExtractor();
	void ApagarImpulsor();
	void ApagarIluminacion();
	void GetSensores();

private:
	static config_Hardware configHardware;
	/**
	 * @brief Sensor Interior.
	 *
	 */
	DHT sondaInterior;
	/**
	 * @brief Sensor Exterior.
	 *
	 */
	DHT sondaExterior;
	/**
	 * @brief Get the Sensor Exterior object
	 *
	 */
	datos_sensores GetSensor(DHT Sensor);
	static millis_set hardwareMillis;
};
#endif
