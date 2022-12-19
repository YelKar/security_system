#include "Arduino.h"
#include "EspMQTTClient.h"
#include "MyData.h"

#define TXD 2              
int x;                    
int y;                    

EspMQTTClient client(
  ssid,            
  password,              
  
  MQTT_HOST,       
  MQTT_ID 
);

void setup() {
  pinMode(TXD, INPUT);     //инициируем пин дачика на получение данных
  Serial.begin(9600);
  Serial.setTimeout(200);
  client.subscribe("ikdd", onTestMessageReceived);
}

void onConnectionEstablished(){
  Serial.println("conn");
}        //в этой функции получаем данные с сервера. Так ка в данном поекте мы не получаем данных то она у нас пустая

void publishTemperature(int x){
  if (client.isConnected()){
    String pl = (String)x;
    client.publish("topic", pl);
    Serial.print("Отправлен x равный ");
    Serial.println(x);
    Serial.println(pl);
  }
}

void onTestMessageReceived(const String& message) {
  Serial.print("message received from test/mytopic: " + message);
}

void loop() {
  client.loop();
  int x = Serial.parseInt();
  // if(digitalRead(TXD)){           //если от дачика получен высокий сигнал
  //   x = false;
  // }
  // else if(!digitalRead(TXD)){     //если от дачика получен низкий сигнал
  //   x = true;
  // }

  if(y != x && !!x){                     //если значение дачика изменилось
    publishTemperature(x);         //вызываем функцию отправки данных
    y = x;
    Serial.println("Detected");
  }
}
