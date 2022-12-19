#include <SoftwareSerial.h>


#include <OneWire.h>
#include <DallasTemperature.h>

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial GPS(RXPin, TXPin);

#define ONE_WIRE_PIN 2     //Define the Arduino Pin 

OneWire oneWire(ONE_WIRE_PIN);    //Setup of instance to communicate with one wire sensor

DallasTemperature sensors(&oneWire);
SoftwareSerial mySerial(9, 10);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);  
  Serial.begin(9600);
  sensors.begin();// Setting the baud rate of Serial Monitor (Arduino)
  Serial.begin(9600);
  GPS.begin(GPSBaud);
  delay(100);
}


void loop()
{
  sensors.requestTemperatures();  //Call and request all sensors in one wire bus
  gps.encode(GPS.read());
     if (gps.location.isUpdated()){
      mySerial.println("Latitude= "); 
      mySerial.println(gps.location.lat(), 6);
      mySerial.println(" Longitude= "); 
      mySerial.println(gps.location.lng(), 6);
}
  //Printing the Temperature in Celsius and Fahrenheit

  Serial.print("Celsius temperature: ");
  String t = String(Serial.write(int(sensors.getTempCByIndex(0))));
  Serial.print(t);
  Serial.print("Fahrenheit temperature: ");
  Serial.print(sensors.getTempFByIndex(0));
  Serial.println();
  delay(1000);
//  mySerial.println("AT+CMGS=\"+919305954858\"\r"); // Replace x with mobile number
//     delay(1000);
//    mySerial.println("msg pahucha GSM SE KIYA THA");// The SMS text you want to send
//     delay(100);
//     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
//      delay(1000);
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+919305954858\"\r"); // Replace x with mobile number
     delay(1000);
     gps.encode(GPS.read());
     if (gps.location.isUpdated()){
      mySerial.println("Latitude= "); 
      mySerial.println(gps.location.lat(), 6);
      mySerial.println(" Longitude= "); 
      mySerial.println(gps.location.lng(), 6);
     }
     mySerial.println("Temperature is:-");
     mySerial.println(sensors.getTempCByIndex(0));// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
     delay(1000);
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+919305954858\"\r"); // Replace x with mobile number
     delay(1000);
     gps.encode(GPS.read());
      mySerial.println("Latitude= "); 
      mySerial.println(gps.location.lat(), 6);
      mySerial.println(" Longitude= "); 
      mySerial.println(gps.location.lng(), 6);
     mySerial.println("Temperature is:-");
     mySerial.println(sensors.getTempCByIndex(0));// The SMS text you want to send// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      break;



      
    case 'r':
      mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      delay(1000);
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}
