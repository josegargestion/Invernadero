/**
 * @brief Funciones de la capa de abstraccion de hardware
 * Esta libreria contiene las funciones referenes al hardware del sistema, para hacer
 * que el programa funcione sin teenr en cuenta factores como los pines de entrada
 * o la configuracion de sensores.
 * que lo mantiene entre el maximo y el minimo, vaciandolo o rellenandolo cuando sea preciso.
 *
 * @author Josegar1908@gmail.com
 * @version 0.5.0
 *
 * @todo	- Comprobación del sistema.
 * @copyright Copyright (c) 2021
 */
#include "configurations.h" // Guarda los datos por defecto del equipo.
#include "debug.h"          // Necesario para las llamadas de depuración.
#include "cAPPconfig.h"     // Guardado de datos a EEPROM.
#include "DHT.h"            // Control sensores DHT.
#include "Time.h"           // Control de horas y tiempos, ademas del rtc.
#include "CTiempos.h" // Personal de control de tiempos del procesador y horarios.
#include "hardware.h"       // Biblioteca de control de hardware.
#include "deposito.h"       // Control sistema de deposito de liquidos
#include <Arduino.h>        // STD de arduino.
#include "estructuras.h"    // Coleccion de estructuras comunes de proyecto.
#include <Wire.h>           // Biblioteca i2c standar.
const unsigned long DHT_TIEMPO_MEDIDAS = 10000;
estado_Hardware Hardware::estadoHardware;
config_Hardware Hardware::configHardware;
millis_set Hardware::hardwareMillis;
Hardware::Hardware() : sondaInterior(_HTINTPIN, _HTINTTYPE), sondaExterior(_HTEXTPIN, _HTEXTTYPE)
{
    hardwareMillis.currentmillis = 0;                              // Lectura actual de ejecucion.
    hardwareMillis.lastmillis = 0;                                 // Tiempo de la ultima ejecucion.
    hardwareMillis.period = _DEFECTO_PERIODO;                      // Lapso de tiempo entre ejecuciones, defecto _DEFECTO_PERIODO
    configHardware.pinControlBomba = _pinControlBomba;             // Asigna el pin de la bomba desde _BOMBA.
    configHardware.pinControlValvula = _pinControlValvula;         // Asigna el pin de la valvula desde _Valvula.
    configHardware.pinControlSondaMaximo = _pinControlSondaMaximo; // Asigna el pin del sensor de maximo desde _SONDAMAXIMO.
    configHardware.pinControlSondaMinimo = _pinControlSondaMinimo; // Asigna el pin del sensor de maximo desde _SONDAMINIMO.
    configHardware.pinInt = _HTINTPIN;                             // Pin del sensor interior.
    configHardware.typeInt = _HTINTTYPE;                           // Tipo de sensor interior.
    configHardware.pinExt = _HTEXTPIN;                             // Pin del sensor exterior.
    configHardware.typeExt = _HTEXTTYPE;                           // Tipo de sensor exterior.
    estadoHardware.TCalibracionBomba = _CalibracionBomba;          // Tiempo de calibrado de la bomba.
    estadoHardware.TCalibracionValvula = _CalibracionValvula;      // Tiempo de calibrado de la valvula de llenado.
    configHardware.pinControlLampara = _pinControlLampara;
    configHardware.pinControlCalefaccion = _pinControlCalefaccion;
    configHardware.pinControlHumidificador = _pinControlHumidificador;
    configHardware.pinControlDeshumidificador = _pinControlDeshumidificador;
    configHardware.pinControlExtractor = _pinControlExtractor;
    configHardware.pinControlImpulsor = _pinControlImpulsor;
#ifdef NANO
    estadoHardware.EstadoSensorMax = false; // Valor por defecto del sensor de maximo al arranque.
    estadoHardware.EstadoSensorMin = false; // Valor por defecto del sensor de minimo al arranque.
    estadoHardware.EstadoBomba = false;     // Estado por defecto de la bomba al arranque.
    estadoHardware.EstadoValvula = false;   // Estado por defecto de la valvula de llenado.
    estadoHardware.EstadoLampara = false;
#endif
#ifdef MC23008
    Adafruit_MCP23X08 mcpIn, mcpOut;
    estadoHardware.TCalibracionBomba = _CalibracionBomba;     // Tiempo de calibrado de la bomba.
    estadoHardware.TCalibracionValvula = _CalibracionValvula; // Tiempo de calibrado de la valvula de llenado.
#endif
}
void Hardware::begin()
{
    #ifdef RTC
    DPRINTLN(F(" Antes de cargar RTC"));
    setSyncProvider(RTC.get);
    if (timeStatus() != timeSet)
    {
        DPRINTLN(F(" Unable to sync with the RTC"));
    }
    else
    {
        DPRINTLN(F(" RTC has set the system time"));
    }
    #endif
    sondaInterior.begin();
    sondaExterior.begin();
#ifdef NANO
    DTIME;
    DPRINTLN(F(" Incializando Hardware NANO."));
    pinMode(configHardware.pinControlCalefaccion, OUTPUT);      // Pin de salida.
    pinMode(configHardware.pinControlHumidificador, OUTPUT);    // Pin de salida.
    pinMode(configHardware.pinControlDeshumidificador, OUTPUT); // Pin de salida.
    pinMode(configHardware.pinControlExtractor, OUTPUT);        // Pin de salida.
    pinMode(configHardware.pinControlImpulsor, OUTPUT);         // Pin de salida.
    pinMode(configHardware.pinControlSondaMaximo, INPUT);       // Pin de entrada.
    pinMode(configHardware.pinControlSondaMinimo, INPUT);       // Pin de Entrada.
    pinMode(configHardware.pinControlBomba, OUTPUT);            // Pin de salida.
    pinMode(configHardware.pinControlValvula, OUTPUT);          // Pin de salida.
    pinMode(configHardware.pinControlLampara, OUTPUT);
#endif
#ifdef S74HCXX

#endif
#ifdef MC23008
    Adafruit_MCP23X08 mcpIn, mcpOut;
    mcpIn.begin_I2C(_IO1_ADD);
    mcpOut.begin_I2C(_IO2_ADD);
    DTIME;
    DPRINTLN(F(" Incializando Hardware MC23008."));

    mcpOut.pinMode(configHardware.pinControlBomba, OUTPUT);            // Pin control Bomba.
    mcpOut.pinMode(configHardware.pinControlValvula, OUTPUT);          // Pin control Valvula.
    mcpOut.pinMode(configHardware.pinControlCalefaccion, OUTPUT);      // Pin control calefaccion.
    mcpOut.pinMode(configHardware.pinControlHumidificador, OUTPUT);    // Pin control Humidificador.
    mcpOut.pinMode(configHardware.pinControlDeshumidificador, OUTPUT); // Pin control DesHumidificador.
    mcpOut.pinMode(configHardware.pinControlExtractor, OUTPUT);        // Pin control extractor.
    mcpOut.pinMode(configHardware.pinControlImpulsor, OUTPUT);         // Pin control Impulsor.
    mcpIn.pinMode(configHardware.pinEstadoLampara, INPUT);             // Estado de la iluminacion.
    mcpIn.pinMode(configHardware.pinEstadoSondaMinimo, INPUT);         // Estado Sonda de Minimo.
    mcpIn.pinMode(configHardware.pinEstadoSondaMaximo, INPUT);         // Estado Sonda de Maximo.
    mcpIn.pinMode(configHardware.pinEstadoBomba, INPUT);               // Estado de la bomba.
    mcpIn.pinMode(configHardware.pinEstadoValvula, INPUT);             // Estado de la electrovalvula.
    mcpIn.pinMode(configHardware.pinEstadoExtractor, INPUT);           // Estado del extractor.
    mcpIn.pinMode(configHardware.pinEstadoDeshumidificador, INPUT);    // Estado del deshumidificador.
    mcpIn.pinMode(configHardware.pinEstadoHumidificador, INPUT);       // Estado del humidificador.
    mcpIn.pinMode(configHardware.pinEstadoCalefaccion, INPUT);         // Estado calefaccion.
    mcpIn.pinMode(configHardware.pinEstadoImpulsor, INPUT);            // Estado del impulsor.

    estadoHardware.EstadoCalefaccion = mcpIn.digitalRead(configHardware.pinEstadoCalefaccion);           // Estado calefaccion.
    estadoHardware.EstadoHumidificador = mcpIn.digitalRead(configHardware.pinEstadoHumidificador);       // Estado del humidificador.
    estadoHardware.EstadoDeshumidificador = mcpIn.digitalRead(configHardware.pinEstadoDeshumidificador); // Estado del deshumidificador.
    estadoHardware.EstadoExtractor = mcpIn.digitalRead(configHardware.pinEstadoExtractor);               // Estado del extractor.
    estadoHardware.EstadoImpulsor = mcpIn.digitalRead(configHardware.pinEstadoImpulsor);                 // Estado del impulsor.
    estadoHardware.EstadoLampara = mcpIn.digitalRead(configHardware.pinEstadoLampara);                   // Estado iluminacion.
    estadoHardware.EstadoSensorMax = mcpIn.digitalRead(configHardware.pinEstadoSondaMaximo);             // Estado Sonda de Maximo,
    estadoHardware.EstadoSensorMin = mcpIn.digitalRead(configHardware.pinEstadoSondaMinimo);             // Estado Sonda de Minimo.
    estadoHardware.EstadoBomba = mcpIn.digitalRead(configHardware.pinEstadoBomba);                       // Estado Bomba.
    estadoHardware.EstadoValvula = mcpIn.digitalRead(configHardware.pinEstadoValvula);                   // Estado Valvula.

    estadoHardware.TCalibracionBomba = _CalibracionBomba;     // Tiempo de calibrado de la bomba.
    estadoHardware.TCalibracionValvula = _CalibracionValvula; // Tiempo de calibrado de la valvula de llenado.
#endif
}
void Hardware::Control()
{
    DTIME;
    DPRINTLN(F(" Ejecutando Control de Hardware."));
}
bool Hardware::GetSondaMaximo()
{
#ifdef NANO
    estadoHardware.EstadoSensorMax = digitalRead(configHardware.pinControlSondaMaximo);
#endif
#ifdef S74HCXX

#endif
#ifdef DEBUG
    DTIME;
    DPRINT(" Sensor Max : ");
    DPRINT(estadoHardware.EstadoSensorMax);
    DPRINT(" PIN Sensor Max : ");
    DPRINT(configHardware.pinControlSondaMaximo);
    DPRINTLN();
#endif
    return estadoHardware.EstadoSensorMax;
}
bool Hardware::GetSondaMinimo()
{
#ifdef NANO
    estadoHardware.EstadoSensorMin = digitalRead(configHardware.pinControlSondaMinimo);
#endif
#ifdef S74HCXX

#endif
#ifdef DEBUG
    DTIME;
    DPRINT(" Sensor Min : ");
    DPRINT(estadoHardware.EstadoSensorMin);
    DPRINT(" PIN Sensor Min : ");
    DPRINT(configHardware.pinControlSondaMinimo);
    DPRINTLN();
#endif
    return estadoHardware.EstadoSensorMin;
}
void Hardware::UpdateSondas()
{
    GetSondaMaximo();
    GetSondaMinimo();
}
void Hardware::EncenderIluminacion()
{
#ifdef NANO
    digitalWrite(configHardware.pinControlLampara, HIGH);
    estadoHardware.EstadoLampara = true;
#endif
#ifdef S74HCXX

#endif
}
bool Hardware::GetEstadoIluminacion()
{
#ifdef NANO

#endif
#ifdef S74HCXX

#endif
    return estadoHardware.EstadoLampara;
}
void Hardware::ApagarIluminacion()
{
#ifdef NANO
    digitalWrite(configHardware.pinControlLampara, LOW);
    estadoHardware.EstadoLampara = false;
#endif
#ifdef S74HCXX

#endif
}
void Hardware::ApagarValvula()
{
#ifdef DEBUG
    DTIME;
    DPRINTLN(F(" LLE - Apagado de Valvula."));
#endif
#ifdef NANO
    digitalWrite(configHardware.pinControlValvula, LOW);
    estadoHardware.EstadoValvula = false;
#endif
#ifdef S74HCXX

#endif
}
void Hardware::EncenderValvula()
{
    DTIME;
    DPRINTLN(F(" LLE - Encendido de Valvula."));
#ifdef NANO
    digitalWrite(configHardware.pinControlValvula, HIGH);
    estadoHardware.EstadoValvula = true;
#endif
#ifdef S74HCXX

#endif
}
void Hardware::ApagarBomba()
{
    DTIME;
    DPRINTLN(F(" VAC - Apagado de bomba."));
#ifdef NANO
    digitalWrite(configHardware.pinControlBomba, LOW);
    estadoHardware.EstadoBomba = false;
#endif
#ifdef S74HCXX

#endif
}
void Hardware::EncenderBomba()
{
    DTIME;
    DPRINTLN(F(" VAC - Encendido de bomba."));
#ifdef NANO
    digitalWrite(configHardware.pinControlBomba, HIGH);
    estadoHardware.EstadoBomba = true;
#endif
#ifdef S74HCXX

#endif
}
unsigned long Hardware::GetCalibracionBomba()
{
    millis_set controlTime; // Control de tiempos de la calibracion.
    bool calibrado = false;
    unsigned long tiempoCalibracion = 0;
    bool fristrun = true;
    ApagarBomba();
    ApagarValvula();
    UpdateSondas();
    DTIME;
    DPRINTLN(F(" Iniciando calibracion de la bomba."));
    do // Rutina de calibracion de la bomba.
    {
        if (estadoHardware.EstadoSensorMax && estadoHardware.EstadoSensorMin)
        {
            DTIME;
            DPRINTLN(F(" 000 - Deposito lleno, calibrando."));
            do
            {
                if (fristrun)
                {
                    controlTime.lastmillis = millis();
                    DTIME;
                    DPRINT(F(" Primera ejecucion = "));
                    DPRINTLN(controlTime.lastmillis);
                    fristrun = false;
                }
                if (!estadoHardware.EstadoBomba)
                {
                    EncenderBomba();
                }
                UpdateSondas();
            } while (estadoHardware.EstadoSensorMin);
            if (!estadoHardware.EstadoSensorMin)
                controlTime.currentmillis = millis();
            tiempoCalibracion = controlTime.currentmillis - controlTime.lastmillis;
            calibrado = true;
        }
        else if (estadoHardware.EstadoSensorMax && !estadoHardware.EstadoSensorMin)
        {
            ControlErrorDeposito();
            UpdateSondas();
        }
        else if (!estadoHardware.EstadoSensorMax && estadoHardware.EstadoSensorMin)
        {
            /*do
            {
                controlTime.currentmillis = millis();
                DTIME;
                DPRINT(F(" Ultima ejecucion = "));
                DPRINTLN(controlTime.currentmillis);
                tiempoCalibracion = controlTime.currentmillis - controlTime.lastmillis;
            }*/
        }
        else if (!estadoHardware.EstadoSensorMax && estadoHardware.EstadoSensorMin)
        {
            DTIME;
            DPRINTLN(F(" 002 - Deposito vacio, llenando."));
            if (fristrun)
            {
                do
                {
                    if (estadoHardware.EstadoBomba)
                    {
                        ApagarBomba();
                    }
                    if (!estadoHardware.EstadoValvula)
                    {
                        EncenderValvula();
                    }
                    UpdateSondas();
                } while (!estadoHardware.EstadoSensorMax);
            }
        }
        else if (!estadoHardware.EstadoSensorMax && !estadoHardware.EstadoSensorMin)
        {
            DTIME;
            DPRINTLN(F(" 003 - Deposito vacio, llenando."));
            if (fristrun)
            {
                do
                {
                    if (estadoHardware.EstadoBomba)
                    {
                        ApagarBomba();
                    }
                    if (!estadoHardware.EstadoValvula)
                    {
                        EncenderValvula();
                    }
                    UpdateSondas();
                } while (!estadoHardware.EstadoSensorMax);
            }
        }
    } while (calibrado);
    return tiempoCalibracion;
}
unsigned long Hardware::GetCalibracionValvula()
{
    millis_set controlTime; // Control de tiempos de la calibracion.
    bool calibrado = false;
    unsigned long tiempoCalibracion = 0;
    bool fristrun = true;
    ApagarValvula();
    ApagarBomba();
    UpdateSondas();
    controlTime.currentmillis = millis();
    do // Rutina de calibracion de la valvula de llenado.
    {
        if (estadoHardware.EstadoSensorMax && estadoHardware.EstadoSensorMin)
        {
            DTIME;
            DPRINTLN(F(" 100 - Deposito lleno, calibrando."));
            do
            {
                if (fristrun)
                {
                    controlTime.lastmillis = millis();
                }
                EncenderBomba();
                UpdateSondas();
            } while (!estadoHardware.EstadoSensorMin);
            ApagarBomba();
            calibrado = true;
        }
        else if (estadoHardware.EstadoSensorMax && !estadoHardware.EstadoSensorMin)
        {
            /*
            DTIME;
            DPRINTLN(F(" 101 - Sensor de maximo activo y minimo inactivo, error de sonda."));
            ControlError();
            UpdateSondas();
            */
        }
        else if (!estadoHardware.EstadoSensorMax && estadoHardware.EstadoSensorMin)
        {
            /*
            DTIME;
            DPRINTLN(F(" 102 - En proceso de vaciado."));
            do
            {
                Vaciado(OFF);
                LLenado(ON);
                UpdateSondas();
            } while (!estadoHardware.SensorMin);
            */
        }
        else if (!estadoHardware.EstadoSensorMax && !estadoHardware.EstadoSensorMin)
        {
            /*
            DTIME;
            DPRINTLN(F(" 103 - Deposito vacio, llenando."));
            do
            {
                Vaciado(OFF);
                LLenado(ON);
                UpdateSondas();
            } while (estadoHardware.SensorMin);
            */
        }
    } while (calibrado);
    ApagarBomba();
    ApagarValvula();
    controlTime.currentmillis = millis();
    tiempoCalibracion = controlTime.currentmillis - controlTime.lastmillis;
    return tiempoCalibracion;
}
configData_t Hardware::SetCalibracion(configData_t configAPP)
{
    DTIME;
    DPRINTLN(F(" Iniciando calibracion. "));
    UpdateSondas();
    configAPP.TCalibracionBomba = GetCalibracionBomba();
    DTIME;
    DPRINT(F(" Tiempo calibracion bomba = "));
    DPRINTLN(configAPP.TCalibracionBomba);
    configAPP.CalBomba = true;
    configAPP.TCalibracionValvula = GetCalibracionValvula();
    DTIME;
    DPRINTLN(F(" Tiempo calibracion valvula = "));
    DPRINTLN(configAPP.TCalibracionValvula);
    configAPP.CalValvula = true;
    return configAPP;
}
void Hardware::ControlErrorDeposito()
{
    {
        millis_set controlTime;
        controlTime.lastmillis = 0;
        controlTime.period = 3000;
        controlTime.currentmillis = millis();
        if (controlTime.currentmillis - controlTime.lastmillis >= controlTime.period)
        {
            if (estadoHardware.EstadoSensorMax && !estadoHardware.EstadoSensorMin)
            {
                DTIME;
                DPRINTLN(F(" Apagando valvula."));
                ApagarValvula();
                do
                {
                    DTIME;
                    DPRINTLN(F(" Encendiendo bomba y comprobando nivel minimo."));
                    EncenderBomba();
                    UpdateSondas();
                    controlTime.lastmillis = millis();
                    if (controlTime.currentmillis - controlTime.lastmillis >= estadoHardware.TCalibracionBomba * 2)
                    {
                        DTIME;
                        DPRINTLN(F(" Superado tiempo maximo de bombeo."));
                        break;
                    }
                } while (estadoHardware.EstadoSensorMin);
            }
        }
    }
}
void Hardware::EncenderCalefaccion() {}
void Hardware::EncenderHumidificador() {}
void Hardware::EncenderDeshumidificador() {}
void Hardware::EncenderExtractor() {}
void Hardware::EncenderImpulsor() {}
void Hardware::ApagarCalefaccion() {}
void Hardware::ApagarHumidificador() {}
void Hardware::ApagarDeshumidificador() {}
void Hardware::ApagarExtractor() {}
void Hardware::ApagarImpulsor() {}
datos_sensores Hardware::GetSensor(DHT Sensor)
{
    datos_sensores AmbienteTemporal;
    millis_set sensorMillis;
    sensorMillis.lastmillis = 0;
    unsigned long periodoActual;
    periodoActual = DHT_TIEMPO_MEDIDAS;
    sensorMillis.currentmillis = millis();

    if (sensorMillis.currentmillis - sensorMillis.lastmillis >= periodoActual) // Ejecutar solo si han pasado mas de period.
    {
        AmbienteTemporal.temperatura = Sensor.readTemperature();
        AmbienteTemporal.humedad = Sensor.readHumidity();
    }
    sensorMillis.lastmillis = millis();
    return AmbienteTemporal;
}
void Hardware::GetSensores()
{
    Hardware::estadoHardware.AmbienteExterno = GetSensor(sondaExterior);
    Hardware::estadoHardware.AmbienteInterno = GetSensor(sondaInterior);
}
