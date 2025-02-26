# Smart-Sphere: IoT-Based Smart Building Automation  

## 📌 Overview  
**Smart-Sphere** is an IoT-driven smart building automation system powered by **ESP32** and **Blynk IoT**. It allows users to **remotely and manually control devices** like lights and buzzers, while monitoring real-time **temperature and humidity** via a **DHT22 sensor**.  

---

## 🚀 Features  
✅ **Remote & Manual Control** – Operate devices via the Blynk app or physical buttons  
✅ **Real-Time Monitoring** – Get live **temperature & humidity** updates  
✅ **State Synchronization** – Keeps manual and app controls in sync  
✅ **Scalable & Energy-Efficient** – Easily expandable with more devices  
✅ **Wokwi Simulation Tested** – Ensures reliable performance  

---

## 🛠️ Components  
- **ESP32** – WiFi-enabled microcontroller  
- **DHT22 Sensor** – Temperature & humidity monitoring  
- **Relay Modules** – Control electrical appliances  
- **Push Buttons** – Manual override for devices  
- **Blynk IoT Platform** – Cloud-based remote monitoring  

---

## 📱 Setup & Installation  
1. Connect **ESP32** to relays, push buttons, and **DHT22 sensor**  
2. Set up the **Blynk app** and obtain an authentication token  
3. Upload the **Arduino code** to the ESP32  
4. Sync device states with **Blynk virtual pins**  

---

## 💻 Code Snippets  
### **Device Control via Blynk**  
```cpp
BLYNK_WRITE(V1) {  
  digitalWrite(dev1, param.asInt());  
}

### **Sensor Data Handling** 
```cpp
void send_dht_val() {  
  TempAndHumidity data = dhtSensor.getTempAndHumidity();  
  Blynk.virtualWrite(V8, data.temperature);  
}