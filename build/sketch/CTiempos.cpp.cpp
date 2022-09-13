##line 18 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino"
void setup();
#line 27 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino"
void loop();
#line 0 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino"
line 1 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp"
/**
 * @file ControlTiempos.cpp
 * @brief Codigo de la biblioteca de control de tiempos de ejecucion y operaciones de encendido apagado
 *
 * @author Jose Luis Garcia Lopez (josegar1980@gmail.com)
 * @version 0.5.0
 * @date 2022-06-23
 * @copyright Copyright (c) 2021
 *
 */

#include "CTiempos.h"                                   // Personal de control de tiempos del procesador y horarios.
#include "configurations.h"                                   // Guarda los datos por defecto del equipo.
#include <Time.h>                                             // Libreria de control de tiempos.
#include "DHT.h"                                              // Control sensores DHT.
#include "Debug.h"                                            // Necesario para las llamadas de depuración.
#include <Arduino.h>                                          // STD de arduino.
void Control_Tiempos::SetTimeOn(uint8_t Hora, uint8_t Minuto) // Configura tiempo de encendido.
{
    setOn.Hora = Hora;
    setOn.Minuto = Minuto;
}
void Control_Tiempos::SetTimeOn(uint8_t Hora, uint8_t Minuto, set_Horario set) // Configura tiempo de encendido.
{
    set.Hora = Hora;
    set.Minuto = Minuto;
}
void Control_Tiempos::SetTimeOn(uint8_t Hora, uint8_t Minuto, set_Ambiente set) // Configura tiempo de encendido.
{
    /** @todo corregir esto
    SetTimeOn(Hora, Minuto, setOn.set);
    setOn. = Temp;
    setOn.Hr = Hr;
    **/
}
void Control_Tiempos::SetTimeOff(uint8_t Hora, uint8_t Minuto) // Configura el tiempo de apagado.
{
    setOff.Hora = Hora;
    setOff.Minuto = Minuto;
}
void Control_Tiempos::SetTimeOff(uint8_t Hora, uint8_t Minuto, set_Horario set) // Configura el tiempo de apagado.
{
    set.Hora = Hora;
    set.Minuto = Minuto;
}
void Control_Tiempos::SetTimeOff(uint8_t Hora, uint8_t Minuto, set_Ambiente set) // Configura el tiempo de apagado.
{
    /** @todo corregir esto
    SetTimeOff(Hora, Minuto, setOn.set);
    setOff.Temp = Temp;
    setOff.Hr = Hr;
    **/
}
bool Control_Tiempos::ControlOnOff(set_Horario setOn, set_Horario setOff)
{
    bool control_return = false;
    setAOn.set.Hora = setOn.Hora;
    setAOn.set.Minuto = setOn.Minuto;
    setAOff.set.Hora = setOff.Hora;
    setAOff.set.Minuto = setOff.Minuto;
    control_return = ControlOnOff(setAOn, setAOff);
    return control_return;
}
bool Control_Tiempos::ControlOnOff(set_Ambiente setAOn, set_Ambiente setAOff)
{
    time_t t = now();
    bool control_return = false;
    if (setAOn.set.Hora < setAOff.set.Hora) // Si la hora de encendido esta antes de la de apagado.
    {
        if (((int)setAOn.set.Hora == hour(t)) && ((int)setAOn.set.Minuto > minute(t))) // Apagado.
        {
            control_return = false;
        }
        else if (((int)setAOn.set.Hora == hour(t)) && ((int)setAOn.set.Minuto <= minute(t))) // Encendido.
        {
            control_return = true;
        }
        else if (((int)setAOff.set.Hora == hour(t)) && ((int)setAOff.set.Minuto < minute(t))) //  Encendido.
        {
            control_return = true;
        }
        else if (((int)setAOff.set.Hora == hour(t)) && ((int)setAOff.set.Minuto >= minute(t))) // Apagado.
        {
            control_return = false;
        }
        else if (((int)setAOff.set.Hora > hour(t)) && ((int)setAOn.set.Hora > hour(t))) // Apagado.
        {
            control_return = false;
        }
        else if (((int)setAOff.set.Hora < hour(t)) && ((int)setAOn.set.Hora > hour(t))) // Encendido.
        {
            control_return = true;
        }
        else if (((int)setAOff.set.Hora < hour(t)) && ((int)setAOn.set.Hora < hour(t))) // Apagado.
        {
            control_return = false;
        }
        else if (((int)setAOff.set.Hora > hour(t)) && ((int)setAOn.set.Hora < hour(t))) // Encendido.
        {
            control_return = true;
        }
        else // Si todo falla.
        {
            DTIME;
            DPRINTLN(F(" ECT - 001 No ha caido en las otras condiciones. "));
        }
    }
    else if (setAOn.set.Hora > setAOff.set.Hora) // Si la hora de encendido esta despues de la de apagado.
    {
        if (((int)setAOn.set.Hora == hour(t)) && ((int)setAOn.set.Minuto < minute(t))) // Encendido.
        {
            control_return = true;
        }
        else if (((int)setAOn.set.Hora == hour(t)) && ((int)setAOn.set.Minuto >= minute(t))) // Apagado.
        {
            control_return = false;
        }
        else if (((int)setAOff.set.Hora > hour(t)) && ((int)setAOn.set.Hora > hour(t))) // Encendido.
        {
            control_return = true;
        }
        else if (((int)setAOff.set.Hora == hour(t)) && ((int)setAOff.set.Minuto <= minute(t))) // Apagado.
        {
            control_return = false;
        }
        else if (((int)setAOff.set.Hora == hour(t)) && ((int)setAOff.set.Minuto > minute(t))) // Encendido.
        {
            control_return = true;
        }
        else if (((int)setAOff.set.Hora < hour(t)) && ((int)setAOn.set.Hora > hour(t))) // Apagado.
        {
            control_return = false;
        }
        else if (((int)setAOff.set.Hora < hour(t)) && ((int)setAOn.set.Hora < hour(t))) // Encendido.
        {
            control_return = true;
        }
        else // Si todo falla.
        {
            DTIME;
            DPRINTLN(F(" ECT - 002 No ha caido en las otras condiciones. "));
        }
    }
    return control_return;
}

#line 1 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino"
/**
 * @file inver.ino
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 **/
#include "Debug.h"       // Biblioteca de macros de errores.
#include "estructuras.h" // Personal de control de tiempos del procesador y horarios.
#include "invernadero.h" // Clase maestra de control del sistema.
#include <Arduino.h>     // STD de arduino.
Inver Inver1;
millis_set mainMillis;

void setup()
{
  mainMillis.currentmillis = millis();
  mainMillis.period = 1000;
  mainMillis.lastmillis = 0;
  Serial.begin(19200);
  Inver1.begin();
}

void loop()
{
  mainMillis.currentmillis = millis();
  if (mainMillis.currentmillis - mainMillis.lastmillis >= mainMillis.period)
  {
    DPRINTLN(F(" 000 - Loop principal. "));
    Inver1.Control();
    mainMillis.lastmillis = millis();
  }
}

