/*
 * Timer.h
 * created: Dec 2020
 */

#ifndef TIMER_h
#define TIMER_h

#include "Arduino.h"
#include "PT6961.h"

#define TIMER_DEBUG 0

/*!
 * A Library that is used in conjunction with a PT6961 driven, 4 digit,
 * 7 segment display, for use as a stopwatch or timer.
 * \author srichs
 */
class Timer {
public:
  /*!
   * An enumeration to define the fidelity of the timer, whether it
   * counts by minutes or seconds.
   */
  enum Fidelity : byte { MINUTES, SECONDS };
  /*!
   * An enumeration to define the type of timer, whether it counts up
   * or counts down.
   */
  enum Type : byte { COUNTDOWN, COUNTUP };
  /*!
   * The default constructor for the Timer class.
   */
  Timer(uint8_t DIN, uint8_t CLK, uint8_t CS, uint8_t alarm)
      : _display(DIN, CLK, CS) {
    _alarmPin = alarm;
  };
  /*!
   * Initialize a countdown timer.
   * \param fidelity The fidelity of the Timer.
   * \param digits The digits to set the countdown timer to.
   */
  void countdown(Fidelity fidelity, uint16_t digits);
  /*!
   * Initialize a countup timer.
   * \param fidelity The fidelity of the Timer.
   */
  void countup(Fidelity fidelity);
  /*!
   * Checks and updates the displayed time. It should be called in a loop.
   */
  void update();
  /*!
   * Pauses the timer and saves the elapsed time at pause.
   */
  void pause();
  /*!
   * Restarts a paused timer.
   */
  void restart();

private:
  static const uint16_t MINUTE_INCREMENT = 60000;
  static const uint16_t SECOND_INCREMENT = 1000;
  static const uint16_t ALARM_LENGTH = 5000;
  Fidelity _fidelity;
  Type _type;
  PT6961 _display;
  uint32_t _nextTime;
  uint32_t _pauseTime;
  uint8_t _digitOne;
  uint8_t _digitTwo;
  uint8_t _digitThree;
  uint8_t _digitFour;
  uint8_t _alarmPin;
  bool _done;
  bool _isPaused;
  void init();
  void setTime(uint16_t digits);
  void decrement();
  void decrementLarge();
  void increment();
  void incrementLarge();
  void alarm();
};

#endif
