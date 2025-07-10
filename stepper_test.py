import gpiod
import time

# GPIO chip and lines
CHIP = 'gpiochip1'
STEP_LINE = 25  # PIN_18
DIR_LINE = 24   # PIN_17

# Setup chip and lines
chip = gpiod.Chip(CHIP)
step = chip.get_line(STEP_LINE)
direction = chip.get_line(DIR_LINE)

# Request lines as outputs
step.request(consumer='stepper', type=gpiod.LINE_REQ_DIR_OUT)
direction.request(consumer='stepper', type=gpiod.LINE_REQ_DIR_OUT)

# Set direction: 1 = CW, 0 = CCW
direction.set_value(1)

# Send steps
num_steps = 200  # One full revolution for 1.8° stepper motor
delay = 0.001    # 1 ms = 1 kHz → adjust for speed

for i in range(num_steps):
    step.set_value(1)
    time.sleep(delay)
    step.set_value(0)
    time.sleep(delay)

# Cleanup
step.set_value(0)
direction.set_value(0)
step.release()
direction.release()
