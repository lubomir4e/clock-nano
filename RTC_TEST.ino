#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <TM1637Display.h>

#define RST_PIN 7
#define DAT_PIN 6
#define CLK_PIN 5

ThreeWire myWire(DAT_PIN, CLK_PIN, RST_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

#define TM_CLK 2
#define TM_DIO 3

TM1637Display display(TM_CLK, TM_DIO);

unsigned long lastUpdate = 0;

void setup() {
  Rtc.Begin();
  display.setBrightness(7);

  // Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
}

void loop() {
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    RtcDateTime now = Rtc.GetDateTime();

    int timeValue = now.Hour() * 100 + now.Minute();

    display.showNumberDecEx(timeValue, 0b01000000, true);
  }
}