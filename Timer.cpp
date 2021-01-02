/*
 * Timer.cpp
 * created: Dec 2020
 */

#include "Arduino.h"
#include "PT6961.h"
#include "Timer.h"

void Timer::countdown(Fidelity fidelity, uint16_t digits)
{
    _fidelity = fidelity;
    _type = COUNTDOWN;
    setTime(digits);
    init();
}

void Timer::countup(Fidelity fidelity)
{
    _fidelity = fidelity;
    _type = COUNTUP;
    _digitOne = 0;
    _digitTwo = 0;
    _digitThree = 0;
    _digitFour = 0;
    init();
}

void Timer::update()
{
    if (millis() >= _nextTime && !_isPaused) {
        if (_type == COUNTDOWN) {
            decrement();
        } else {
            increment();
        }
        _display.sendDigits(_digitOne, _digitTwo, _digitThree, _digitFour, 1);
        if (_fidelity == MINUTES) {
            _nextTime += MINUTE_INCREMENT;
        } else {
            _nextTime += SECOND_INCREMENT;
        }
    }
}

void Timer::pause()
{
    if (!_isPaused) {
        _isPaused = true;
        _pauseTime = _nextTime - millis();
    }
}

void Timer::restart()
{
    if (_isPaused) {
        _isPaused = false;
        _nextTime = millis() + _pauseTime;
    }
}

/*
 * A common initialization method.
 */
void Timer::init()
{
#if (TIMER_DEBUG == 1)
    Serial.begin(9600);
    delay(1000);
    Serial.println("Timer initialization");
#endif
    _done = false;
    _isPaused = false;
    _display.initDisplay();
    _display.sendDigits(_digitOne, _digitTwo, _digitThree, _digitFour, 1);
    if (_fidelity == MINUTES) {
        _nextTime = millis() + MINUTE_INCREMENT;
    } else {
        _nextTime = millis() + SECOND_INCREMENT;
    }
}

/*
 * Sets the time to be displayed by the timer for a countdown.
 */
void Timer::setTime(uint16_t digits)
{
    if (digits > 9999 || digits <= 0) {
    #if (TIMER_DEBUG == 1)
        Serial.println("Given time outside of range.");
    #endif
    } else {
        _digitFour = digits % 10;
        digits = digits / 10;
        _digitThree = digits % 10;
        digits = digits / 10;
        _digitTwo = digits % 10;
        digits = digits / 10;
        _digitOne = digits % 10;
    #if (TIMER_DEBUG == 1)
        Serial.print("Time Set: ");
        Serial.print(_digitOne);
        Serial.print(_digitTwo);
        Serial.print(":");
        Serial.print(_digitThree);
        Serial.println(_digitFour);
    #endif
    }
}

/*
 * Decrements the third and fourth digits.
 */
void Timer::decrement()
{
    if (_digitFour == 0) {
        if (_digitThree == 0) {
            decrementLarge();
        } else {
            _digitThree--;
            _digitFour = 9;
        }
    } else {
        _digitFour--;
    }
}

/*
 * Decrements the first and second digits.
 */
void Timer::decrementLarge()
{
    if (_digitTwo == 0) {
        if (_digitOne == 0) {
            alarm();
        } else {
            _digitOne--;
            _digitTwo = 9;
            _digitThree = 5;
            _digitFour = 9;
        }
    } else {
        _digitTwo--;
        _digitThree = 5;
        _digitFour = 9;
    }
}

/*
 * Increments the third and fourth digits.
 */
void Timer::increment()
{
    if (_digitFour == 9) {
        if (_digitThree == 5) {
            incrementLarge();
        } else {
            _digitThree++;
            _digitFour = 0;
        }
    } else {
        _digitFour++;
    }
}

/*
 * Increments the first and second digits.
 */
void Timer::incrementLarge()
{
    if (_digitTwo == 9) {
        if (_digitOne == 9) {
            _digitOne = 0;
            _digitTwo = 0;
            _digitThree = 0;
            _digitFour = 0;
            alarm();
        } else {
            _digitOne++;
            _digitTwo = 0;
            _digitThree = 0;
            _digitFour = 0;
        }
    } else {
        _digitTwo++;
        _digitThree = 0;
        _digitFour = 0;
    }
}

/*
 * An alarm that is called when a countdown reaches 00:00 or a countup timer
 * reaches 99:99.
 */
void Timer::alarm()
{
    if (!_done) {
        digitalWrite(_alarmPin, HIGH);
        delay(ALARM_LENGTH);
        digitalWrite(_alarmPin, LOW);
        _done = true;
    }
}
