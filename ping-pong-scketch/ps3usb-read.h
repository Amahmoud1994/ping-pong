#include <PS3USB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
PS3USB PS3(&Usb); // This will just create the instance

bool printAngle;
uint8_t state = 0;

void ps3Setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 USB Library Started"));
}
void checkButtons() {
  Usb.Task();
    if (PS3.getButtonClick(UP)) {
      Serial.print(F("\r\nUp"));
      
    }
    if (PS3.getButtonClick(RIGHT)) {
      Serial.print(F("\r\nRight"));
      PS3.setLedOff();
      PS3.setLedOn(LED1);
    }
    if (PS3.getButtonClick(DOWN)) {
      Serial.print(F("\r\nDown"));
      PS3.setLedOff();
      PS3.setLedOn(LED2);
    }
    if (PS3.getButtonClick(LEFT)) {
      Serial.print(F("\r\nLeft"));
      PS3.setLedOff();
      PS3.setLedOn(LED3);
    }
}
