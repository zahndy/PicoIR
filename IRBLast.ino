#define IR_SEND_PIN 15
#define IR_RECV_PIN 16
#define SEND_PWM_BY_TIMER 
#include <hardware/structs/usb.h> //pico-sdk/src/rp2350/
#include <hardware/regs/usb.h>
#include <IRremote.hpp>
#include <Keyboard.h>

bool sentIr = false;

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(500);
}

void loop() {
  uint32_t sie_status_value = usb_hw->sie_status;
  if(sie_status_value & USB_SIE_STATUS_SUSPENDED_BITS) // USB SUSPEND  
  { 
    if(!sentIr)
    {
      IrSender.sendNEC(0x6CD2, 0xCB, 0); //recorded onkyo on/off code
      sentIr = true;
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  else 
  { 
    if(sentIr)
    {
      IrSender.sendNEC(0x6CD2, 0xCB, 0);
      sentIr = false;
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
 delay(1000);
}
