#include <Arduino.h>
#include <WiFi.h>

#include "wifi_connect.h"
#include <WiFiClientSecure.h>

#include "ca_cert_emqx.h"
#include <PubSubClient.h>
#include "MQTT.h"

#include <Ticker.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include "Adafruit_SHT31.h"
#include "../include/secrets/wifi.h"
#include "../include/secrets/mqtt.h"

#define SERVO_PIN 16


#define LED1_PIN 5
#define LED2_PIN 18
#define LED3_PIN 19
#define LED4_PIN 23

#define FAN1_PIN 14
#define FAN2_PIN 27
#define PUMP_PIN 26

#define IR1_PIN 36
#define IR2_PIN 39
#define IR3_PIN 34
#define IR4_PIN 35

//sht30
Adafruit_SHT31 sht30;

//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//SERVO
Servo servoMotor;

// WORD 
namespace
{
    const char *ssid     = WiFiSecrets::ssid;
    const char *password = WiFiSecrets::pass;

    WiFiClientSecure tlsClient;
    PubSubClient mqttClient(tlsClient);

    Ticker shtTicker;
    Ticker irTicker;

    // MQTT topics
    const char *topic_sht30 = "esp32/sht30";

    const char *topic_servo = "esp32/servo";

    const char *topic_led1   = "esp32/led1";
    const char *topic_led2   = "esp32/led2";
    const char *topic_led3   = "esp32/led3";
    const char *topic_led4   = "esp32/led4";
    const char *topic_ledAll = "esp32/led_all";

    const char *topic_fan   = "esp32/fan";
    const char *topic_pump  = "esp32/pump";

    const char *topic_ir1   = "esp32/ir1";
    const char *topic_ir2   = "esp32/ir2";
    const char *topic_ir3   = "esp32/ir3";
    const char *topic_ir4   = "esp32/ir4";

    // Danh sách topic cần subscribe
    const char *subscribe_list[] = {
        topic_servo,
        topic_led1, topic_led2, topic_led3, topic_led4,
        topic_ledAll,
        topic_fan,
        topic_pump
    };
    int subscribe_count = 8;

    String client_id = String("ESP32-") + WiFi.macAddress();
}

// ======================================================
//                  READ SHT30 + Publish
// ======================================================
void publishSHT30()
{
    float t = sht30.readTemperature();
    float h = sht30.readHumidity();

    if (isnan(t) || isnan(h)) {
        Serial.println("[SHT30] Read failed!");
        return;
    }

    char json[80];
    sprintf(json, "{ \"temperature\": %.2f, \"humidity\": %.2f }", t, h);

    mqttClient.publish(topic_sht30, json);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printf("Temp: %.1f C", t);
    lcd.setCursor(0, 1);
    lcd.printf("Humi: %.1f %%", h);

    Serial.print("[SHT30] Publish: ");
    Serial.println(json);
}

// ======================================================
//                  READ IR SENSORS
// ======================================================
void publishIR()
{
    const char *ir1 = digitalRead(IR1_PIN) ? "HIGH" : "LOW";
    const char *ir2 = digitalRead(IR2_PIN) ? "HIGH" : "LOW";
    const char *ir3 = digitalRead(IR3_PIN) ? "HIGH" : "LOW";
    const char *ir4 = digitalRead(IR4_PIN) ? "HIGH" : "LOW";

    mqttClient.publish(topic_ir1, ir1);
    mqttClient.publish(topic_ir2, ir2);
    mqttClient.publish(topic_ir3, ir3);
    mqttClient.publish(topic_ir4, ir4);

    Serial.printf("[IR] 1:%s  2:%s  3:%s  4:%s\n", ir1, ir2, ir3, ir4);
}


void mqttCallback(char *topic, uint8_t *payload, unsigned int len)
{
    String msg = "";
    for (unsigned int i = 0; i < len; i++)
        msg += (char)payload[i];

    Serial.printf("[MQTT] %s = %s\n", topic, msg.c_str());

    // ===== Servo: quay 90 rồi tự quay về 0 =====
    if (!strcmp(topic, topic_servo)) {
        if (msg == "1") {
            Serial.println("[SERVO] Rotate 90 then return");
            servoMotor.write(90);   
            delay(200);            
            servoMotor.write(0);   
        } else {
            servoMotor.write(0);    
        }
        return;
    }


    if (!strcmp(topic, topic_led1)) { digitalWrite(LED1_PIN, msg == "1"); return; }
    if (!strcmp(topic, topic_led2)) { digitalWrite(LED2_PIN, msg == "1"); return; }
    if (!strcmp(topic, topic_led3)) { digitalWrite(LED3_PIN, msg == "1"); return; }
    if (!strcmp(topic, topic_led4)) { digitalWrite(LED4_PIN, msg == "1"); return; }

    // LED ALL
    if (!strcmp(topic, topic_ledAll)) {
        bool st = (msg == "1");
        digitalWrite(LED1_PIN, st);
        digitalWrite(LED2_PIN, st);
        digitalWrite(LED3_PIN, st);
        digitalWrite(LED4_PIN, st);
        Serial.printf("[LED_ALL] state = %d\n", st);
        return;
    }

    // FAN 
    if (!strcmp(topic, topic_fan)) {
        bool st = (msg == "1");
        digitalWrite(FAN1_PIN, st);
        digitalWrite(FAN2_PIN, st);
        Serial.printf("[FAN] state = %d\n", st);
        return;
    }

    // Pump
    if (!strcmp(topic, topic_pump)) {
        bool st = (msg == "1");
        digitalWrite(PUMP_PIN, st);
        Serial.printf("[PUMP] state = %d\n", st);
        return;
    }
}

//SETUP
void setup()
{
    Serial.begin(115200);
    delay(100);

    Serial.println("\n=== ESP32 START ===");

    setup_wifi(ssid, password);
    tlsClient.setCACert(ca_cert);

    mqttClient.setServer(EMQX::broker, EMQX::port);
    mqttClient.setCallback(mqttCallback);

    // Init Outputs
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);

    pinMode(FAN1_PIN, OUTPUT);
    pinMode(FAN2_PIN, OUTPUT);
    pinMode(PUMP_PIN, OUTPUT);

    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED4_PIN, LOW);
    digitalWrite(FAN1_PIN, LOW);
    digitalWrite(FAN2_PIN, LOW);
    digitalWrite(PUMP_PIN, LOW);

    // IR
    pinMode(IR1_PIN, INPUT);
    pinMode(IR2_PIN, INPUT);
    pinMode(IR3_PIN, INPUT);
    pinMode(IR4_PIN, INPUT);

    // Servo
    servoMotor.attach(SERVO_PIN);
    servoMotor.write(0);

    // LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System Booting...");
    delay(1000);

    // SHT30
    Wire.begin(21, 22);         // SCL=22, SDA=21
    if (!sht30.begin(0x44)) {
        Serial.println("Could not find SHT30 sensor!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SHT30 ERROR");
    } else {
        Serial.println("SHT30 OK");
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System Ready");

    // Timers
    shtTicker.attach(5, publishSHT30); // mỗi 5s đọc SHT30
    irTicker.attach(2, publishIR);     // mỗi 2s đọc IR

    Serial.println("Setup done.");
}

// ======================================================
//                        LOOP
// ======================================================
void loop()
{
    MQTT::reconnect(mqttClient,
                    client_id.c_str(),
                    EMQX::username,
                    EMQX::password,
                    subscribe_list,
                    subscribe_count);

    mqttClient.loop();
    delay(10);
}
