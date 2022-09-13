# 1 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino"
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
# 11 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino"
# 12 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino" 2
# 13 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino" 2
# 14 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino" 2
# 15 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino" 2
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
# 32 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 32 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino"
   " 000 - Loop principal. "
# 32 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino" 3
   ); &__c[0];}))
# 32 "c:\\Users\\usuario\\Documents\\GitHub\\Inver\\Inver.ino"
   ))); };
    Inver1.Control();
    mainMillis.lastmillis = millis();
  }
}
