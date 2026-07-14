# rf-outdoor-light-project

A simple project that lets you control 433MHz RF lights using a local webpage hosted on an Arduino UNO R4 WiFi or ESP32.

Features
Manual Control: Toggle lights instantly via a button on the webpage.

Automation: Set a specific time on the webpage for the lights to turn on automatically every day.

No Extra Clock Hardware: Uses internet time (NTP) over WiFi to stay accurate instead of a physical clock module.

How the Code Works
WiFi & Web Server: Connects to your network and runs a server on port 80. It reads the web requests to see if you clicked "Toggle" or submitted a new "Auto Time".

NTP Time Sync: Connects to pool.ntp.org to check the current time. It compares this time against your schedule to trigger the lights.

RF Transmission: Uses the RCSwitch library to send a 24-bit code (11206632) out of Digital Pin 10 to trigger your light switch.

Double-Trigger Prevention: A logic flag ensures the RF signal only sends once when the target minute hits, resetting automatically at 3:00 AM.

Wiring Layout
RF GND (pin 1) to Arduino GND

RF VCC (pin 3) to Arduino 5V

RF DATA (pin 5) to Arduino Pin 10 

Quick BOM (more details in csv file)

<img width="314" height="146" alt="image" src="https://github.com/user-attachments/assets/c6937544-65f8-4b30-90b2-8405d139d20b" />

Note: I wrote the scehma for arduino cuz it's more popular but this also works with ESP32 as shown in the images. But just make sure you use the same pins as I wrote above and it works. 
The demo video shows it with arduino and the image in hardware shows it with ESP32! 

Total Cost: $43.50

Schema 

<img width="686" height="438" alt="image" src="https://github.com/user-attachments/assets/05ff829e-3f1f-498f-8609-5f6c7b1dde74" />

Image of completed circuit (my camera is not very good sorry)

<img width="1068" height="775" alt="image" src="https://github.com/user-attachments/assets/e87f57ed-46be-46d6-8be9-fb6f3f7455a4" />

Demo link:

https://www.youtube.com/watch?v=M-ceNtTLbqY
