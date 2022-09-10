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
Hardware Sistema1;
#ifndef NODEPOSITO
Deposito Deposito1;
#endif
Ambiente Ambiente1;
Iluminacion Iluminacion1;
millis_set inverMillis;
Inver::Inver()
{
}
void Inver::begin()
{
  Sistema1.begin();
  configApp1.begin();
  Iluminacion1.begin();
  Ambiente1.begin();
  #ifndef NODEPOSITO
  Deposito1.begin();
  #endif
  Horario1.SetTimeOn(configApp1._D.OnHora, configApp1._D.OnMinuto);
  Horario1.SetTimeOff(configApp1._D.OffHora, configApp1._D.OffMinuto);
  // Ambiente1.SetTimeOn(configApp1._D.OnHora, configApp1._D.OnMinuto, configApp1._D.OnTemp, configApp1._D.OnHr);
  // Ambiente1.SetTimeOff(configApp1._D.OffHora, configApp1._D.OffMinuto, configApp1._D.OffTemp, configApp1._D.OffHr);
#ifdef DEBUG
#ifndef NODEPOSITO
  configApp1._D.CalBomba = true;
  configApp1._D.CalValvula = true;
#endif
#endif
#ifndef NODEPOSITO
  if (configApp1._D.CalBomba && configApp1._D.CalValvula)
  {
    DTIME;
    DPRINTLN(F(" Cargando calibracion desde EEPROM."));
    Sistema1.estadoHardware.CalBomba = configApp1._D.CalBomba;
    Sistema1.estadoHardware.CalValvula = configApp1._D.CalValvula;
    Sistema1.estadoHardware.TCalibracionBomba = configApp1._D.TCalibracionBomba;
    Sistema1.estadoHardware.TCalibracionValvula = configApp1._D.TCalibracionValvula;
  }
  else
  {
    DTIME;
    DPRINTLN(F(" Generando nueva calibracion."));
    configData_t tempconfig;
    tempconfig = Sistema1.SetCalibracion(configApp1._D);
    configApp1._D = tempconfig;
    DTIME;
    DPRINTLN(F(" Guardando calibracion en EEPROM."));
    configApp1.configSave();
  }
  #endif
}
void Inver::Control()
{
  Sistema1.Control();
  Iluminacion1.Control();
  Ambiente1.Control();
  #ifndef NODEPOSITO
  Deposito1.Control();
  #endif
}
