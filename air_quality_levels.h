#pragma once

// Air quality level definitions — shared across all Carb-O-nated variants.
//
// Sources:
//   CO2:      ASHRAE 62.1 / EN 16798-1 (indoor air quality)
//   CO:       WHO 2021 / EU 2008 Directive / UL 2034 alarm thresholds
//   PM2.5/10: EU Directive 2008/50/EC and 2024/2881 / WHO AQG 2021
//   VOC:      Sensirion VOC Index / German Federal Environment Agency
//
// BWR e-ink: use_red selects red ink.
// RGB TFT:   derive color via get_level_color() / get_level_bg_dim() in display_helpers.h.

enum AirQualityLevelType {
  AQ_UNKNOWN,
  AQ_GOOD,
  AQ_MODERATE,
  AQ_POOR,
  AQ_VERY_POOR
};

struct AirQualityLevel {
  AirQualityLevelType type;
  bool use_red;
};

// ── CO2 ───────────────────────────────────────────────────────────────────────
// Sensor: SCD41  |  Unit: ppm
//   Outdoor baseline ~420 ppm (2024)
//   ASHRAE 62.1 / EN 16798: <1000 acceptable, 1000–1500 moderate, >1500 poor
inline AirQualityLevel get_co2_level(float v) {
  if (isnan(v))     return {AQ_UNKNOWN,   false};
  if (v < 1000.0f)  return {AQ_GOOD,      false};
  if (v < 1500.0f)  return {AQ_MODERATE,  false};
  if (v < 2000.0f)  return {AQ_POOR,      true};
  return              {AQ_VERY_POOR, true};
}
inline AirQualityLevel get_co2_level_cached(float v) {
  static AirQualityLevel c = {AQ_UNKNOWN, false}; static float cv = NAN;
  if ((std::isnan(v) != std::isnan(cv)) || (!std::isnan(v) && std::abs(v - cv) > 0.01f)) { c = get_co2_level(v); cv = v; }
  return c;
}

// ── CO ────────────────────────────────────────────────────────────────────────
// Sensor: MQ-7  |  Unit: ppm
//   WHO 2021 24h mean: 3.5 ppm  |  EU 2008 8h mean: 8.7 ppm  |  UL 2034: 50–150 ppm alarm
// Red reserved for genuinely concerning levels — avoids false alerts from cooking/heating noise.
inline AirQualityLevel get_co_level(float v) {
  if (isnan(v))      return {AQ_UNKNOWN,   false};
  if (v < 4.0f)      return {AQ_GOOD,      false};
  if (v < 8.5f)      return {AQ_MODERATE,  false};
  if (v < 12.0f)     return {AQ_POOR,      true};
  return               {AQ_VERY_POOR, true};
}
inline AirQualityLevel get_co_level_cached(float v) {
  static AirQualityLevel c = {AQ_UNKNOWN, false}; static float cv = NAN;
  if ((std::isnan(v) != std::isnan(cv)) || (!std::isnan(v) && std::abs(v - cv) > 0.01f)) { c = get_co_level(v); cv = v; }
  return c;
}

// ── PM2.5 ─────────────────────────────────────────────────────────────────────
// Sensor: SEN54 (Pro) / simple PM sensor (Plus)  |  Unit: µg/m³
//   WHO 2021 annual: 5 µg/m³  |  EU 2030 annual: 10 µg/m³  |  EU 2030 daily: 25 µg/m³
//   EU 2008 (current): annual 25 µg/m³
inline AirQualityLevel get_pm25_level(float v) {
  if (isnan(v))      return {AQ_UNKNOWN,   false};
  if (v < 5.0f)      return {AQ_GOOD,      false};
  if (v < 10.0f)     return {AQ_MODERATE,  false};
  if (v < 25.0f)     return {AQ_POOR,      true};
  return               {AQ_VERY_POOR, true};
}
inline AirQualityLevel get_pm25_level_cached(float v) {
  static AirQualityLevel c = {AQ_UNKNOWN, false}; static float cv = NAN;
  if ((std::isnan(v) != std::isnan(cv)) || (!std::isnan(v) && std::abs(v - cv) > 0.1f)) { c = get_pm25_level(v); cv = v; }
  return c;
}

// ── PM10 ──────────────────────────────────────────────────────────────────────
// Sensor: SEN54 (Pro only)  |  Unit: µg/m³
//   WHO 2021 annual: 15 µg/m³  |  EU 2030 annual: 20 µg/m³  |  EU 2030 daily: 45 µg/m³
//   EU 2008 (current): daily 50 µg/m³, annual 40 µg/m³
inline AirQualityLevel get_pm10_level(float v) {
  if (isnan(v))       return {AQ_UNKNOWN,   false};
  if (v < 15.0f)      return {AQ_GOOD,      false};
  if (v < 20.0f)      return {AQ_MODERATE,  false};
  if (v < 45.0f)      return {AQ_POOR,      true};
  return                {AQ_VERY_POOR, true};
}
inline AirQualityLevel get_pm10_level_cached(float v) {
  static AirQualityLevel c = {AQ_UNKNOWN, false}; static float cv = NAN;
  if ((std::isnan(v) != std::isnan(cv)) || (!std::isnan(v) && std::abs(v - cv) > 0.1f)) { c = get_pm10_level(v); cv = v; }
  return c;
}

// ── VOC Index ─────────────────────────────────────────────────────────────────
// Sensor: SEN54 (Pro only)  |  Unit: dimensionless 0–500 (Sensirion VOC Index)
//   100 = 24h rolling baseline  |  >100 = deteriorating  |  <100 = improving
inline AirQualityLevel get_voc_level(float v) {
  if (isnan(v))        return {AQ_UNKNOWN,   false};
  if (v <= 100.0f)     return {AQ_GOOD,      false};
  if (v <= 150.0f)     return {AQ_MODERATE,  false};
  if (v <= 250.0f)     return {AQ_POOR,      true};
  return                 {AQ_VERY_POOR, true};
}
inline AirQualityLevel get_voc_level_cached(float v) {
  static AirQualityLevel c = {AQ_UNKNOWN, false}; static float cv = NAN;
  if ((std::isnan(v) != std::isnan(cv)) || (!std::isnan(v) && std::abs(v - cv) > 0.5f)) { c = get_voc_level(v); cv = v; }
  return c;
}
