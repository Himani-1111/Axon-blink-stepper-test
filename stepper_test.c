#include <gpiod.h>
#include <unistd.h>
#include <stdio.h>

#define CHIPNAME "gpiochip0"
#define STEP_PIN 22
#define DIR_PIN 23
#define STEPS 200
#define STEP_DELAY 1000 // microseconds

int main() {
    struct gpiod_chip *chip;
    struct gpiod_line *step_line;
    struct gpiod_line *dir_line;

    chip = gpiod_chip_open_by_name(CHIPNAME);
    if (!chip) {
        perror("Open chip failed");
        return 1;
    }

    step_line = gpiod_chip_get_line(chip, STEP_PIN);
    dir_line = gpiod_chip_get_line(chip, DIR_PIN);

    if (!step_line || !dir_line) {
        perror("Get lines failed");
        return 1;
    }

    if (gpiod_line_request_output(step_line, "step", 0) < 0 ||
        gpiod_line_request_output(dir_line, "dir", 0) < 0) {
        perror("Request lines as output failed");
        return 1;
    }

    gpiod_line_set_value(dir_line, 1); // Set direction

    for (int i = 0; i < STEPS; i++) {
        gpiod_line_set_value(step_line, 1);
        usleep(STEP_DELAY);
        gpiod_line_set_value(step_line, 0);
        usleep(STEP_DELAY);
    }

    gpiod_chip_close(chip);
    return 0;
}
