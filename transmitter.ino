#include <RC.Switch.h>

RCSwitch mySwitch = RCSwitch();

void setup(){
    Serial.begin(115200);

    mySwitch.enableTransmit(10);

    mySwitch.setProtocal(1);
    mySwitch.setPulseLength(390);

    mySwitch.setRepeatTransmit(15);

    Serial.println("Transmit will start");
}

void loop(){
    mySwitch.send(11206632, 24);

    Serial.println("RF wave sent");

    delay(3000);
}
