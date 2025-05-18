/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Output PWM signals on pins 0 and 1

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define KILO 1e3
#define MICRO 1e-6
#define WRAP 10000
#define PWM_FREQ 50 // PWM frequency in hertz

#define WHEEL1_PIN 16
#define WHEEL2_PIN 17
#define RULE_PIN   15

int main() {
    /// \tag::setup_pwm[]
    float clkdiv = (float)frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY) * (float)KILO / (PWM_FREQ * WRAP);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clkdiv);


    gpio_set_function(WHEEL1_PIN, GPIO_FUNC_PWM);
    gpio_set_function(WHEEL2_PIN, GPIO_FUNC_PWM);
    gpio_set_function(RULE_PIN,   GPIO_FUNC_PWM);


    uint slice_num_wheel1 = pwm_gpio_to_slice_num(WHEEL1_PIN);
    uint slice_num_wheel2 = pwm_gpio_to_slice_num(WHEEL2_PIN);
    uint slice_num_rule   = pwm_gpio_to_slice_num(RULE_PIN);


    pwm_set_wrap(slice_num_wheel1, 255);
    pwm_set_wrap(slice_num_wheel2, 255);
    pwm_init(slice_num_rule, &config, true);


    pwm_set_chan_level(slice_num_wheel1, PWM_CHAN_A, 0);
    pwm_set_chan_level(slice_num_wheel2, PWM_CHAN_A, 0);
    pwm_set_chan_level(slice_num_rule,   PWM_CHAN_A, 0);


    pwm_set_enabled(slice_num_wheel1, true);
    pwm_set_enabled(slice_num_wheel2, true);
    // pwm_set_enabled(slice_num, true);
    /// \end::setup_pwm[]

    // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
    // correct slice and channel for a given GPIO.
    static int fade = 0, d = 16, s = 1;



    for(;;) {
        sleep_ms(100);
        fade += d;
        if (fade == 256 || fade == 0) d *= -1;
        pwm_set_gpio_level(WHEEL1_PIN, fade);
        pwm_set_gpio_level(WHEEL2_PIN, fade);
    }
}
