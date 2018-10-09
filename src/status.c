#include <zephyr.h>
#include <board.h>
#include <gpio.h>
#include <led.h>

#define LOG_LEVEL LOG_LEVEL_DEBUG
#include <logging/log.h>
LOG_MODULE_REGISTER(status);

#define STATUS_STACK_SIZE 500
#define STATUS_PRIORITY 5
#define NUM_LEDS 16
#define DELAY_TIME K_MSEC(10)

void status_thread(void)
{
    int i, on = 1;
	static struct device *led0, *ledc;

	ledc = device_get_binding(CONFIG_LP3943_DEV_NAME);
	if (!ledc) {
		LOG_ERR("Could not get pointer to %s sensor\n", CONFIG_LP3943_DEV_NAME);
		return;
	}

    /* turn all leds on */
	for (i = 0; i < NUM_LEDS; i++) {
		led_on(ledc, i);
		k_sleep(DELAY_TIME);
	}

	/* turn all leds off */
	for (i = 0; i < NUM_LEDS; i++) {
		led_off(ledc, i);
		k_sleep(DELAY_TIME);
	}

    led0 = device_get_binding(LED0_GPIO_CONTROLLER);
	gpio_pin_configure(led0, LED0_GPIO_PIN, GPIO_DIR_OUT);
	gpio_pin_write(led0, LED0_GPIO_PIN, 1);

    while (1) {
        gpio_pin_write(led0, LED0_GPIO_PIN, on);
		on = (on == 1) ? 0 : 1;
        k_sleep(2000);
    }
}

K_THREAD_DEFINE(status_id, STATUS_STACK_SIZE, status_thread, NULL, NULL, NULL,
		STATUS_PRIORITY, 0, K_NO_WAIT);