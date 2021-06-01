#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "saran";
const char* password = "poonpan11";

const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "43eb13bc-5a88-46c3-83c5-05f7b44bc126";
const char* mqtt_username = "jq5XeHbo72hFyH79a2e3Ct4VCEHM3r1m";
const char* mqtt_password = "fc5YgI-KksImLPO9BaGOke*Zb!OR4bpc";

WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
int s;

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection…");
        if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
            Serial.println("connected");
            client.subscribe("@msg/led");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println("try again in 5 seconds");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    client.setServer(mqtt_server, mqtt_port);
}

void loop() {
    
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    if(Serial.available()>0){
      s = Serial.parseInt();
      Serial.println("Received Signal :");
      Serial.println(s);
      //String data = "{\"data\": {\"signal\":" + String(s) + "}}";
      String data = String(s);
      
      Serial.println(data);
      data.toCharArray(msg, (data.length() + 1));
      client.publish("@msg/temp", msg);
      delay(100);
    }
}
