

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "your blynk auth";
int Left, Right, Fwd, Rev;
int Dir;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "spam";
char pass[] = "9410032900";

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT); // DA
  pinMode(D4, OUTPUT); //DB
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();

  if (Dir == 1)
  {
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    analogWrite(D1, Fwd - Right);
    analogWrite(D2, Fwd - Left);

  }
  else if (Dir == 0) {
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    analogWrite(D1, Rev - Right);
    analogWrite(D2, Rev - Left);
  }
  else {
    analogWrite(D1, 0);
    analogWrite(D2, 0);
  }




}

BLYNK_WRITE(V0) // Widget WRITEs to Virtual Pin V1
{
  int y = param[1].asInt(); // getting Direction

  if (y > 512) {
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
  else if (y < 512) {
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
    Dir = 3;
    //    analogWrite(D1, 0);
    //    analogWrite(D2, 0);
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
  //    analogWrite(D2, 1023 - Left);
  //    if (Dir == 1) {
  //      analogWrite(D2, Fwd);
  //    }
  //
  //    else {
  //      analogWrite(D2, Rev);
  //    }
  //  }
  //  else {
  //    analogWrite(D1, 0);
  //    analogWrite(D2, 0);
  //  }







  //  int Direction = Right - Left;
  //  int Speed = Fwd - Rev;
  //  Serial.print("The Direction is: ");
  //  Serial.println(Direction);
  //  Serial.print("The Speed is: ");
  //  Serial.println(Speed);
  //
  //  if ( Direction >= 0 && Speed >= 0) {
  //    digitalWrite(D3, HIGH);
  //    digitalWrite(D4, HIGH);
  //    analogWrite(D1, Fwd);
  //    analogWrite(D2, Right);
  //
  //
  //
  //  }
  //  else if ( Direction >= 0 && Speed <= 0) {
  //    digitalWrite(D3, HIGH);
  //    digitalWrite(D4, HIGH);
  //    analogWrite(D1, Left);
  //    analogWrite(D2, Fwd);
  //
  //  }
  //
  //  else if ( Direction <= 0 && Speed >= 0) {
  //    digitalWrite(D3, LOW);
  //    digitalWrite(D4, LOW);
  //    analogWrite(D1, Right);
  //    analogWrite(D2, Rev);
  //
  //  }
  //  else {
  //    digitalWrite(D3, LOW);
  //    digitalWrite(D4, LOW);
  //    analogWrite(D1, Rev);
  //    analogWrite(D2, Left);
  //  }
  //  Serial.println();
}
