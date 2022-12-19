#include "EspMQTTClient.h"
#include "MyData.h"

#define TXD 0                  //пин подключнеия дачика
bool x;                         //создаём переменную для данных с дачика
bool y;                         //создаём промежуточную переменную для проверки обнавлений данных дачика

EspMQTTClient client(
  ssid,            
  password,              
  
  MQTT_HOST,       
  MQTT_ID
);

void setup() {
  pinMode(TXD, INPUT);     //инициируем пин дачика на получение данных
  Serial.begin(9600);
}

void onConnectionEstablished(){}        //в этой функции получаем данные с сервера. Так ка в данном поекте мы не получаем данных то она у нас пустая

void publishTemperature(){
  if (client.isConnected()){                                   //проверяем на связи ли сервер
    client.publish("ikdd", String(x));
    Serial.print("Отправлен x равный ");
    Serial.println(x);
  }
}

void loop() {
  client.loop();                  //строчку не трогать!!!
  x = !digitalRead(TXD);

  if(y != x){                     //если значение дачика изменилось
    publishTemperature();         //вызываем функцию отправки данных
    y = x;
  }
}
