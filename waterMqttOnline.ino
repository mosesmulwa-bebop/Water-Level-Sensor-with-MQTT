#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Phantom6";
const char* password = "host2000";


const char* mqtt_server = "soldier.cloudmqtt.com";
const int mqtt_port = 12826;
const char* mqtt_user = "xzzztrqz";
const char* mqtt_pass = "s_rcKgQU_EgA";
//const char* mqtt_client_name = "arduinoClient1";



long lastMsg = 0;
char msg[50];
int value = 0;


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

WiFiClient espClient;
PubSubClient client(mqtt_server,mqtt_port,callback,espClient);

void setup() {
    
Serial.begin(115200);

WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Connecting to WiFi..");
}
Serial.println("Connected to the WiFi network");
client.setServer(mqtt_server, mqtt_port);
client.setCallback(callback);
}


void reconnect(){
while (!client.connected()) {
Serial.println("Connecting to MQTT…");
if (client.connect("ESP8266Client", mqtt_user, mqtt_pass )) {
Serial.println("connected");
 
 

} 
else {
Serial.print("failed with state");
Serial.print(client.state());
delay(2000);
}
}
}

void loop()
{
if(!client.connected()){
reconnect();
}
client.loop();

 int value = analogRead(A0);
  delay(1000);

  String value1 = String(value);
   int numt = value;
  char cstr[16];

  itoa(numt,cstr,10);
  delay(1500);

  client.publish("water/level",cstr);
client.subscribe("water/level");
  Serial.print("Publish Message: ");
  Serial.println(value1);


}
