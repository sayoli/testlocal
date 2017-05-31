#include <Adafruit_SleepyDog.h>

/*
File: RestClientwithlowpower.ino
This file makes an HTTP request after 10 seconds then sleep for 1min and shows the result both in
serial monitor and in the wifi console of the Arduino Uno WiFi.

Note: works only with Arduino Uno WiFi Developer Edition.
source file:RestClient.ino
ver:1.2 17/5/2 Kilima Sayoli 

*/

#include <Wire.h>
#include <UnoWiFiDevEd.h>
  const char* connector = "rest";
  const char* server = "web1610311936100.bj.bdysite.com";
  const char* method = "GET";
  const char resource[50] = "/IOTtest/transport_easy.php?id=2&curr1=3&curr2=5";//id=2&curr1=3&curr2=5&curr3=3";
  int loopnum=1,id=1,data_get,lastsign1=1,lastsign2=1,lastsign3=1;
  char data[20];
void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.begin(9600);
  Ciao.begin();
  Serial.println(resource);
  dealdata();
  delay(3000);
}

void( * resetFunc) (void) = 0;

void loop() {  
  doRequest(connector, server, resource, method);
  dealresponce();
  resetFunc();
  //int sleepMS = Watchdog.sleep(3000);  //sleep for 1min
  loopnum++;
  Serial.println(loopnum);
}


void doRequest(const char* conn, const char* server, const char* command, const char* method){
  CiaoData data = Ciao.write(conn, server, command, method);
  if (!data.isEmpty()){
    Ciao.println( "State: " + String (data.get(1)) );
    Ciao.println( "Response: " + String (data.get(2)) );
    Serial.println( "State: " + String (data.get(1)) );
    Serial.println( "Response: " + String (data.get(2)) );
    data_get=String(data.get(2)).toInt();
  }
  else{ 
    Ciao.println ("Write Error");
    Serial.println ("Write Error");
  }
}

char* Strcat(char* str1,char* str2) 
{   char *s=str1;  while(*str1)  {     str1++;  }   while(*str2) {    *str1++=*str2++; }    *str1 = 0;   return s; } 

void dealdata(){ 
  int j,curr1,curr2,curr3;
  //j=sprintf(data,"?id=%d",id);
  j=sprintf(data,"?",id);
  //id++;
  //curr1=analogRead(A1);
  //curr2=analogRead(A2);
  curr3=analogRead(A3);
  //j+=sprintf(data+j,"&curr1=%d",curr1);
  //j+=sprintf(data+j,"&curr2=%d",curr2);
  j+=sprintf(data+j,"curr3=%d",curr3);
  Strcat(resource,data);
  Serial.println(resource);
  
}

void dealresponce(){
    //if(loopnum!=0){        
          if(data_get%10==0&data_get%10==2){    
            //if(data_get%10==1){
            digitalWrite(2,HIGH);delay(200);digitalWrite(4,LOW);Serial.println("port3 on");lastsign3=data_get%10;
            }
          else {digitalWrite(2,LOW);Serial.println("port3 off"+data_get);
            }
       /*data_get=data_get/10;
          if(data_get%10==0&data_get%10==2){    
            //if(data_get%10==1){
            digitalWrite(3,LOW);Serial.println("port1 off"+data_get);}
          else {digitalWrite(3,HIGH);delay(200);digitalWrite(3,LOW);Serial.println("port2 on");lastsign2=data_get%10;}
       data_get=data_get/10;
          if(data_get%10==0&data_get%10==2){    
            //if(data_get%10==1){
            digitalWrite(2,HIGH);delay(200);digitalWrite(2,LOW);Serial.println("port1 on");lastsign1=data_get%10;
            }
          else {digitalWrite(2,LOW);Serial.println("port1 off");
            }*/
  }
 /* else{
    if(data_get%10!=1){digitalWrite(2,HIGH);delay(500);digitalWrite(2,LOW);Serial.println("port1 on");lastsign1=data_get%10;}
    data_get/10;
    if(data_get%10!=1){digitalWrite(3,HIGH);delay(500);digitalWrite(3,LOW);Serial.println("port2 on");lastsign2=data_get%10;}
    data_get/10;
    if(data_get%10!=1){digitalWrite(4,HIGH);delay(500);digitalWrite(4,LOW);Serial.println("port3 on");lastsign3=data_get%10;}
    }
}*/
