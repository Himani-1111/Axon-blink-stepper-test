Axon Blink & Stepper Motor Test

This repository contains example C programs for testing GPIO control on the **Axon by Vicharak** board using the `libgpiod` library.

- `blink_led.c`: Toggles a GPIO pin to blink an LED.
- `stepper_test.c`: Controls a stepper motor via A4988 driver using STEP and DIR signals.

🔌 Circuit Connections

 1. 🔴 LED Blink Circuit (Using GPIO28)
- **GPIO Pin 28** (on Axon) → Connected to LED anode (long leg)
- LED cathode (short leg) → 330Ω resistor → GND on Axon

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

Open terminal inside the project folder (`Axon-blink-stepper-test`):

gcc -o blink blink_led.c -lgpiod
gcc -o stepper stepper_test.c -lgpiod
 
How to Execute 

Open terminal inside the project folder (`Axon-blink-stepper-test`):

sudo ./blink 
sudo ./stepper
