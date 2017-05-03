// Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

// Dallas DS18B20 temp sensor
#define ONE_WIRE_BUS 2 
OneWire oneWire(2); 
DallasTemperature sensors(&oneWire);
DeviceAddress sensorDeviceAddress;

// LCD (check your i2c address, mine is 0x3F)
LiquidCrystal_I2C lcd(0x3F,16,2);

// Temperature
int DS = 2;
float rttemp;
float targettemp = 30.00; // Set a default target temperature
float oldtemp = 20.00; // Keep the last measure in mind to know, by comparison, if temperature increase or decrease

// Relay
int relay = 3;

// Buttons
int b1_minus = 4; 
int b2_plus = 9;

// Buffers
// Put here your buffers, down and up (to avoid inertia of your build)
float buffup = 0.15;
float buffdown = 0.10;

void setup() {
  // Serial
  Serial.begin(9600); 
  
  // Sensor setup
  sensors.getAddress(sensorDeviceAddress, 0);
  sensors.setResolution(sensorDeviceAddress, 12);
  
  // LCD setup
  lcd.begin();
  lcd.backlight(); 
  lcd.setCursor(0, 0);
  lcd.print("-#-INCUBATOR-#-");
  lcd.setCursor(0, 1);
  lcd.print("Default = 30C");
  // Buttons and relay setup
  pinMode(b1_minus,INPUT_PULLUP);
  pinMode(b2_plus,INPUT_PULLUP);
  pinMode(relay,OUTPUT);
  delay(2000);
}

void loop() {
  if(digitalRead(b1_minus)== 0){targettemp = targettemp-0.5;} // Button -0.5
  if(digitalRead (b2_plus) == 0){targettemp = targettemp+0.5;} // Button +0.5

  Serial.print("Minus = ");
  Serial.println(digitalRead(b1_minus));

  Serial.print("Plus = ");
  Serial.println(digitalRead(b2_plus));
  
  lcd.clear();
  lcd.setCursor (0,1);
  lcd.print ("Temp : ");
  sensors.requestTemperatures();
  rttemp = sensors.getTempCByIndex(0);
  lcd.print (rttemp);
  lcd.print ('C'); 

  lcd.setCursor (0,0);
  lcd.print ("Target : ");
  lcd.print (targettemp);
  lcd.print ('C'); 

  // If temperature goes down
  if(rttemp < oldtemp){
    Serial.println("Decrease");
    if(rttemp < targettemp + buffdown){digitalWrite(relay, HIGH);}
  }
  
  // If temperature goes up
  else if(rttemp > oldtemp){
    Serial.println("Increase");
    if(rttemp > targettemp - buffup){digitalWrite(relay, LOW);}
  }

  // If there is a perfect equal situation, it makes another loop
  else{}
  
  // Wait between two loops, the delay may affect the calculation of the buffers and/or the precision of the constant temperature maintained
  delay (1000); 
  
  // Save the previous temperature for the next comparison
  oldtemp = rttemp;
  
}  
