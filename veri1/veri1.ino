#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Wi-Fi ayarları
const char* ssid     = "TURKNET_BAEA6";
const char* password = "ycUdfSQT";

// UDP ayarları
WiFiUDP udp;
const char* udpAddress = "192.168.1.11";  
const int udpPort = 4210;

// Sensör pin ve nesneleri
const int pirPin = 33;
Adafruit_BME280 bme;

unsigned long delayTime = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);

  // I2C başlat (ESP32 S3 için SDA=8, SCL=9)
  Wire.begin(8, 9);

  // BME280 başlat
  if (!bme.begin(0x76)) {
    Serial.println("BME280 sensörü bulunamadı!");
    while (1);
  }

  // Wi-Fi bağlantısı
  WiFi.begin(ssid, password);
  Serial.print("WiFi bağlanıyor...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi bağlandı!");
  Serial.print("IP adresi: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // PIR sensör durumu
  int hareket = digitalRead(pirPin);
  String hareketDurumu = (hareket == HIGH) ? "Hareket var" : "Hareket yok";

  // BME280 verileri
  float sicaklik = bme.readTemperature();
  float nem = bme.readHumidity();
  float basinc = bme.readPressure() / 100.0F;

  // Seri port çıktısı
  Serial.println(hareketDurumu);
  Serial.printf("Sıcaklık: %.2f °C, Nem: %.2f %%, Basınç: %.2f hPa\n", sicaklik, nem, basinc);

  // JSON formatında UDP mesajı
  String udpMesaj = "{";
  udpMesaj += "\"hareket\":\"" + hareketDurumu + "\",";
  udpMesaj += "\"sicaklik\":" + String(sicaklik, 2) + ",";
  udpMesaj += "\"nem\":" + String(nem, 2) + ",";
  udpMesaj += "\"basinc\":" + String(basinc, 2);
  udpMesaj += "}";

  // UDP mesaj gönderimi
  udp.beginPacket(udpAddress, udpPort);
  udp.print(udpMesaj);
  udp.endPacket();

  Serial.println("UDP veri gönderildi.\n");

  delay(delayTime);
}
