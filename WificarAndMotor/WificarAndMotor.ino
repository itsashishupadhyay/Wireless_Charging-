
#include <SparkFunBQ27441.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#define BLYNK_PRINT Serial

char auth[] = "blynk auth ";
short  Left, Right, Fwd, Rev;
bool Dir;

char ssid[] = "spam";
char pass[] = "9410032900";
// e.g. 850mAh battery
const unsigned int BATTERY_CAPACITY = 2000;
//
//unsigned long previousMillis = 0;
//const long interval = 10000;
BlynkTimer timer;



void setup()
{
  Serial.begin(9600);
  Wire.begin(D5,D6); //SDA SCL
  // Debug console
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT); // DA
  pinMode(D4, OUTPUT); //DB
  Blynk.begin(auth, ssid, pass);
  setupBQ27441();
  timer.setInterval(1000L,printBatteryStats);
}



void setupBQ27441(void)
{
  // Use lipo.begin() to initialize the BQ27441-G1A and confirm that it's
  // connected and communicating.
  if (!lipo.begin()) // begin() will return true if communication is successful
  {
    // If communication fails, print an error message and loop forever.
    Serial.println("Error: Unable to communicate with BQ27441.");
    Serial.println("  Check wiring and try again.");
    Serial.println("  (Battery must be plugged into Battery Babysitter!)");
    while (1) ;
  }
  Serial.println("Connected to BQ27441!");

  // Uset lipo.setCapacity(BATTERY_CAPACITY) to set the design capacity
  // of your battery.
  lipo.setCapacity(BATTERY_CAPACITY);
}

void printBatteryStats()
{
  // Read battery stats from the BQ27441-G1A
  unsigned int soc = lipo.soc();  // Read state-of-charge (%)
  Blynk.virtualWrite(V2, soc);
  
  unsigned int volts = lipo.voltage(); // Read battery voltage (mV)
  Blynk.virtualWrite(V3, volts);
  float current = lipo.current(AVG); // Read average current (mA)
  Blynk.virtualWrite(V4, current);
  unsigned int fullCapacity = lipo.capacity(FULL); // Read full capacity (mAh)
  Blynk.virtualWrite(V5, fullCapacity);

  unsigned int capacity = lipo.capacity(REMAIN); // Read remaining capacity (mAh)
  Blynk.virtualWrite(V6, capacity);

  int power = lipo.power(); // Read average power draw (mW)
  Blynk.virtualWrite(V7, power);
  int health = lipo.soh(); // Read state-of-health (%)
  Blynk.virtualWrite(V8, health);

  // Now print out those values:
//  String toPrint = String(soc) + "% | ";
//  toPrint += String(volts) + " mV | ";
//  toPrint += String(current) + " mA | ";
//  toPrint += String(capacity) + " / ";
//  toPrint += String(fullCapacity) + " mAh | ";
//  toPrint += String(power) + " mW | ";
//  toPrint += String(health) + "%";
//
//  Serial.println(toPrint);
}







void loop()
{
  Blynk.run();
   timer.run();
//  unsigned long currentMillis = millis();

  if (Dir == 1)
  {
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    analogWrite(D1, Fwd - Right);
    analogWrite(D2, Fwd - Left);
//    Serial.println("Fwd Test");

  }
  else if (Dir == 0) {
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    analogWrite(D1, Rev - Right);
    analogWrite(D2, Rev - Left);
//    Serial.println("back Test");
  }
//  else {
//    analogWrite(D1, 0);
//    analogWrite(D2, 0);
//    Serial.println("zero Test");
//  }

// if (currentMillis - previousMillis >= interval) {
//   previousMillis = currentMillis;
//   printBatteryStats();
// }
//
//
}

BLYNK_WRITE(V0) // Widget WRITEs to Virtual Pin V1
{
  int y = param[1].asInt(); // getting Direction

  if (y > 450) {
    Fwd = map(y, 512, 1023, 0, 1023);
    Rev = 0;
    Dir = 1;
    Serial.print("The FWD: ");
    Serial.println(Fwd);
    //    digitalWrite(D3, HIGH);
    //    digitalWrite(D4, HIGH);
    //        analogWrite(D1, Fwd);
    //        analogWrite(D2, Fwd);


  }
  else if (y < 450) {
    Rev = map(y, 511, 0, 0, 1023);
    Fwd = 0;
    Dir = 0;
    Serial.print("The REV: ");
    Serial.println(Rev);
    //    digitalWrite(D3, LOW);
    //    digitalWrite(D4, LOW);
    //        analogWrite(D1, Rev);
    //        analogWrite(D2, Rev);
  }
  else {
    
       analogWrite(D1, 0);
       analogWrite(D2, 0);
  }

}


BLYNK_WRITE(V1) // Widget WRITEs to Virtual Pin V1
{
  int x = param[0].asInt(); // getting Direction


  //  Rev=0;
  //  Fwd=0;
  //  Left=0;
  //  Rev=0;



  if (x >= 512) {
    Right = map(x, 512, 1023, 0, 1023);
    Left = 0;
    Serial.print("The Right: ");
    Serial.println(Right);
    //    analogWrite(D1, 1023 - Right);
    //
    //    if (Dir == 1) {
    //      analogWrite(D2, Fwd);
    //    }
    //
    //    else {
    //      analogWrite(D2, Rev);
    //    }

  }
  else if (x < 512) {
    Left = map(x, 511, 0, 0, 1023);
    Right = 0;
    Serial.print("The Left: ");
    Serial.println(Left);
  }

}
