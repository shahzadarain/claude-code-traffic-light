# Wiring guide

This guide wires three LEDs to an ESP32 so the firmware can switch them on and
off. It takes about 10 minutes on a breadboard and needs no soldering.

## Parts

| Part | Qty | Notes |
| --- | --- | --- |
| ESP32 dev board | 1 | Any common ESP32 (e.g. ESP32-WROOM DevKit). ~$6 |
| 5 mm LEDs | 3 | One red, one yellow, one green |
| 220 Ω resistors | 3 | One per LED, to limit current |
| Breadboard | 1 | Half-size is plenty |
| Jumper wires | ~6 | Male-to-male |
| USB cable | 1 | To power and flash the ESP32 |

## Pin mapping

The firmware drives these GPIO pins (defined at the top of
`firmware/traffic_light/traffic_light.ino`):

| Color  | ESP32 GPIO |
| ------ | ---------- |
| Red    | 25         |
| Yellow | 26         |
| Green  | 27         |

All three LEDs share the board's **GND**.

## LED polarity (important)

An LED only lights up one way around:

- **Longer leg = anode (+)** → goes toward the GPIO pin (through the resistor).
- **Shorter leg = cathode (−)** → goes toward GND. The flat side of the LED
  rim is also the cathode.

If an LED doesn't light, the most common cause is that it's in backwards.

## Pin-by-pin wiring

Do this for each of the three LEDs:

1. Put the LED across the breadboard gap so its two legs are on separate rows.
2. Connect a **220 Ω resistor** from the LED's **long leg (+)** to the matching
   GPIO pin:
   - Red LED  → GPIO **25**
   - Yellow LED → GPIO **26**
   - Green LED → GPIO **27**
   (It doesn't matter which end of the resistor is which — resistors aren't
   directional.)
3. Connect the LED's **short leg (−)** to a breadboard ground rail.
4. Finally, run one jumper from the ESP32 **GND** pin to that ground rail so all
   three LEDs share ground.

```
  ESP32 GPIO 25 ──[220Ω]──▶|── GND     (red LED,    ▶| = long leg toward resistor)
  ESP32 GPIO 26 ──[220Ω]──▶|── GND     (yellow LED)
  ESP32 GPIO 27 ──[220Ω]──▶|── GND     (green LED)
```

## Resistor notes

- 220 Ω is a safe, standard value for a single 5 mm LED on 3.3 V logic.
- Anything from ~150 Ω to ~470 Ω works; higher values just make the LED dimmer.
- Never connect an LED directly to a GPIO pin without a resistor — it can
  damage the LED or the pin.

## Test it

After flashing the firmware and wiring everything up, run from your computer:

```bash
~/.claude/light.sh red
~/.claude/light.sh yellow
~/.claude/light.sh green
~/.claude/light.sh off
```

Each command should switch to exactly one LED (or turn them all off).
