#include <gpiod.h>
#include <unistd.h>
#include <stdio.h>

#define CHIP_NAME "/dev/gpiochip1"
#define STEP_LINE_OFFSET 25  // PIN_18
#define DIR_LINE_OFFSET 24   // PIN_17

int main(void) {
    struct gpiod_chip *chip;
    struct gpiod_line *step, *dir;

    chip = gpiod_chip_open(CHIP_NAME);
    if (!chip) {
        perror("Failed to open GPIO chip");
        return 1;
    }

    step = gpiod_chip_get_line(chip, STEP_LINE_OFFSET);
    dir = gpiod_chip_get_line(chip, DIR_LINE_OFFSET);

    if (!step || !dir) {
        perror("Failed to get GPIO lines");
        return 1;
    }

    if (gpiod_line_request_output(step, "stepper", 0) < 0 ||
        gpiod_line_request_output(dir, "stepper", 0) < 0) {
        perror("Failed to request lines as output");
        return 1;
    }
// Set motor direction
    gpiod_line_set_value(dir, 1);  // 1 = CW, 0 = CCW

    // Generate step pulses
    for (int i = 0; i < 200; i++) {  // Adjust for full revs or microstepping
        gpiod_line_set_value(step, 1);
        usleep(1000);  // 1 ms HIGH
        gpiod_line_set_value(step, 0);
        usleep(1000);  // 1 ms LOW
    }

    gpiod_line_release(step);
    gpiod_line_release(dir);
    gpiod_chip_close(chip);

    return 0;
}
