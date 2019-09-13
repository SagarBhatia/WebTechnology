#include<SoftwareSerial.h>

SoftwareSerial mySerial(9,10);
String msg,num;
String temp;
char k;

void setup()
{
  // put your setup code here, to run once:
  //Serial.println("Executing..!!");
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Executing..!!");
  mySerial.println("AT+CMGF=1");
  delay(1000);
 /* mySerial.println("AT+CNMI=2,2,0,0,0");
  delay(2000);*/

}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("Reading Messages..!!");
  //if (occupied!=1)
//  delay(5000);
  if(mySerial.available()>0)
  {
      RecMsg();

    Serial.write(mySerial.read());
    msg=mySerial.readString();
//    Serial.setTimeout(3000);
    Serial.println(msg);
    delay(1000);
    num=msg.substring(8,21);
    delay(3000);
    Serial.println(num);
    SendMsg();
    delay(5000);
  }
}

void SendMsg()
{
  String t="AT+CMGS=\""; 
  t.concat(num);
  t.concat("\"");
  delay(1000);
  mySerial.println(t);
  delay(1000);
  mySerial.println("INCOMING.!!");
  delay(1000);
  mySerial.println((char)26);
  delay(1000);
  
}
void RecMsg()
{
  mySerial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
}
