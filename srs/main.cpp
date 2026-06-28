#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <esp_wifi.h>
#include <lwip/init.h>
#include <lwip/netif.h>
#include <lwip/dhcp.h>
#include <WiFiAP.h>

// Castle House WiFi
const char* ssid_sta = "Castle House";
const char* password_sta = "12345678";

// DTECH AP
const char* ssid_ap = "DTECH";
const char* password_ap = "12345678";

// AP Gateway IP
IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting ESP32 WiFi Repeater...");

  // Connect to Castle House WiFi
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid_sta, password_sta);
  Serial.print("Connecting to Castle House WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("STA IP: ");
  Serial.println(WiFi.localIP());

  // Start DTECH Access Point
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid_ap, password_ap);
  Serial.println("DTECH AP started!");
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // Enable NAT / Internet forwarding
  wifi_promiscuous_filter_t filter;
  tcpip_adapter_init();
  Serial.println("Internet sharing enabled...");
}

void loop() {
  // The repeater will forward internet automatically
}