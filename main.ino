/*
  This was done on an uno r4. 
  For web capabiltiies a esp32 or internet enabled microcontroler is required. 
*/

#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();


char ssid[] = "Your Wifi Name Here";
char pass[] = "Your wifi pass here";

WiFiServer server(80);


WiFiUDP ntpUDP;


NTPClient timeClient(ntpUDP, "pool.ntp.org", -14400);


int scheduledHour = 20;
int scheduledMinute = 30;

bool triggeredToday = false;


void sendRF() {

  Serial.println("SENDING SINGLE CLEAN RF");

  mySwitch.setProtocol(1);

  mySwitch.setPulseLength(394);

  mySwitch.setRepeatTransmit(2);

  mySwitch.send(11206632, 24);

  Serial.println("DONE");
}



void checkSchedule() {

  timeClient.update();

  int hour = timeClient.getHours();
  int minute = timeClient.getMinutes();

  static unsigned long lastPrint = 0;

  if (millis() - lastPrint > 10000) {

    Serial.print("Current Time: ");

    Serial.print(hour);

    Serial.print(":");

    if (minute < 10) {
      Serial.print("0");
    }

    Serial.println(minute);

    lastPrint = millis();
  }

  if (hour == scheduledHour &&
      minute == scheduledMinute &&
      !triggeredToday) {

    Serial.println("AUTO LIGHT TOGGLE!");

    sendRF();

    triggeredToday = true;
  }

  if (hour == 3 && minute == 0) {

    triggeredToday = false;
  }
}

void setup() {

  Serial.begin(115200);

  delay(3000);

  Serial.println();
  Serial.println("BOOTING...");


  mySwitch.enableTransmit(10);

  Serial.println("RF TRANSMITTER READY");


  Serial.println("Connecting WiFi...");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {

    Serial.println("Retrying WiFi...");
    delay(3000);
  }

  // Wait for REAL IP
  IPAddress ip;

  do {

    delay(1000);

    ip = WiFi.localIP();

    Serial.print("Current IP: ");
    Serial.println(ip);

  } while (ip[0] == 0);

  Serial.println("WIFI FULLY CONNECTED!");

  Serial.print("FINAL IP: ");
  Serial.println(ip);

  server.begin();

  Serial.println("SERVER STARTED");


  timeClient.begin();

  Serial.println("TIME CLIENT STARTED");
}

void loop() {

  checkSchedule();

  WiFiClient client = server.available();

  if (client) {

    Serial.println("NEW CLIENT");

    String request = client.readStringUntil('\r');

    Serial.println(request);

    client.flush();

    if (request.indexOf("/toggle") != -1) {

      sendRF();
    }


    int timeIndex = request.indexOf("/set?time=");

    if (timeIndex != -1) {

      int start = timeIndex + 10;

      int end = request.indexOf(' ', start);

      String timeValue = request.substring(start, end);


      int encodedIndex = timeValue.indexOf("%3A");

      if (encodedIndex != -1) {

        String hourStr =
          timeValue.substring(0, encodedIndex);

        String minuteStr =
          timeValue.substring(encodedIndex + 3);

        scheduledHour = hourStr.toInt();

        scheduledMinute = minuteStr.toInt();

        Serial.print("NEW TIME SET: ");

        Serial.print(scheduledHour);

        Serial.print(":");

        if (scheduledMinute < 10) {
          Serial.print("0");
        }

        Serial.println(scheduledMinute);
      }
    }


    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    client.println(R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<title>RF Light Control</title>

<style>

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
)rawliteral");

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

<br><br>

<form action="/set">

<input type="time" name="time">

<br><br>

<button type="submit">
Set Auto Time
</button>

</form>

</body>
</html>

)rawliteral");

    client.println();

    delay(1);

    client.stop();

    Serial.println("CLIENT DISCONNECTED");
  }
}
