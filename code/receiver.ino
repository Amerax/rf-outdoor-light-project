// Use this code with a rf receiver to gain all the info you need

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup(){
    Serial.begin(115200);

    mySwitch.enableReceive(digitalpPinToInterrupt(2));

    Serial.println("Receiver is looking for signals");
}

void loop(){
    if(mySwitch.available()){
        Serial.println("Decimal: ");
        Serial.println(mySwitch.getReceivedValue());

        Serial.print("Binary");
        Serial.println("mySwitch.getRecievedValue()", BIN);

        Serial.print("Bit Length: ");
        Serial.println(mySwitch.getReceivedBitLength());

        Serial.print("Protocal: ");
        Serial.println(mySwitch.getReceivedProtocal();)

        Serial.print("Pulse Length: ");
        Serial.println(mySwitch.getReceivedDelay());

        Serial.println("-------------------");
        mySwitch.resetAvailable());
    }
}
