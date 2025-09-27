// Apple II Disk Clacker for ATtiny microcontrollers
//
// Arduino IDE board settings:
//  1. Install the DIY-ATtiny board package
//  2. Under Tools->Board, select your ATtiny type from the DIY-ATtiny board type 
//  3. Under Tools->Processor Version, select your processor (ATtiny13a)
//  4. Under Tools->Processor Speed, select 1.2 MHz Internal Oscillator
//
// Build a .hex file using Sketch->Export Compiled Binary
//
// Fuses when programming:
//  1. CKDIV8 = 0  (divide clock by 8; this is the default fuse value on ATtiny13)
//  2. CKSEL1:0 = 10  (use internal 9.6MHz oscillator; these are the default fuse values on ATtiny13)
//  3. RSTDISBL (disable /RESET so it can be used as GPIO)
//
// Because this code requires the RSTDISBL fuse to be cleared, a high voltage serial programmer must be used.


// PORTB pin definitions
#define DRIVEN_MASK   0b000001
#define CLACKOUT_MASK 0b000010
#define PHASES_MASK   0b111100


static inline bool is_drive_enabled() {
    return !(PINB & DRIVEN_MASK);
}

static inline uint8_t get_stepper_phase_bits() {
    return (PINB & PHASES_MASK);
}

static inline void relay_toggle() {
    PORTB ^= CLACKOUT_MASK;
}

static inline void relay_off() {
    PORTB &= ~CLACKOUT_MASK;
}


void setup() {
    // enable pull-ups on inputs
    PORTB = (DRIVEN_MASK | PHASES_MASK);

    // set pin directions
    DDRB = CLACKOUT_MASK;
}


void loop() {
    static uint8_t prev_phases = 0;

    if(! is_drive_enabled()) {
        relay_off();
        return;
    }

    uint8_t phases = get_stepper_phase_bits();
    if(phases != 0) {
        // check for any new bit to be set
        if(phases & ~prev_phases) {
            relay_toggle();
        }
        prev_phases = phases;
    }
}
