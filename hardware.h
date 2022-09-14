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
#include "deposito.h"		// Control de deposito.
class Hardware : public IHAL
{
public:
	struct estado_Hardware
	{
		IHAL_DATA _HAL_DATA;	/// Capa de abstraccion de la interfaz.
		Estado_HAL_Deposito _estadoDeposito; /// Capa de abstracción de la interfaz.
		bool EstadoLampara;
		bool EstadoSensorMax;			   // Estado sensor de maximo.
		bool EstadoSensorMin;			   // Estado sensor de minimo.
		bool EstadoBomba;				   // Estado de la bomba.
		bool EstadoValvula;				   // Estado de la electrovalvula.
		bool EstadoCalefaccion;			   // Estado calefaccion.
		bool EstadoHumidificador;		   // Estado del humidificador.
		bool EstadoDeshumidificador;	   // Estado del deshumidificador.
		bool EstadoExtractor;			   // Estado del extractor.
		bool EstadoImpulsor;			   // Estado del impulsor.
		bool CalValvula;				   // Calibracion realizada.
		bool CalBomba;					   // Calibracion realizada.
		unsigned long TCalibracionBomba;   // Tiempo de calibracion de la bomba.
		unsigned long TCalibracionValvula; // Tiempo de calibracion de la valvula.
		datos_sensores AmbienteInterno;
		datos_sensores AmbienteExterno;
	};
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
	IHAL_DATA GetEstado();
	bool SetEstado(IHAL_DATA set);
	void Control();
	bool GetIluminacion();
	void SetIluminacion(bool set);
	void ControlIluminacion();
	void GetTemperatura();
	void SetTemperatura();
	void ControlTemperatura();
	void GetHumedadAire();
	void SetHumedadAire();
	void ControlHumedadAire();
	void GetHumedadTierra();
	void SetHumedadTierra();
	void ControlHumedadTierra();
	/**
	 * @brief Gestion automatica de la iluminación, para controlar desde la aplicacion principal.
	 *
	 */
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
	IDeposito &_deposito;
	void LLenarDeposito();
	void VaciarDeposito();
	void GetDeposito(Estado_HAL_Deposito *PestadoDeposito);
	Estado_HAL_Deposito UpdateEstado();

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
