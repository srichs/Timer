# Timer

A Library for Arduino that uses a 4-digit, 7 segment display, driven by a PT6961 chip, that can be used as a Timer or Stopwatch. It makes use of the [PT6961 Library](https://github.com/Renaud11232/PT6961) written by Garrett Blanton.

## How to Use

A timer object can be created by passing the pin numbers for the DIN, CLK, CS and Alarm pins of the Arduino.

```arduino
Timer timer(4, 3, 2, 12);
```

The ```Timer``` can be initialized in two different types: ```countdown()``` or ```countup()```, and these methods also start the Timer. The fidelity can be set to two different types: ```MINUTES``` or ```SECONDS```. ```MINUTES``` sets the timer to the format "HH:MM" and ```SECONDS``` sets the timer to the format "MM:SS".

```arduino
timer.countdown(Timer::Fidelity::SECONDS, 1200);
```

```arduino
timer.countup(Timer::Fidelity::MINUTES);
```

There are three methods that can be used to control the Timer: ```update()```, ```pause()```, and ```restart()```. The ```update()``` method will be used to check the time and update the display if needed.

## Dependencies

[PT6961 Library](https://github.com/Renaud11232/PT6961)
