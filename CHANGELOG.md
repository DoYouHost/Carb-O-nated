# 2026.3
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
