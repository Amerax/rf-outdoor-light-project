// The main code
//Updated for html wifi capabilities 

#include <WifiS2.h>
#include <WifiUdp.h>
#include <NTPClient.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// Network info 
char ssid[] = "YouSSIDHere";
char pass[] = "YourPassHere";

WifiServer server(80);
WifiUDP ntpUDP; 

NTPClient timeClient(ntpUDP, "pool.ntp.org", -14400);

// time settings
int scheduledHour = 20;
int shceduledMinute = 30; 
bool triggeredToday = false;

void sendRF(){
    Serial.println("Sending signal...");

    mySwitch.setProtocal(1);
    mySwitch.setPulseLength(394);
    mySwitch.setRepeatTransmit(2);
    mySwitch.send(11206621, 24);

    Serial.println("Signal done");
}
