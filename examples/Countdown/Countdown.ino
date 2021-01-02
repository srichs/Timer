#include "Timer.h"

// Pin 4 = DIN; Pin 3 = CLK; Pin 2 = CS; Pin 12 = Alarm;
Timer timer(4, 3, 2, 12);

void setup()
{
  timer.countdown(Timer::Fidelity::SECONDS, 1200);
}

void loop()
{
  timer.update();
  delay(100);
}
