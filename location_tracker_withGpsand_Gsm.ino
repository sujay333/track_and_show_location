#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial mySerial(9, 10),ss(4,3);//mySerial(9,10) is for GSM module SIM 900A and ss(4,3) is for gps module NEO-6m

float flat, flon;


// The TinyGPS++ object
TinyGPSPlus gps;

void setup()
{
   
ss.begin(9600);  // Setting the baud rate of GSM Module Â 
Serial.begin(9600);
delay(100);
}

void loop()
{     
    while (ss.available() > 0)
    if (gps.encode(ss.read()))
      
      
      if(millis() > 5000 && gps.charsProcessed() < 10)
      {
              Serial.println(F("No GPS detected: check wiring."));
              while(true);
     }
     else
         { 
             
        

      if (mySerial.available()>0)
      switch(mySerial.read())
      {  
        case 's':
           // if (gps.time.isValid())
              //{                                   //uncomment the following lines only when you need SMS every 2 minutes
                //if (gps.time.minute()%2 ==0)                 
                  if (gps.location.isValid()
                  //{
                    SendMessage();
                     break;
                  //}
             // }
        
        
      }


}


void SendMessage()
{

      mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
         delay(1000); // Delay of 1000 milli seconds or 1 second
         mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r"); // Replace x with mobile number
         delay(100);
        mySerial.print("http://maps.google.com/maps?q=");//to send on mobile
        Serial.print("http://maps.google.com/maps?q=");//to print on the output screen
        mySerial.print("Latitude = ");
        mySerial.print(gps.location.lat(),6);
        Serial.print("Latitude = ");
        Serial.print(gps.location.lat(),6);
        Serial.print(",");
        mySerial.print(",");
        mySerial.print(" Longitude = ");
        mySerial.print(gps.location.lng(),6 );
        Serial.print(" Longitude = ");
        Serial.print(gps.location.lng(),6);
        //delay(200);
        mySerial.write(0x1A);// ASCII code of CTRL+Z
        mySerial.println();
       
}

 
