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

CO2Level get_co2_level(float co2_value) {
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
