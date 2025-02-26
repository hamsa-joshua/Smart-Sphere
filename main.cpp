#define BLYNK_TEMPLATE_ID "TMPL3lTbNFyv-"
#define BLYNK_TEMPLATE_NAME "SMART BUILDING"
#define BLYNK_AUTH_TOKEN "bycZHCdC0qS54DoQfrw-h0YDT31-Y-Ve"

#define BLYNK_PRINT Serial // Enables serial monitor for debugging

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h>

// Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN;

// WiFi credentials
char ssid[] = "Wowki-GUEST";
char pass[] = "your_password_here"; // Ensure you set your WiFi password

BlynkTimer timer; // Blynk timer instance for periodic tasks
DHTesp dhtSensor; // DHT sensor instance

// Pin definitions for devices and sensors
const int dev1 = 5;
const int dev2 = 22;
const int dev3 = 21;
const int dev4 = 19;
const int dev5 = 18;
const int dht = 15;  // DHT sensor pin
const int button1 = 2; // Push button pin

// Variables to store relay states
bool relay_s_dev1 = false;
bool relay_s_dev2 = false;
bool relay_s_dev3 = false;
bool relay_s_dev4 = false;
bool relay_s_dev5 = false;

// Virtual pin definitions for Blynk
#define vpin1 V1
#define vpin2 V2
#define vpin3 V3
#define vpin4 V4
#define vpin5 V5
#define vpinTemp V8

// Sync virtual pins with Blynk server on connection
BLYNK_CONNECTED() {
    Blynk.syncVirtual(vpin1);
    Blynk.syncVirtual(vpin2);
    Blynk.syncVirtual(vpin3);
    Blynk.syncVirtual(vpin4);
    Blynk.syncVirtual(vpin5);
}

// Blynk write handlers to update relay states
BLYNK_WRITE(vpin1) {
    relay_s_dev1 = param.asInt();
    digitalWrite(dev1, relay_s_dev1);
}

BLYNK_WRITE(vpin2) {
    relay_s_dev2 = param.asInt();
    digitalWrite(dev2, relay_s_dev2);
}

BLYNK_WRITE(vpin3) {
    relay_s_dev3 = param.asInt();
    digitalWrite(dev3, relay_s_dev3);
}

BLYNK_WRITE(vpin4) {
    relay_s_dev4 = param.asInt();
    digitalWrite(dev4, relay_s_dev4);
}

BLYNK_WRITE(vpin5) {
    relay_s_dev5 = param.asInt();
    digitalWrite(dev5, relay_s_dev5);
}

// Function to send DHT sensor values to Blynk
void send_dht_val() {
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    float temp = data.temperature;
    if (!isnan(temp)) {
        Blynk.virtualWrite(vpinTemp, temp);
    }
}

void myTimerEvent() {
    Serial.println("Timer event triggered");
}

void setup() {
    Serial.begin(115200);

    pinMode(button1, INPUT_PULLUP);
    pinMode(dev1, OUTPUT);
    pinMode(dev2, OUTPUT);
    pinMode(dev3, OUTPUT);
    pinMode(dev4, OUTPUT);
    pinMode(dev5, OUTPUT);

    dhtSensor.setup(dht, DHTesp::DHT22);

    // Initialize devices to OFF state
    digitalWrite(dev1, LOW);
    digitalWrite(dev2, LOW);
    digitalWrite(dev3, LOW);
    digitalWrite(dev4, LOW);
    digitalWrite(dev5, LOW);

    Blynk.begin(auth, ssid, pass);

    timer.setInterval(1000L, myTimerEvent);
    timer.setInterval(2000L, send_dht_val);
}

// Function to check button status and control devices
void button_status() {
    if (digitalRead(button1) == LOW) {
        delay(500);
        controlButton(1);
        Blynk.virtualWrite(vpin1, relay_s_dev1);
    }
}

// Function to toggle device state based on button input
void controlButton(int relayIn) {
    if (relayIn == 1) {
        relay_s_dev1 = !relay_s_dev1;
        digitalWrite(dev1, relay_s_dev1);
        delay(100);
    }
}

void loop() {
    Blynk.run();  // Run Blynk
    timer.run();  // Run timer
    button_status();  // Check button status
}
