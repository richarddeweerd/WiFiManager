#include <Arduino.h>
#include <LittleFS.h>
#include <WiFiManager.h>

#include "setup.h"
#define AP_NAME "WifiManager"
#define AP_PASS "password"

WiFiManager wm;
WiFiManagerParameterString custom_mqtt_server;
WiFiManagerParameterInt custom_mqtt_port;
WiFiManagerParameterString parameter_mqtt_user;
WiFiManagerParameterPassword parameter_mqtt_password;
WiFiManagerParameterBoolean custom_mqtt_boolean;
WiFiManagerParameterBoolean custom_mqtt_boolean2;
WiFiManagerParameterSpacer spacer("Label");
WiFiManagerParameterSelect custom_selector;
WiFiManagerParameterSelectOption light_mode_off(1, "Label1");
WiFiManagerParameterSelectOption base_option2(2, "Label2");

void cb() {
    DynamicJsonDocument doc(2048);
    wm.save(doc);
    serializeJson(doc, Serial);
    File file = LittleFS.open("/settings.json", "w");
    serializeJson(doc, file);
    file.close();
}

void load_from_file(WiFiManager* wm) {
    Serial.println("Loading Config");
    DynamicJsonDocument doc(2048);
    File file = LittleFS.open("/settings.json", "r");
    deserializeJson(doc, file);
    file.close();
    wm->load(doc);
    serializeJson(doc, Serial);
}

void setup() {
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);

    if (!LittleFS.begin()) {
        Serial.println("LittleFS mount failed");
        LittleFS.format();
    }

    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();
    // wm_init(&wm);
    wm.addParameter(&custom_mqtt_server);
    wm.addParameter(&custom_mqtt_port);
    wm.addParameter(&parameter_mqtt_user);
    wm.addParameter(&spacer);
    wm.addParameter(&parameter_mqtt_password);
    wm.addParameter(&custom_mqtt_boolean);
    wm.addParameter(&custom_mqtt_boolean2);
    wm.addParameter(&custom_selector);

    std::vector<const char*> menu = {"wifi", "info", "param", "sep", "erase", "update", "restart", "exit"};
    wm.setMenu(menu);

    wm.setSaveParamsCallback(cb);

    load_from_file(&wm);

    bool res = wm.autoConnect(AP_NAME, AP_PASS);  // password protected ap

    if (!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } else {
        // if you get here you have connected to the WiFi
        Serial.println("connected...yeey :)");
        wm.startWebPortal();
    }
    // wm.save();
}

void loop() {
    wm.process();
    // put your main code here, to run repeatedly:
};  // password protected ap
