/**
 * @file invernadero.cpp
 * @brief Codigo de la biblioteca invernadero.h
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @version 0.5.0
 * @date 2022-06-23
 * @copyright Copyright (c) 2021
 */
#include "configurations.h" // Guarda los datos por defecto del equipo.
#include "Debug.h"          // Necesario para las llamadas de depuración.
#include "cAPPconfig.h"     // Guardado de datos a EEPROM.
#include "debug.h"          // Necesario para las llamadas de depuración.
#include "Time.h"           // Control de horas y tiempos, ademas del rtc.
#include "estructuras.h"    // Estructuras de datos.
#include "deposito.h"       // Control sistema de deposito de liquidos
#include "ambiente.h"       // Control del ambiente.
#include "Iluminacion.h"    // Control iluminación.
#include "invernadero.h"    // Clase maestra de control del sistema.
#include "hardware.h"       // Clase de control del hardware.
#include "CTiempos.h"       // Clase de control de horarios.
#include <Arduino.h>        // STD de arduino.
cAppConfig configApp1;
Control_Tiempos Horario1;
IHAL& Sistema1;
Ambiente Ambiente1;
Iluminacion Iluminacion1;
millis_set inverMillis;

Inver::Inver()
Inver::Inver(IHAL &_hal) : _hal(Sistema1)
{
}
void Inver::begin()
{
  Sistema1.begin();
  configApp1.begin();
  Iluminacion1.begin();
  Ambiente1.begin();
  Horario1.SetTimeOn(configApp1._D.OnHora, configApp1._D.OnMinuto);
  Horario1.SetTimeOff(configApp1._D.OffHora, configApp1._D.OffMinuto);
  // Ambiente1.SetTimeOn(configApp1._D.OnHora, configApp1._D.OnMinuto, configApp1._D.OnTemp, configApp1._D.OnHr);
  // Ambiente1.SetTimeOff(configApp1._D.OffHora, configApp1._D.OffMinuto, configApp1._D.OffTemp, configApp1._D.OffHr);
}
void Inver::Control()
{
  Sistema1.Control();
  Iluminacion1.Control();
  Ambiente1.Control();
}
