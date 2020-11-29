#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ButtonDebounce.h>

LiquidCrystal_I2C lcd(0x27,16,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//////////////////Pins///////////

const byte menuKeyPin =  4;
const byte menuKeyStepUp =  5;
const byte menuKeyStepDown =  6;
const byte led = 2;
ButtonDebounce Menubtn(menuKeyPin, 250);
ButtonDebounce MenuStepUp(menuKeyStepUp, 250);
ButtonDebounce MenuStepDown(menuKeyStepDown, 250);

bool flag = false;
void setup()
{
    Serial.begin(9600);
    lcd.init();                      // initialize the lcd 
    lcd.backlight();
    
    lcd.setCursor(3,0);
    lcd.print("Hello, VS");

   
    pinMode(led, OUTPUT);
 
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
}

void loop()
{
  updateButton();

  if(Menubtn.state() == HIGH)
  {
      if(flag)flag= false;else{flag= true;}
    Serial.println("Clicked menu");
    
  }

  
  if(MenuStepUp.state() == HIGH)
  {
       if(flag)flag= false;else{flag= true;}
    Serial.println("Clicked menuUp");
  }

  if(MenuStepDown.state() == HIGH)
  {
       if(flag)flag= false;else{flag= true;}
    Serial.println("Clicked menuDown");
  }

  
}

void updateButton()
{

  Menubtn.update();
    MenuStepUp.update();
    MenuStepDown.update();

}