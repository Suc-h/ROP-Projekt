#include <LiquidCrystal_I2C.h>
#include <SimpleRelay.h>
#include <SoftwareSerial.h>


#define RX 11
#define TX 10
SoftwareSerial bluetooth(TX, RX);
LiquidCrystal_I2C lcd(0x27, 20, 4);
constexpr static byte RELAY_PIN = 2;
SimpleRelay relay = SimpleRelay(RELAY_PIN);

#define INTERVAL 1000
byte led; 
unsigned long time_for_action;



int casovac;
int n;
bool cas;

void setup()
{


  casovac = 0;
  cas = false;
  n=0;
  
  pinMode(13, OUTPUT);
  
  bluetooth.begin(9600);
  bluetooth.println("Arduino zapnuto!");

  lcd.init();
  lcd.backlight();

  lcd.setCursor(4, 0);
  
  
  lcd.printstr("Vypnuto");
  relay.off();


  
}

void loop()
{

  n = 0;
  casovac = 0;
  cas = false;
  byte BluetoothData;

  


  if (bluetooth.available() > 0)
  {
    BluetoothData = bluetooth.read();

    switch (BluetoothData) {

      case '0':
        lcd.clear();
        relay.on();
        
        cas = true;
        casovac = 30;
        break;
        


      case '1':
        lcd.clear();
        relay.on();
        
        cas = true;
        casovac = 60;
        break;


      case 'a':
        relay.on();
        
        cas = true;
        casovac = 5;
        break;
    
    case 'b':
        relay.on();
        
        cas = true;
        casovac = 15;
        break;
    }
  }
 

 
  RelayOn();
}


  

void Casovac()
{
  if (millis() > time_for_action) {
    time_for_action = millis() + (unsigned long)INTERVAL;
    led = !led;
    digitalWrite(13, led);

    casovac--;

            if(casovac==9);
            {
              lcd.clear();
              lcd.setCursor(4, 0);
              lcd.printstr("Zapnuto");
              lcd.setCursor(7, 1);
            }
    lcd.print(casovac);
  }
 
 
  
  
}
void RelayOn()
{
 
 if (relay.isRelayOn())
  {
    
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.printstr("Zapnuto");

    if (cas)
    {
        casovac++;
        
     
      while (n < casovac)
      {
        
        lcd.setCursor(7, 1);
        Casovac();
        
      }

      relay.off();
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.printstr("Vypnuto");

    }
    else
    {
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.printstr("Vypnuto");
    }
}
}