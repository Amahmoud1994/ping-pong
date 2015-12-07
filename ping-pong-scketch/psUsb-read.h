#include <PS4BT.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

PS4BT PS4(&Btd, PAIR);

bool printAngle;
uint8_t state = 0;

void psSetup() {
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
    if (PS4.getButtonClick(UP)) {
      Serial.print(F("\r\nUp"));
    }
    if (PS4.getButtonClick(RIGHT)) {
      Serial.print(F("\r\nRight"));
    }
    if (PS4.getButtonClick(DOWN)) {
      Serial.print(F("\r\nDown"));
    }
    if (PS4.getButtonClick(LEFT)) {
      Serial.print(F("\r\nLeft"));
    }
}
