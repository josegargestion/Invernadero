/**
 * @file comms.cpp
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @brief Codigo de la biblioteca comms.h
 * @version 0.0.3
 * @date 2021-11-22
 *
 * @copyright Copyright (c) 2021
 * @todo Definir las estructuras de control para el paso de informacion entre el microcontrolador y la interfaz de control.
 */
#include <Arduino.h>		// STD de arduino.
#include "configurations.h" // Guarda los datos por defecto del equipo.
#include "Debug.h"          // Necesario para las llamadas de depuración.
#include "Time.h"           // Control de horas y tiempos, ademas del rtc.
#include "CTiempos.h" // Personal de control de tiempos del procesador y horarios.
