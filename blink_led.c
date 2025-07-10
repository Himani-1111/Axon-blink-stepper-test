#include <gpiod.h>
#include <unistd.h>
#include <stdio.h>

#define CHIPNAME "gpiochip0"
#define LINE_OFFSET 28
#define BLINK_COUNT 5
#define DELAY 500000 // microseconds

int main() {
    struct gpiod_chip *chip;
    struct gpiod_line *line;

    chip = gpiod_chip_open_by_name(CHIPNAME);
    if (!chip) {
        perror("Open chip failed");
        return 1;
    }

    line = gpiod_chip_get_line(chip, LINE_OFFSET);
    if (!line) {
        perror("Get line failed");
        return 1;
    }

    if (gpiod_line_request_output(line, "blink", 0) < 0) {
        perror("Request line as output failed");
        return 1;
    }

    for (int i = 0; i < BLINK_COUNT; i++) {
        gpiod_line_set_value(line, 1);
        usleep(DELAY);
        gpiod_line_set_value(line, 0);
        usleep(DELAY);
    }

    gpiod_chip_close(chip);
    return 0;
}
