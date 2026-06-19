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

void checkSchedule(){
    timeClient.update();

    int hour = timeClient.getHours();
    int minute = timeClient.getMinutes();

    // ysed to print time every 10 seconds
    static unsigned long lastPrint = 0;

    if(millis()-lastPrint >1000){
        Serial.print("Current Time: ");
        Serial.print(hour);

        Serial.print(":");

        if(minute<10)
            {
            Serial.print("0";)
        }
    Serial.println(minute);
    lastPrint - millis();
    }
    
    if(hour == scheduledHour &&
      minute == scheduledMinute &&
      !triggeredToday){
        Serial.println("Auto light is turning on");
      
        sendRF();

        triggeredToday = true;
    }

    if(hour == 3 && minute == 0){
        triggeredToday = false;

    }
}

void setup(){
    Serial.begin(115200); // this is the baud rate
    delay(3000);

    Serial.println();
    Serial.print("Booting, please wait");

    mySwitch.enableTransmit(10);

  Serial.println("RF TRANSMITTER READY");

  // connection for wifi

  Serial.println("Connecting WiFi...");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {

    Serial.println("Retrying WiFi...");
    delay(3000);
  }

  IPAdress ip;
  do{
    delay(1000);
    ip = Wifi.localIP();

    Serial.print("Current IP is: ");
    serial.println(ip);
  }
  while(ip[0]==0);

  Serial.println("Wifi is connected");
  Serial.print("Final ip is");
  Serial.println(ip);

  server.begin();
  Serial.println("Server started");

  timeClient.begin();
  Serial.println("Time client has started");
}

