/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Output PWM signals on pins 0 and 1

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define WHEEL1_PIN 2
#define WHEEL2_PIN 4
#define RULE_PIN

int main() {
    /// \tag::setup_pwm[]

    // Tell GPIO 0 and 1 they are allocated to the PWM
    gpio_set_function(WHEEL1_PIN, GPIO_FUNC_PWM);
    gpio_set_function(WHEEL2_PIN, GPIO_FUNC_PWM);
    // gpio_set_function(RULE_PIN,   GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_num_wheel1 = pwm_gpio_to_slice_num(WHEEL1_PIN);
    uint slice_num_wheel2 = pwm_gpio_to_slice_num(WHEEL2_PIN);
    // uint slice_num = pwm_gpio_to_slice_num(0);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num_wheel1, 256);
    pwm_set_wrap(slice_num_wheel2, 256);
    // pwm_set_wrap(slice_num, 3);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num_wheel1, PWM_CHAN_A, 1);
    pwm_set_chan_level(slice_num_wheel2, PWM_CHAN_A, 1);
    // pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    // Set the PWM running
    pwm_set_enabled(slice_num_wheel1, true);
    pwm_set_enabled(slice_num_wheel2, true);
    // pwm_set_enabled(slice_num, true);
    /// \end::setup_pwm[]

    // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
    // correct slice and channel for a given GPIO.
    static int fade = 0, d = 16;

    for(;;) {
        sleep_ms(100);
        fade += d;
        if (fade == 256 || fade == 0) d *= -1;
		pwm_set_gpio_level(WHEEL1_PIN, fade);
		pwm_set_gpio_level(WHEEL2_PIN, fade);
    }
}
