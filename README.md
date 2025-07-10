Axon Blink & Stepper Motor Test

This repository contains example C and Python programs for testing GPIO control on the **Axon by Vicharak** board using the `libgpiod` library.

- `blink_led.c` and `blink_led.py`: Toggles a GPIO pin to blink an LED.
- `stepper_test.c` and `stepper_test.py`: Controls a stepper motor via A4988 driver using STEP and DIR signals.

✅ **Common Setup for Both C and Python**


1. **Update package lists (once):**

   ```bash
   sudo apt update
   ```

2. **Check GPIO chip availability:**

   ```bash
   gpiodetect
   gpioinfo
   ```
👨‍💻 For C Language

 1. **Install GCC and libgpiod-dev**

```bash
sudo apt install build-essential libgpiod-dev
```

 2. **Create the C file using nano**

```bash
nano blink_led.c
```

or for stepper test:

```bash
nano stepper_test.c
```


🐍 For Python Language

 1. **Install Python and gpiod module**

```bash
sudo apt install python3-pip
pip3 install gpiod
```

 2. **Create the Python file using nano**

```bash
nano blink_led.py
```

or for stepper test:

```bash
nano stepper_test.py
```


🔌 Circuit Connections
  Refer to the this link for gpio documentation "https://docs.vicharak.in/vicharak_sbcs/axon/axon-gpio-description/"

 1. 🔴 LED Blink Circuit (Using GPIO28)
- **GPIO Pin 28** (on Axon) → Connected to LED anode (long leg)
- LED cathode (short leg) → 220kΩ resistor → GND on Axon mostly pin 6 or pin 3

💡 This LED will blink 5 times when `blink_led.c` is executed.


 2. 🔁 A4988 Stepper Motor Driver (GPIO22 & GPIO23)

| A4988 Pin     | Connect To (Axon) |
|---------------|-------------------|
| **STEP**      | GPIO **22**       |
| **DIR**       | GPIO **23**       |
| **VDD**       | 3.3V or 5V        |
| **GND**       | GND               |
| **1A/1B/2A/2B** | Stepper motor wires |
| **VMOT**      | Motor power (12V) |
| **EN**        | (Optional) GND    |

> The code rotates the motor **200 steps** in one direction. Adjust `STEP_DELAY` and `STEPS` in `stepper_test.c` for speed and distance.

⚙️ Requirements

- Axon by Vicharak (with `libgpiod` installed)
- `gcc` compiler installed
- LED + resistor (220k)
- A4988 driver + stepper motor (e.g., NEMA17)

  🧑‍💻 How to Compile

Open terminal 

For C:

gcc -o blink blink_led.c -lgpiod
gcc -o stepper stepper_test.c -lgpiod
 
How to Execute 

Open terminal:

For C:
sudo ./blink 
sudo ./stepper

For python:
sudo python3 blink_led.py
sudo python3 stepper_test.py
