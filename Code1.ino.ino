#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
String s;
String x;
int engaged = 0;
//int debug=0;
void setup()
{
  
  //digitalWrite(Reset, HIGH);
  //delay(200); 
  //pinMode(Reset, OUTPUT);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("execution start....");
  delay(100);
  RecieveMessage();
}


void loop()
{
 
 if (mySerial.available()>0)
 {
   Serial.println("reading message and number....");
   //Serial.write(mySerial.read());
   //int x = mySerial.read(); 
   //Serial.println(x);
   s=mySerial.readString();
   Serial.println(s);
   Serial.println(s.substring(12,22));
   x = s.substring(12,22);
   if(x.length()==10 && (x.charAt(0)=='9' || x.charAt(0)=='8' || x.charAt(0)=='7' || x.charAt(0)=='6'))
   {
     //mySerial.println(s);
     delay(5000);
  
     Serial.println("calling sendMessage....");
     SendMessage();
     //digitalWrite(Reset, LOW);
     setup();
   }
 }
}

void RecieveMessage()
{
  Serial.println(" Inside receivemessage function.....");
  mySerial.println(" AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
 
 void SendMessage()
{
  mySerial.println(" AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  Serial.println(" concating for sending....");
  String t = "AT+CMGS=\"+91";
  t.concat(x);
  t.concat("\"\r");
  mySerial.println(t); // Replace x with mobile number
  delay(1000);
  String temp="SORRY!! THE DRONE IS ENGAGED..!!";
  if(engaged==0){
    engaged=1;
    mySerial.println("INCOMING...");// The SMS text you want to send
  }
   else{
    mySerial.println(temp);
   }
  delay(100);
  
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
}
