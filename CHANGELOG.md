
# 2026.5
## .5
- feat: show mdi:fire icon in display header when MQ-7 heater is active
- feat: add Bluetooth proxy with active BLE scanning
## .4
- feat: update to ESPHome 2026.4.5
- fix: blank screen after backlight re-enable — page lambdas now check `remote_values` instead of `current_values`
- fix: eliminate double render on page change by removing `on_page_change` component.update
- fix: add missing diacritical glyphs for PL/DE/FR/ES to all text-rendering fonts
## .3
- feat: move to Carb-O-nated-Common repo for shared assets and code
## .2
- feat: redesign main_page — left accent strip, centered CO₂ value, segmented bar, CO footer
- feat: redesign info_page — 2×2 grid with per-sensor accent bars and fill backgrounds
- feat: add Light On/Off Time inputs and LED Strip / Backlight Auto switches with scheduled control
- feat: add MQ-7 CO sensor with temperature/humidity compensation
- feat: add WS2812B wave effect colored by air quality level
- feat: add init screen during sensor warm-up
- feat: event-driven display updates
## .1
- feat: add buzzer confirmation switch and move pin assignments to substitutions
- feat: update to ESPHome 2026.4.3
## .0
- feat: add info page with CO2/temp/humidity and page cycling
  - display.pages: wrap existing view as `main_page`, add `info_page` with three rows and a slow top→bottom accent wave
  - Button B and new "Next Page" HA template button cycle pages
  - Gate page cycling on `init_done` flag (first valid CO2 reading) so UI stays on main_page during warm-up
- fix: trigger firmware update check on SNTP sync to avoid TLS failure before clock is set; add 22:00 daily recheck
- fix: add digits to roboto_bold_25 / roboto_medium_20 glyph sets
# 2026.4
## .2
- fix: center segments on display
## .1
- perf: render display with native primitives, drop image assets
## .0
- feat: update to ESPHome 2026.4.1
- feat: add display backlight toggle to Button A
# 2026.3
## .6 
- fix: correct offset value for temperature and humidity
## .5
- fix: initial value for humidity and temperature
- feat: update to ESPHome 2026.3.3
## .4
- feat: add temperature and humidity calibration offsets
## .3
- fix: remove improv authorizer requirement
## .2
- feat: add buzzer support and update ESPHome to 2026.3.1
## .1
- feat: update to ESPHome 2026.2.4
## .0
- fix: switch SCD4x to periodic mode with tuned filters
  - measurement_mode: single_shot → periodic (5s cadence)
  - update_interval: 15s → 5s
  - skip_initial: 4 → 12 (maintains ~60s warm-up)
  - alpha: 0.1 → 0.3 (faster response to changes)
  - send_every: 12 → 6 (publish every 30s)
  - Enable temperature and humidity sensors with matching filter config
# 2026.1
## .4
- fix: invert status LED pin logic
## .3
- fix: correct manifest URL path casing
## .2
- feat: add factory reset button for SCD4x sensor and status LED configuration
- feat: add remote theme
## .1
- feat: Update animated bar assets and optimize display logic
- refactor: remove unused assets
- feat: Add lookup tables for pre-computed sin/cos values and update display calculations
- feat: Add asset generation script for bitmap assets and animated bar graphics
## .0
- Initial release.
