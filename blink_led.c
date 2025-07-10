// this code can also be used to toggle the pins 


#include <gpiod.h>
#include <unistd.h>
#include <stdio.h>

#define CHIP_NAME "/dev/gpiochip1"
#define TEST_LINE_OFFSET 24  // PIN_18

int main(void) {
    struct gpiod_chip *chip;
    struct gpiod_line *line;

    chip = gpiod_chip_open(CHIP_NAME);
    if (!chip) {
        perror("Open chip failed");
        return 1;
    }

    line = gpiod_chip_get_line(chip, TEST_LINE_OFFSET);
    if (!line) {
        perror("Get line failed");
        return 1;
    }

    if (gpiod_line_request_output(line, "toggle", 0) < 0) {
        perror("Request output failed");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        gpiod_line_set_value(line, 1);
        printf("Pin HIGH\n");
        usleep(500000);  // 0.5 sec
        gpiod_line_set_value(line, 0);
        printf("Pin LOW\n");
        usleep(500000);
    }

    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}
