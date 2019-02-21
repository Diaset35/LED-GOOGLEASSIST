
#include <WiFi.h>

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

WiFiClient wiFiClient;
Adafruit_MQTT_Client mqttClient(&wiFiClient, "192.168.0.119", 1883);
Adafruit_MQTT_Subscribe ledSubscriber(&mqttClient, "/led");

void ledCallback(double x) { 
  if(x == 1) {
  digitalWrite(27, HIGH);

} else if (x == 0) {
  digitalWrite(27, LOW);
}
  
  
  }

void setup() {
  
  pinMode(27, OUTPUT);
  Serial.begin(9600);
  WiFi.begin("createch", "createch");
  delay(5000); 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  ledSubscriber.setCallback(ledCallback);
  mqttClient.subscribe(&ledSubscriber);
 



}

void loop() {
  
  if (mqttClient.connected()) {
   mqttClient.processPackets(10000);
   mqttClient.ping();
 } else {
   mqttClient.disconnect();
   mqttClient.connect();
}
}
