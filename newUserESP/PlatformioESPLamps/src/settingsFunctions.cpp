#include "funcHeader.h"

bool resetWifi(String newSsid, String newPass, String currentWifiType)
{
    char SSID[newSsid.length() + 1]; //stores ssid to pass to wifi method
    newSsid.toCharArray(SSID, newSsid.length() + 1);

    char PASS[newPass.length() + 1]; //stores password to pass to wifi method
    newPass.toCharArray(PASS, newPass.length() + 1);

    // Serial.println(currentWifiType);

    WiFi.softAPdisconnect(true);
    WiFi.disconnect();
    delay(1000); //so both softap and wlan won't crash

    // Serial.println("Check");
    // WiFi.printDiag(Serial);

    unsigned long connectionTimeOut = 0;
    int timeOut = 30000;

    if (currentWifiType == "WLAN") //begins working in user WLAN
    {

        WiFi.enableAP(false); //turns off softAP mode
        WiFi.mode(WIFI_STA);  //enables WIFI STA mode

        // sets default IP address 192.168.0.11
        // if (!WiFi.config(IPAddress(192, 168, 0, 11), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0), IPAddress(8, 8, 8, 8)))
            // Serial.println("STA Failed to configure");

        WiFi.begin(SSID, PASS); //starts wifi

        connectionTimeOut = millis();
        while (WiFi.status() != WL_CONNECTED) //waits untils hub gets connected to WLAN
        {
            delay(500);
            Serial.println(F("Connecting to WiFi.."));
            if (millis() - connectionTimeOut >= timeOut)
                return false;
        }
        Serial.println(F("Connected to the WiFi network"));
        Serial.println(WiFi.localIP());
        // WiFi.printDiag(Serial);
    }
    else if (currentWifiType == "softAP") // begins softAP regime
    {
        IPAddress NMask(255, 255, 255, 0);
        IPAddress IP(192, 168, 4, 1);
        // Serial.print("Wifi Status bef: ");
        // Serial.println(WiFi.status());
        // Serial.print("AP SSID: ");
        // Serial.println(SSID);
        // Serial.print("AP PASS: ");
        // Serial.println(PASS);
        WiFi.enableAP(true);                                                          //enables softAP mode
        WiFi.mode(WIFI_AP);                                                           //enables WIFI_AP mode
        WiFi.softAP(SSID, PASS) ? Serial.println("Ready") : Serial.println("Failed"); //starts softAP
        while (!(WiFi.softAPIP() == IP))                                              //waits until softAP starts, this prevents crashes
        {
            WiFi.softAPConfig(IP, IP, NMask);
        }
        // WiFi.printDiag(Serial);
        // Serial.println("AP IP address: ");
        // Serial.println(WiFi.softAPIP());
    }
    return true;
}
