#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ButtonDebounce.h>
#include <RTClib.h>
byte lcdRows = 4;
byte lcdColumns = 16;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); // set the LCD address to 0x27 for a 16 chars and 2 line display
RTC_DS1307 RTC;
//////////////////Pins///////////
uint8_t hourupg = 0;
uint8_t  minupg = 0;
uint16_t  yearupg = 0;
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


uint8_t menu =0;
byte hourSetting = 24;

void clearLCD(int row);
void updateButton();


void setup()
{
  Serial.begin(9600);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(1000);
 digitalWrite(led, LOW);
  lcd.print("=====Welcome====");
  
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
  case 3:DisplaySetMinute();break;
  case 4:DisplaySetYear();break;
  case 5:DisplaySetMonth();break;
  case 6:DisplaySetDay();break;
  
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

bool minFlag = true;

while (minFlag)
      {
        updateButton();
        if(Menubtn.state() == HIGH)
        {
          
        delay(10);
        updateButton();
            if(Menubtn.state() == LOW)
            {
              minFlag = false;
              Serial.println("minFlag false inside disp minute");
              menu =4;
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

            if(minupg > 59 )minupg = 59;
            else{minupg++;}
            Serial.println("clicked min up");
            clearLCD(1);
            lcd.setCursor(0, 1);
            lcd.print("Set minutes:"); lcd.print(minupg);   
          }
        }
      
      
      if (MenuStepDown.state() == HIGH)
        {
          delay(10);
          updateButton();
         
          if (MenuStepDown.state() == LOW)
          {

            if(minupg < 1 )minupg = 0;
            else{minupg--;}
            Serial.println("clicked min down");
            clearLCD(1);
            lcd.setCursor(0, 1);
            lcd.print("Set minutes:"); lcd.print(minupg);   
          }
        }
      
      
      }
        



}

void DisplaySetYear()
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Settings");
lcd.setCursor(0, 1);
lcd.print("Set Year:"); lcd.print(yearupg);     

bool yearFlag = true;

while (yearFlag)
      {
        updateButton();
        if(Menubtn.state() == HIGH)
        {
          
        delay(10);
        updateButton();
            if(Menubtn.state() == LOW)
            {
              yearFlag = false;
              Serial.println("yearFlagFlag false inside disp year");
              menu = 5;
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
            yearupg++;  
            Serial.println("clicked year up");
            clearLCD(1);
            lcd.setCursor(0, 1);
            lcd.print("Set Year:"); lcd.print(yearupg);    
          }
        }
      
      
      if (MenuStepDown.state() == HIGH)
        {
          delay(10);
          updateButton();
         
          if (MenuStepDown.state() == LOW)
          {
            
            if(yearupg < 2000) yearupg =2000;
            else{yearupg--;}
            Serial.println("clicked year down");
            clearLCD(1);
            lcd.setCursor(0, 1);
            lcd.print("Set Year:"); lcd.print(yearupg);   
          }
        }
      
      
      }
        



}

void DisplaySetMonth()
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Settings");
lcd.setCursor(0, 1);
lcd.print("Set Month:"); lcd.print(monthupg);     

bool monthFlag = true;

while (monthFlag)
      {
        updateButton();
        if(Menubtn.state() == HIGH)
        {
          
        delay(10);
        updateButton();
            if(Menubtn.state() == LOW)
            {
              monthFlag = false;
              Serial.println("monthFlag false inside disp month");
              menu = 6;
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
            if(monthupg >12)monthupg =12;
            else{monthupg++; } 
            Serial.println("clicked month up");
            clearLCD(1);
            lcd.setCursor(0, 1);
            lcd.print("Set month:"); lcd.print(monthupg);    
          }
        }
      
      
      if (MenuStepDown.state() == HIGH)
        {
          delay(10);
          updateButton();
         
          if (MenuStepDown.state() == LOW)
          {
            
            if(monthupg < 1) monthupg =1;
            else{monthupg--;}
            Serial.println("clicked year down");
            clearLCD(1);
            lcd.setCursor(0, 1);
            lcd.print("Set month:"); lcd.print(monthupg);   
          }
        }
      
      
      }
        


}

void DisplaySetDay()
{
  lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Settings");
lcd.setCursor(0, 1);
lcd.print("Set Date:"); lcd.print(dayupg);     

bool dayFlag = true;

while (dayFlag )
      {
        updateButton();
        if(Menubtn.state() == HIGH)
        {
          
        delay(10);
        updateButton();
            if(Menubtn.state() == LOW)
            {
              dayFlag = false;
              Serial.println("dayFlag false inside disp day");
              menu = 7;
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
            if(dayupg >31)dayupg =31;
            else{dayupg++; } 
            Serial.println("clicked day up");
            clearLCD(1);
            lcd.setCursor(0, 1);
            lcd.print("Set Date:"); lcd.print(dayupg);    
          }
        }
      
      
      if (MenuStepDown.state() == HIGH)
        {
          delay(10);
          updateButton();
         
          if (MenuStepDown.state() == LOW)
          {
            
            if(dayupg < 2) dayupg =1;
            else{dayupg--;}
            Serial.println("clicked year down");
            clearLCD(1);
            lcd.setCursor(0, 1);
            lcd.print("Set Date:"); lcd.print(dayupg);  
          }
        }
      
      
      }
        


}


