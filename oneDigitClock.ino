#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ButtonDebounce.h>
#include <RTClib.h>
byte lcdRows = 4;
byte lcdColumns = 16;

LiquidCrystal_I2C lcd(0x20, lcdColumns, lcdRows); // set the LCD address to 0x27 for a 16 chars and 2 line display
RTC_DS1307 RTC;
//////////////////Pins///////////
uint8_t hourupg = 0;
uint8_t  minupg = 0;
uint8_t  yearupg = 0;
uint8_t  monthupg = 0;
uint8_t  dayupg = 0;
uint8_t  amPm = 0; //0 = AM,1 = PM
const uint8_t menuKeyPin = 4;
const uint8_t menuKeyStepUp = 5;
const uint8_t menuKeyStepDown = 6;
const uint8_t led = 2;
ButtonDebounce Menubtn(menuKeyPin, 100);
ButtonDebounce MenuStepUp(menuKeyStepUp, 100);
ButtonDebounce MenuStepDown(menuKeyStepDown, 100);

bool flag = false;
bool session = false;
uint8_t menuLevel = 0;
uint8_t menu =0;
byte hourSetting = 24;

void clearLCD(int row);
void updateButton();
unsigned long prev = 0;
int  interval = 300;

void setup()
{
  Serial.begin(9600);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  
  pinMode(led, OUTPUT);
  //digitalWrite(led, HIGH);
  //delay(1000);
 // digitalWrite(led, LOW);
  lcd.print("=====Welcome====");
  prev= millis();
}

void loop()
{
  updateButton();

if(Menubtn.state() == HIGH)
{
  delay(10);
  updateButton();
  
 if(Menubtn.state() == LOW)
 {

Serial.print("menu");Serial.println(menu);

  if(menu < 7)
  {

    menu++;
  }else
  {

    menu=0;
  }



 }




}


switch(menu)
{
  case 0:break;//displaytime
  case 1:DisplayHourSetting();break;
  case 2:DisplaySetHour();break;
  default: break;

}




}





  


void updateButton()
{

  Menubtn.update();
  MenuStepUp.update();
  MenuStepDown.update();
}

void DisplayHourSetting()
{

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Settings");
lcd.setCursor(0, 1);
if (hourSetting == 24)lcd.print("Hour setting:24H");      
else {lcd.print("Hour setting:12H");}
bool hsFlag = true;

while (hsFlag)
      {
        updateButton();
        if(Menubtn.state() == HIGH)
        {
          
        delay(10);
        updateButton();
            if(Menubtn.state() == LOW)
            {
              hsFlag = false;
              Serial.println("hsFlag false");
              menu =2;
              Serial.print("menu:");Serial.println(menu);
              welcomeMsgLcd();

            }

        }
        
        
        if (MenuStepUp.state() == HIGH)
        {
          delay(10);
          updateButton();
         
          if (MenuStepUp.state() == LOW)
          {

            Serial.println("clicked");
            lcd.setCursor(0, 1);
            if (hourSetting == 24)
            {
              lcd.print("Hour setting:12H");
              hourSetting = 12;
            }
            else
            {
              lcd.print("Hour setting:24H");
              hourSetting = 24;
            }
          }
        }
      }
        




}
void clearLCD(int row)
{
  lcd.setCursor(0, row);

  for (int i = 0; i < lcdColumns; i++)
  {
    lcd.setCursor(i, row);
    lcd.print(" ");
  }
  lcd.setCursor(0, row);
}
void DisplaySetHour()
{
  lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Settings");
  
  lcd.setCursor(0, 1);

  lcd.print("Set hour:");lcd.print(hourupg);

  bool hFlag= true;

 

  while (hFlag)
  {
    updateButton();

    if(Menubtn.state() == HIGH)
    {
        delay(10);
        updateButton();
        if(Menubtn.state() == LOW)
        {
          
          hFlag= false;
          
        }

    }



    if (MenuStepUp.state() == HIGH)
    {
      delay(10);
      updateButton();
      if (MenuStepUp.state() == LOW)
      {
        
      Serial.println("step up clicked hour");
      if (hourSetting ==  24 )
      {

            if (hourupg >= 23)
      {
        hourupg = 0;
      }
      else
      {
        hourupg = hourupg + 1;
      }
      }
      else
      {
      if (hourupg >= 12)
      {
        hourupg = 1;
      }
      else
      {
        hourupg = hourupg + 1;
      }

      }
      clearLCD(1);
      lcd.setCursor(0,1);
      lcd.print("Set hour:");lcd.print(hourupg);

      }
      
    }

    if (MenuStepDown.state() == HIGH)
    {
       delay(10);
      updateButton();
      if (MenuStepDown.state() == LOW)
      {
          Serial.println("clicked hour Down");
      if (hourSetting == 24)
      {
        if (hourupg == 0)
      {
        hourupg = 23;
      }
      else
      {
        hourupg = hourupg - 1;
      }
      }
      else
      {
        if (hourupg == 1)
      {
        hourupg = 12;
      }
      else
      {
        hourupg = hourupg - 1;
      }
      }
      clearLCD(1);
      lcd.setCursor(0,1);
      lcd.print("Set hour:");lcd.print(hourupg);


      }
      
    }

    

    
  
  
  }


  if(hourSetting == 12)
  {
    clearLCD(1);
    lcd.setCursor(0,1);
    lcd.print("Set (AM/PM):");(amPm)?lcd.print("AM"):lcd.print("PM");
    updateButton();
   
   bool amPmFlag = true;

    while (amPmFlag)
    {
      
      updateButton();

      if (Menubtn.state() == HIGH)
        {
            delay(10);
            updateButton();
            if (Menubtn.state() == LOW)
            {
              Serial.println("clicked menu button inside am pm ");
              amPmFlag = false;
              menu = 3;
              welcomeMsgLcd();
              

            }
        }
                  
            
            
      if (MenuStepUp.state() == HIGH)
            {
                delay(10);
                updateButton();
                if (MenuStepUp.state() == LOW )
                {
                    clearLCD(1);
                    lcd.setCursor(0,1);
                    if(amPm == 1)amPm=0;else{amPm = 1;}
                    Serial.print("amapm");Serial.println(amPm);
                    lcd.print("Set (AM/PM):");(amPm)?lcd.print("AM"):lcd.print("PM");
                }
                
              
            }
     
  

      }

    }else
    {

      menu = 3;
      welcomeMsgLcd();
    }

    
    
   
   
   

  }




void welcomeMsgLcd()
{

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("=====Welcome====");

}

void DisplaySetMinute()
{

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Settings");
lcd.setCursor(0, 1);
lcd.print("Set minutes:"); lcd.print(minupg);     
else {lcd.print("Hour setting:12H");}
bool hsFlag = true;

while (hsFlag)
      {
        updateButton();
        if(Menubtn.state() == HIGH)
        {
          
        delay(10);
        updateButton();
            if(Menubtn.state() == LOW)
            {
              hsFlag = false;
              Serial.println("hsFlag false");
              menu =2;
              Serial.print("menu:");Serial.println(menu);
              welcomeMsgLcd();

            }

        }
        
        
        if (MenuStepUp.state() == HIGH)
        {
          delay(10);
          updateButton();
         
          if (MenuStepUp.state() == LOW)
          {

            Serial.println("clicked");
            lcd.setCursor(0, 1);
            if (hourSetting == 24)
            {
              lcd.print("Hour setting:12H");
              hourSetting = 12;
            }
            else
            {
              lcd.print("Hour setting:24H");
              hourSetting = 24;
            }
          }
        }
      }
        



}


/*
void DisplaySetYear()
{
  // setting the year
  lcd.clear();
  if (digitalRead(P2) == HIGH)
  {
    yearupg = yearupg + 1;
  }
  if (digitalRead(P3) == HIGH)
  {
    yearupg = yearupg - 1;
  }

  lcd.setCursor(0, 0);
  lcd.print("Set Year:");
  lcd.setCursor(0, 1);
  lcd.print(yearupg, DEC);
  delay(200);
}

void DisplaySetMonth()
{
  // Setting the month
  lcd.clear();
  if (digitalRead(P2) == HIGH)
  {
    if (monthupg == 12)
    {
      monthupg = 1;
    }
    else
    {
      monthupg = monthupg + 1;
    }
  }
  if (digitalRead(P3) == HIGH)
  {
    if (monthupg == 1)
    {
      monthupg = 12;
    }
    else
    {
      monthupg = monthupg - 1;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Set Month:");
  lcd.setCursor(0, 1);
  lcd.print(monthupg, DEC);
  delay(200);
}

void DisplaySetDay()
{
  // Setting the day
  lcd.clear();
  if (digitalRead(P2) == HIGH)
  {
    if (dayupg == 31)
    {
      dayupg = 1;
    }
    else
    {
      dayupg = dayupg + 1;
    }
  }
  if (digitalRead(P3) == HIGH)
  {
    if (dayupg == 1)
    {
      dayupg = 31;
    }
    else
    {
      dayupg = dayupg - 1;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Set Day:");
  lcd.setCursor(0, 1);
  lcd.print(dayupg, DEC);
  delay(200);
}
*/

