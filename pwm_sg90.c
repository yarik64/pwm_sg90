/*
 * LicenseL GNU GPL
 */

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// define PWM const
#define KILO 1e3
#define MICRO 1e-6
#define WRAP 10000
#define PWM_FREQ 50 // PWM frequency in hertz

// define pins
#define WHEEL1 16
#define WHEEL2 17
#define RULE   15

// define UART const
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

static int chars_rxed = 0;

// RX interrupt handler
void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        char ch0 = uart_getc(UART_ID);
        char ch1 = uart_getc(UART_ID);

        if (ch0 == 's') {
            // set wheels speed
			wheel_set_speed(WHEEL1, (int)ch1);
			wheel_set_speed(WHEEL2, (int)ch1);
        } else {
		    if (ch0 == 'd' ) {
                // define rule direction
			    rule_set_dir((int)ch1);
            } else {
                uart_puts(UART_ID, "Wrong command!!!");
			}
	    }
    }
}


int my_uart_init(){
    uart_init(UART_ID, 2400);
    gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
    gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));
    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
    uart_set_fifo_enabled(UART_ID, false);
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);

	return 0;
}


int init_wheel(int wheel_pin) {
    gpio_set_function(wheel_pin, GPIO_FUNC_PWM);
    uint slice_num_wheel = pwm_gpio_to_slice_num(wheel_pin);
    pwm_set_wrap(slice_num_wheel, 255);
    pwm_set_chan_level(slice_num_wheel, PWM_CHAN_A, 0);
    pwm_set_enabled(slice_num_wheel, true);

	return 0;
}


int init_rule() {
    float clkdiv = (float)frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY) * (float)KILO / (PWM_FREQ * WRAP);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clkdiv);

    gpio_set_function(RULE_PIN, GPIO_FUNC_PWM);
    uint slice_num_rule = pwm_gpio_to_slice_num(RULE_PIN);

	pwm_init(slice_num_rule, &config, true);
    pwm_set_chan_level(slice_num_rule, PWM_CHAN_A, 0);
    pwm_set_enabled(slice_num, true);

	return 0;
}


int wheel_set_speed(int wheel, int speed){
    pwm_set_gpio_level(wheel, speed);
}


int rule_set_dir(uint angle){

}


int main() {
    /// \tag::setup_pwm[]
    /// \end::setup_pwm[]

	init_wheel(WHEEL1);
	init_wheel(WHEEL2);
    init_rule();

    for(;;)
        tight_loop_contents();
}
