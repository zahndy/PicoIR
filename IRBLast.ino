#define IR_SEND_PIN 15
#define IR_RECV_PIN 16
#define SEND_PWM_BY_TIMER 
#include <hardware/structs/usb.h> //pico-sdk/src/rp2350/
#include <hardware/regs/usb.h>
#include <IRremote.hpp>
#include <Keyboard.h>

bool sentIrToggle = false;

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(500);
}

void loop() {
  uint32_t sie_status_value = usb_hw->sie_status;
  if(sie_status_value & USB_SIE_STATUS_SUSPENDED_BITS) // USB SUSPEND  
  { 
    if(sie_status_value & USB_SIE_STATUS_CONNECTED_BITS)
    {
      if(!sentIrToggle)
      {
        IrSender.sendNEC(0x6CD2, 0xCB, 0); //turn off (recorded onkyo on/off code)
        sentIrToggle = true;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(60000);
      }
    }
  }
  else 
  { 
    if(sentIrToggle)
    {
      IrSender.sendNEC(0x6CD2, 0xCB, 0); //turn on
      sentIrToggle = false;
      digitalWrite(LED_BUILTIN, LOW);
      delay(60000);
    }
  }
 delay(1000);
}
