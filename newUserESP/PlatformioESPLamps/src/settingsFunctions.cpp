#include "funcHeader.h"

void resetWifi(String newSsid, String newPass, String currentWifiType)
{
    char SSID[newSsid.length() + 1]; //stores ssid to pass to wifi method
    newSsid.toCharArray(SSID, newSsid.length() + 1);

    char PASS[newPass.length() + 1];//stores password to pass to wifi method
    newPass.toCharArray(PASS, newPass.length() + 1);

    Serial.println("AAA");
    Serial.println(currentWifiType);

    

    if (currentWifiType == "WLAN")//begins working in user WLAN
    {
        Serial.println("BBBB");
        WiFi.disconnect();
        WiFi.begin(SSID, PASS);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.println(F("Connecting to WiFi.."));
        }
        Serial.println(F("Connected to the WiFi network"));
        Serial.println(WiFi.localIP());
    }
    else if (currentWifiType == "softAp")// begins softAP regime
    {
        Serial.println("HERE");
        WiFi.softAPdisconnect();
        WiFi.softAP(SSID, PASS) ? Serial.println("Ready") : Serial.println("Failed"); //for softap
        IPAddress NMask(255, 255, 255, 0);
        IPAddress IP(192, 168, 4, 1);
        WiFi.softAPConfig(IP, IP, NMask);
        delay(500);
        Serial.println("AP IP address: ");
        Serial.println(WiFi.softAPIP());
    }
}
