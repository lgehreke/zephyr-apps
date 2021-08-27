/* 
 * Copyright (C) 2021 metraTec GmbH
 */

#include <zephyr.h>

#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#define LED1_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
#define LED1  DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN   DT_GPIO_PIN(LED1_NODE, gpios)
#define FLAGS DT_GPIO_FLAGS(LED1_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led1 devicetree alias is not defined"
#define LED1  ""
#define PIN   0
#define FLAGS 0
#endif

void main(void)
{
    const struct device *dev;
    int                  ret;
    bool                 led_state = true;

    dev = device_get_binding(LED1);
    if (dev == NULL) {
        return;
    }

    ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
    if (ret < 0) {
        return;
    }

    while (1) {
        gpio_pin_set(dev, PIN, led_state);
        led_state = !led_state;
        k_msleep(500);
    }
}