#include "funcHeader.h"

void resetWifi(String newSsid, String newPass, String currentWifiType)
{
    char SSID[newSsid.length() + 1]; //stores ssid to pass to wifi method
    newSsid.toCharArray(SSID, newSsid.length() + 1);

    char PASS[newPass.length() + 1]; //stores password to pass to wifi method
    newPass.toCharArray(PASS, newPass.length() + 1);

    Serial.println(currentWifiType);

    WiFi.softAPdisconnect(true);
    WiFi.disconnect();
    delay(1000); //so both softap and wlan won't crash

    // Serial.println("Check");
    // WiFi.printDiag(Serial);

    if (currentWifiType == "WLAN") //begins working in user WLAN
    {
        // Serial.println("BBBB");
        WiFi.enableAP(false);
        WiFi.mode(WIFI_STA);
        WiFi.begin(SSID, PASS);
        Serial.print("WlanSsid: ");
        Serial.println(SSID);
        Serial.print("WlanPass: ");
        Serial.println(PASS);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.println(F("Connecting to WiFi.."));
        }
        Serial.println(F("Connected to the WiFi network"));
        Serial.println(WiFi.localIP());
        // Serial.println("WLAN: ");
        // WiFi.printDiag(Serial);
    }
    else if (currentWifiType == "softAP") // begins softAP regime
    {
        IPAddress NMask(255, 255, 255, 0);
        IPAddress IP(192, 168, 4, 1);
        Serial.print("Wifi Status bef: ");
        Serial.println(WiFi.status());
        Serial.print("AP SSID: ");
        Serial.println(SSID);
        Serial.print("AP PASS: ");
        Serial.println(PASS);
        WiFi.enableAP(true);
        WiFi.mode(WIFI_AP);
        WiFi.softAP(SSID, PASS) ? Serial.println("Ready") : Serial.println("Failed"); //for softap
        while (!(WiFi.softAPIP() == IP))
        {
            WiFi.softAPConfig(IP, IP, NMask);
        }
        Serial.print("Wifi Status aft: ");
        Serial.println(WiFi.status());
        WiFi.printDiag(Serial);
        // Serial.println("AP IP address: ");
        // Serial.println(WiFi.softAPIP());
        // Serial.println("SoftAP: ");
        // WiFi.printDiag(Serial);
    }
}
