#ifndef PADDLE_SHIFT_INDICATION_H
#define PADDLE_SHIFT_INDICATION_H

#include <Arduino.h>

// PaddleShiftIndication
// Monitors shift up and shift down paddle switches wired to the Arduino.
// Applies 50ms software debounce to prevent spurious multi-shifts from
// mechanical contact bounce (a known issue with paddle switches per
// community A340 implementations).
//
// Call update() every loop. Read shiftUpRequested() / shiftDownRequested()
// to check for a pending shift — each returns true only once per physical press.

class PaddleShiftIndication {
public:
    PaddleShiftIndication(int pinUp, int pinDown);

    void begin();

    // Must be called every loop iteration to sample switch states
    void update();

    // Returns true once per physical upshift press, then resets
    bool shiftUpRequested();

    // Returns true once per physical downshift press, then resets
    bool shiftDownRequested();

private:
    int _pinUp;
    int _pinDown;

    bool _upFlag;
    bool _downFlag;

    int _lastUpState;
    int _lastDownState;

    unsigned long _lastUpTime;
    unsigned long _lastDownTime;

    static const unsigned long DEBOUNCE_MS = 50;
};

#endif
