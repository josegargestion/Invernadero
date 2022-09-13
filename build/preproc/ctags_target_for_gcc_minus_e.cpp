# 1 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp"
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
# 12 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp"
# 13 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 2
# 14 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 2
# 15 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 2
# 16 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 2
# 17 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 2
# 18 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 2
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
# 35 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp"
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
# 53 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp"
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
            { hora_detalle(); };
            { Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 105 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 3
           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 105 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp"
           " ECT - 001 No ha caido en las otras condiciones. "
# 105 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 3
           ); &__c[0];}))
# 105 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp"
           ))); };
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
            { hora_detalle(); };
            { Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 141 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 3
           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 141 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp"
           " ECT - 002 No ha caido en las otras condiciones. "
# 141 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp" 3
           ); &__c[0];}))
# 141 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\CTiempos.cpp"
           ))); };
        }
    }
    return control_return;
}
# 1 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino"
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
# 11 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino"
# 12 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino" 2
# 13 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino" 2
# 14 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino" 2
# 15 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino" 2
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
    { Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 32 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 32 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino"
   " 000 - Loop principal. "
# 32 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino" 3
   ); &__c[0];}))
# 32 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\inver.ino"
   ))); };
    Inver1.Control();
    mainMillis.lastmillis = millis();
  }
}
