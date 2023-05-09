#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "ssid"; //ESP'nin bağlanacağı ağın ssid'si girilmeli.
const char* password = "pass"; //ESP'nin bağlanacağı ağın şifresi girilmeli.

WiFiUDP Udp;

unsigned int localUdpPort = 8080; //UDP server'ın başlatılacağı port girilmeli.

void setup() {
  
  Serial.begin(115200);
  delay(1000);
  
  Serial.print("Bağlantı kurulan ağ: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi ağına bağlanılıyor...");
  }
  
  Serial.println("WiFi ağına bağlanıldı.");

  Udp.begin(localUdpPort);
  
  Serial.print("UDP sunucusunun başlatıldığı IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("UDP sunucusunun başlatıldığı port: ");
  Serial.println(localUdpPort);
}

void loop() {
  
  int randomValue = int(random(256));
  Serial.print("Gönderilen değer: ");
  Serial.println(randomValue);

  byte packetBuffer[4];
  packetBuffer[0] = randomValue >> 24;
  packetBuffer[1] = randomValue >> 16;
  packetBuffer[2] = randomValue >> 8;
  packetBuffer[3] = randomValue;

  IPAddress remoteIp(192, 168, 1, 94); //Paketlerin gönderileceği IP adresi girilmeli.
  int remotePort = 8081; //Paketlerin gönderileceği port girilmeli.
  
  Udp.beginPacket(remoteIp, remotePort);
  Udp.write(packetBuffer, 4);
  Udp.endPacket();

  delay(1000);
}
