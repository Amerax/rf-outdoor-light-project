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

void loop(){
    checkSchedule();
    WifiClient client = server.available();
    if(client){
        Serial.println("New Client");
        String request = client.readStringUtil('/r');
        Serial.println("request");
        client.flush();

        if(request.indexof("/toggle") != -1){
            sendRF();
        }

        int timeIndex = request.indexOf("/set?time=");

        if(timeIndex != -1){
            int start = timeIndex + 10;
            int end = request.indexOf(' ', start);
            String tiemValue = request.substring(start, end);

            int encodedIndex = timeValue.indexOf("%3A");

      if (encodedIndex != -1) {

        String hourStr =
          timeValue.substring(0, encodedIndex);

        String minuteStr = timeValue.substring(encodedIndex + 3); 
        scheduledHour = hourStr.toInt();
        scheduledMinute = minuteStr.toInt(); 
        Serial.print("Setting new time ");
        Serial.print(scheduledHour); 

        Serial.print(":"); 

        if (scheduledMinute < 10) {
          Serial.print("0");
        }

        Serial.println(scheduledMinute);
      }
    }

    client.println("Content-type:text/html");
    client.println();


<!DOCTYPE html>
<html>

<head>
<title>RF Light Control</title>
<style>
// basic css nothing special 
body{
  background:#111;
  color:white;
  font-family:Arial;
  text-align:center;
  margin-top:70px;
}

h1{
  font-size:50px;
}

button{
 width:300px;
 height:100px;
  font-size:30px;
  border:none;
  border-radius:20px;
  background:#00cc66;
  color:white;
  cursor:pointer;
  margin-top:20px;
}
button:hover{ 
  background:#00aa55;
}

input{ 
  width:220px;
  height:60px;
  font-size:28px; 
  border-radius:15px;
  border:none;
  text-align:center;
}

p{
  font-size:28px;
}

</style>

</head>

<body>

<h1>RF Light Control</h1>

<p>Current Auto Time:</p>

<p>
rawliteral");

    client.print(scheduledHour);

    client.print(":");

   if (scheduledMinute < 10) {
    client.print("0");
    }

    client.print(scheduledMinute);

    client.println(R"rawliteral(
</p>

<form action="/toggle">

<button type="submit">
Toggle Lights 
</button>
</form>
<form action="/set">

<input type="time" name="time">

<button type="submit">
Set Auto Time
</button>
</form>

</body>
</html>

)rawliteral");
    // to get client status
    client.println();
    delay(1);
    client.stop();
    Serial.println("Client was disconnected!");
    }

}
