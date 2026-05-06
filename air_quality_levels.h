#pragma once

enum CO2LevelType {
  CO2_UNKNOWN,
  CO2_PERFECT,
  CO2_EXCELLENT,
  CO2_MODERATE,
  CO2_POOR,
  CO2_VERY_POOR
};

struct CO2Level {
  CO2LevelType type;
  Color color;
  Color bg_dim;
};

inline CO2Level get_co2_level(float co2_value) {
  CO2Level level;
  
  if (isnan(co2_value)) {
    level.type = CO2_UNKNOWN;
    level.color = Color(100, 100, 100);
    level.bg_dim = Color(20, 20, 20);
  } else if (co2_value < 400) {
    level.type = CO2_PERFECT;
    level.color = Color(0, 255, 51);  // color_excellent
    level.bg_dim = Color(0, 40, 10);
  } else if (co2_value < 1000) {
    level.type = CO2_EXCELLENT;
    level.color = Color(0, 255, 51);  // color_excellent
    level.bg_dim = Color(0, 40, 10);
  } else if (co2_value < 1500) {
    level.type = CO2_MODERATE;
    level.color = Color(255, 204, 0);  // color_moderate
    level.bg_dim = Color(40, 32, 0);
  } else if (co2_value < 2000) {
    level.type = CO2_POOR;
    level.color = Color(255, 102, 0);  // color_poor
    level.bg_dim = Color(40, 16, 0);
  } else {
    level.type = CO2_VERY_POOR;
    level.color = Color(255, 0, 0);  // color_very_poor
    level.bg_dim = Color(40, 0, 0);
  }
  
  return level;
}

inline CO2Level get_co2_level_cached(float co2_value) {
  static CO2Level cached_level = get_co2_level(NAN);
  static float cached_co2 = NAN;

  bool value_changed = (std::isnan(co2_value) != std::isnan(cached_co2)) ||
                       (!std::isnan(co2_value) && std::abs(co2_value - cached_co2) > 0.01f);
  if (value_changed) {
    cached_level = get_co2_level(co2_value);
    cached_co2 = co2_value;
  }
  return cached_level;
}

// ── CO (Carbon Monoxide) ─────────────────────────────────────────────────────
// Unit: ppm  |  Sensor: MQ-7
//   WHO 2021 24h mean:   3.5 ppm   (long-term health guideline)
//   EU 2008   8h mean:   8.7 ppm   (current legal limit)
//   UL 2034 alarms:     50–70 ppm @ 60–240 min  (residential CO alarm spec)
//   UL 2034 alarms:    >150 ppm   (must alarm within 50 min)
// CO2_EXCELLENT reused as "Good" (no CO2_PERFECT tier for CO).
inline CO2Level get_co_level(float value) {
  CO2Level level;
  if (isnan(value)) {
    level.type = CO2_UNKNOWN;
    level.color = Color(100, 100, 100);
    level.bg_dim = Color(20, 20, 20);
  } else if (value < 4.0f) {
    // Below WHO long-term guideline (3.5 ppm)
    level.type = CO2_EXCELLENT;
    level.color = Color(0, 255, 51);
    level.bg_dim = Color(0, 40, 10);
  } else if (value < 8.5f) {
    // Approaching EU 8h legal limit (8.7 ppm)
    level.type = CO2_MODERATE;
    level.color = Color(255, 204, 0);
    level.bg_dim = Color(40, 32, 0);
  } else if (value < 12.0f) {
    // Above EU legal limit, below UL 2034 alarm thresholds
    level.type = CO2_POOR;
    level.color = Color(255, 102, 0);
    level.bg_dim = Color(40, 16, 0);
  } else {
    // UL 2034 alarm range — immediate ventilation required
    level.type = CO2_VERY_POOR;
    level.color = Color(255, 0, 0);
    level.bg_dim = Color(40, 0, 0);
  }
  return level;
}

inline CO2Level get_co_level_cached(float value) {
  static CO2Level cached = {CO2_UNKNOWN, Color(100, 100, 100), Color(20, 20, 20)};
  static float cached_val = NAN;
  bool changed = (std::isnan(value) != std::isnan(cached_val)) ||
                 (!std::isnan(value) && std::abs(value - cached_val) > 0.01f);
  if (changed) { cached = get_co_level(value); cached_val = value; }
  return cached;
}

// Returns the worse of two CO2LevelType values (higher enum = worse quality).
// CO2_UNKNOWN is treated as "no data" — the other value wins.
inline CO2LevelType worst_aq_level(CO2LevelType a, CO2LevelType b) {
  if (a == CO2_UNKNOWN) return b;
  if (b == CO2_UNKNOWN) return a;
  return (a > b) ? a : b;
}

inline Color get_level_color(CO2LevelType t) {
  switch (t) {
    case CO2_PERFECT:
    case CO2_EXCELLENT: return Color(0,   255, 51);
    case CO2_MODERATE:  return Color(255, 204, 0);
    case CO2_POOR:      return Color(255, 102, 0);
    case CO2_VERY_POOR: return Color(255, 0,   0);
    default:            return Color(100, 100, 100);
  }
}
