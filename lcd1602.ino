#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include <time.h>

LiquidCrystal_I2C lcd(0x27,20,4);

RTC_DS1307 rtc;

int timetable[2][5] = {
  {13, 13, 13, 13, 13},
  {26, 27, 28, 29, 30}
};

void setup()
{
  lcd.init();
  Serial.begin(115200);

  if(!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
}

void loop()
{
  DateTime now = rtc.now();

  if(now.second() == 0)
  {
    for(int i = 0; i < 5; i++)
    {
      if(now.hour() == timetable[0][i])
      {
        if(now.minute() == timetable[1][i])
        {
          alarm();
        }
      }
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());

  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  lcd.print(now.day());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.year());

  delay(1000);
  lcd.clear();
}

void alarm()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("****Alarming****");
  lcd.setCursor(0, 1);
  lcd.print("****Alarming****");
  digitalWrite(13, HIGH);
  delay(5000);
  digitalWrite(13, LOW);
}