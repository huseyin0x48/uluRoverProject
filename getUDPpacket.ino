#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;

const char* ssid = "ssid";
const char* password = "pass";

int port = 8081;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi ağına bağlanılıyor...");
  }

  Serial.println("WiFi ağına bağlanıldı.");
  Serial.print("UDP server bağlantı IP'si: ");
  Serial.println(WiFi.localIP());

  Udp.begin(port);
  Serial.print("UDP server bağlantı portu: ");
  Serial.println(port);

 
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Alınan paket boyutu: ");
    Serial.println(packetSize);

    char incomingPacket[255];
    int len = Udp.read(incomingPacket, 255);

    if (len > 0) {
      incomingPacket[len] = 0;
    }
    
    Serial.print("İçerik: ");
    Serial.println(incomingPacket);
    Serial.println();
    
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.print(incomingPacket);
    Udp.endPacket();
  }
}
