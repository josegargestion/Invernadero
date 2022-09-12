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
#include "Debug.h"                                            // Necesario para las llamadas de depuración.
#include "estructuras.h"
#include <Arduino.h>                                          // STD de arduino.
set_Horario Control_Tiempos::SetTime(uint8_t Hora, uint8_t Minuto)
{
    set_Horario tmp;
    tmp.Hora = Hora;
    tmp.Minuto = Minuto;
    return tmp;
}
set_Ambiente Control_Tiempos::SetTime(uint8_t Hora, uint8_t Minuto, float Temp, float HR)
{
    set_Ambiente tmp;
    tmp.set = SetTime(Hora , Minuto);
    tmp.AmbienteHora.temperatura = Temp;
    tmp.AmbienteHora.humedad = HR;
    return tmp;
}
set_Ambiente Control_Tiempos::SetTime(uint8_t Hora, uint8_t Minuto, datos_sensores sensores)
{
    set_Ambiente tmp;
    tmp.set = SetTime(Hora, Minuto);
    tmp.AmbienteHora = sensores;
    return tmp;
}
void Control_Tiempos::SetTimeOn(uint8_t Hora, uint8_t Minuto) 
{
    setOn = SetTime(Hora, Minuto);
}
void Control_Tiempos::SetTimeOn(set_Horario set)
{
    setOn = set;
}
void Control_Tiempos::SetTimeOn(set_Ambiente setA)
{
    setAOn = setA;
}
void Control_Tiempos::SetTimeOff(uint8_t Hora, uint8_t Minuto)
{
    setOff = SetTime(Hora, Minuto);
}
void Control_Tiempos::SetTimeOff(set_Horario set)
{
    setOff = set;
}
void Control_Tiempos::SetTimeOff(set_Ambiente setA)
{
    setAOff = setA;
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
