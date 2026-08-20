# rf-outdoor-light-project

A simple project that lets you control 433MHz RF lights using a local webpage hosted on an Arduino UNO R4 WiFi or ESP32.

Features:
Manual Control: Toggle lights through a button on the webpage.

Automation: Set a specific time on the webpage for the lights to turn on automatically every day.

No Extra Clock Hardware: Uses internet time (NTP) over WiFi to stay accurate instead of a physical clock module.

How the Code Works
WiFi & Web Server: Connects to your network and runs a server. It reads the web requests to see if you clicked "Toggle" or submitted a new "Auto Time".

RF Transmission: Uses the RCSwitch library to send a 24-bit code (11206632) out of Digital Pin 10 to trigger your light switch. However your code may be different depending on model, simply change it. 

To run the code, wire the components using the schematics, then open the arduino ide and copy and paste the relevent code you want and connect your computer with the microcontroler and upload code. Or just download the .ino file from this repo and run it with the arduino ide or any ide that lets you upload to a microcontroller. 

*You do not need to edit code except for where it says to enter your network details, your ssid and internet password and your rf code freq as mentioned before. Make sure you fill in these two fields before running.  

**Uploading the Code**  

1. Open `main.ino` (or desired code file) in the Arduino IDE either download the file and open it, or just copy and paste its contents into the ide yourself.  
2. Connect your Arduino to your computer with a USB cable.  
3. Select the correct **Board** and **Port** under **Tools**.  
4. Click **Upload** (→).  
5. Wait for the upload to finish. The Arduino will automatically restart and run the program.

Code files overview:  

main.ino  
This is the main program and the file most users should use. Has all the advertised features and webserver etc. 

reciver.ino  
This is the RF receiver/testing program.  
It can be used with a compatible 433MHz RF receiver to help detect and identify the RF codes being transmitted by a remote control.  
This is useful if you do not already know the RF code used by your lights.  

transmitter.ino  
This is a basic RF transmitter test program.  

---

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

Onshape Link: https://cad.onshape.com/documents/eef422d60583b873929a7558/w/0fc1c908cc83cf96700e0fc9/e/6d5f1e9001d06be59a7583eb?renderMode=0&uiState=6a6f7e8d9649816d2430750a

Optional Case Included:

<img width="687" height="835" alt="image" src="https://github.com/user-attachments/assets/4d9cd76a-ea59-4eb5-bdf0-d63b4eeb6fc0" />

