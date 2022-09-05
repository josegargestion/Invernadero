#include "Arduino.h" //incluimos de nuevo la librería Arduino.h
#include "AutoTime.h" //incluimos el fichero AutoTimer.h
 
    AutoTimer::AutoTimer(void(*f)(void), unsigned long d) //Constructor
    {
      inicialWait = false;
      lastUpdate = millis();
      funcion = f;
      delayTime = d;  
    }
 
    AutoTimer::AutoTimer(void(*f)(void), unsigned long d, boolean iW) //Constructor opción 2
    {
      inicialWait = iW;
      funcion = f;
      delayTime = d;
      if(inicialWait)
      {
        lastUpdate = delayTime + millis();
      }
      else
      {
       lastUpdate = millis(); 
      }
    }
 
    boolean AutoTimer::evaluate(){
      if(lastUpdate > millis()) //Esto es en caso de que ocurra un desbordamiento de la función millis
      {
        lastUpdate = millis();
      }
       
      if(millis() - lastUpdate >= delayTime){
        (*funcion)();
        lastUpdate = millis();
        return true;
      }
 
      return false;
    }
 
    boolean AutoTimer::setDelayTime(unsigned long d){
      delayTime = d;
      return true;
    }
 
    unsigned long AutoTimer::getDelayTime(){
      return delayTime;
    }