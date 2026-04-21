# Carb-O-nated

A smart indoor CO₂ monitor built on ESP32 with a color display, Home Assistant integration, and multi-language support.

## What it does

Carb-O-nated continuously measures CO₂ concentration in the air and displays it on a compact color LCD. The display updates in real time with a large, easy-to-read ppm value and a color that reflects air quality at a glance — green for fresh air, yellow through red as CO₂ builds up.

All data is pushed to Home Assistant, enabling automations such as ventilation alerts, notifications, or fan control based on CO₂ thresholds.

## Display

The screen shows:

- **CO₂ value** — large central readout in ppm
- **Quality label** — text status above the value (e.g. *Perfect*, *Excellent*, *Moderate*, *Poor*, *Very Poor*)
- **Bar graph** — 18-segment level indicator spanning 0–3000 ppm
- **Unit strip** — animated bottom bar with "ppm CO₂" label

Colors update automatically based on CO₂ level:

| Level | Range | Color |
|---|---|---|
| Perfect | < 400 ppm | Green |
| Excellent | 400–1000 ppm | Green |
| Moderate | 1000–1500 ppm | Yellow |
| Poor | 1500–2000 ppm | Orange |
| Very Poor | > 2000 ppm | Red |

## Sensors

The device uses a **SCD4x** sensor to measure:

- CO₂ concentration (ppm)
- Temperature (°C)
- Relative humidity (%)

Readings are taken every 5 seconds, smoothed with an exponential moving average, and published to Home Assistant every 30 seconds.

## Controls

| Button | Action |
|---|---|
| Button A | Toggle display backlight on/off |
| Button B | None right now |

## Home Assistant integration

All sensor values are available as entities in Home Assistant. Additional controls exposed:

- **CO₂ air quality** — text status entity
- **Temperature / humidity offsets** — number sliders for calibration (±10 °C, ±20 %)
- **Language selector** — English, Polish, German, French, Spanish
- **Buzzer switch** — enable or disable audio feedback
- **SCD4x factory reset** — clear sensor calibration
- **Ambient pressure input** — API action for barometric compensation
- **Restart / safe mode / factory reset** — device management buttons


