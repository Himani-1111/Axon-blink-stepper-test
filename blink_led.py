import gpiod
import time

CHIP = 'gpiochip1'
LED_GPIO_OFFSET = 25  # GPIO1_D1 (Pin 18) at the header pins

chip = gpiod.Chip(CHIP)
led_line = chip.get_line(LED_GPIO_OFFSET)

led_line.request(consumer='led', type=gpiod.LINE_REQ_DIR_OUT)

# Blink the LED 10 times
for i in range(10):
    led_line.set_value(1)  # ON
    time.sleep(0.5)
    led_line.set_value(0)  # OFF
    time.sleep(0.5)

# Cleanup
led_line.release()


