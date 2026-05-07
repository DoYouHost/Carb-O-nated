#pragma once

#include <algorithm>
#include <cmath>
#include <initializer_list>

#include "air_quality_levels.h"

// Display helpers — shared across all Carb-O-nated variants.
// TFT-specific:   get_level_color, get_level_bg_dim, draw_co2_bar
// E-ink-specific: draw_sensor_cell, level_ratio
// Universal:      worst_level, update_trend, trend_glyph

// ── Worst level ───────────────────────────────────────────────────────────────
inline AirQualityLevelType worst_level(std::initializer_list<AirQualityLevelType> levels) {
  AirQualityLevelType worst = AQ_UNKNOWN;
  for (auto l : levels) { if (l > worst) worst = l; }
  return worst;
}

// ── TFT: RGB color mapping ────────────────────────────────────────────────────
inline esphome::Color get_level_color(AirQualityLevelType t) {
  switch (t) {
    case AQ_GOOD:      return esphome::Color(0,   255, 51);
    case AQ_MODERATE:  return esphome::Color(255, 204, 0);
    case AQ_POOR:      return esphome::Color(255, 102, 0);
    case AQ_VERY_POOR: return esphome::Color(255, 0,   0);
    default:           return esphome::Color(100, 100, 100);
  }
}

// Dimmed background variant for dark UI panels.
inline esphome::Color get_level_bg_dim(AirQualityLevelType t) {
  switch (t) {
    case AQ_GOOD:      return esphome::Color(0,  40, 10);
    case AQ_MODERATE:  return esphome::Color(40, 32, 0);
    case AQ_POOR:      return esphome::Color(40, 16, 0);
    case AQ_VERY_POOR: return esphome::Color(40, 0,  0);
    default:           return esphome::Color(20, 20, 20);
  }
}

// ── TFT: segmented CO2 bar ────────────────────────────────────────────────────
// Fixed layout for 240×135 (Carb-O-nated base).
template<typename Display>
inline void draw_co2_bar(Display &it, float co2, esphome::Color fill_color, esphome::Color dim_color) {
  constexpr int segments = 18, seg_w = 11, seg_h = 13, seg_gap = 1;
  constexpr int bar_x = 12, bar_y = 97, max_co2 = 3000;

  float pct = (!std::isnan(co2) && co2 > 0.0f) ? std::min(1.0f, co2 / (float)max_co2) : 0.0f;
  int fq = std::min((int)((segments * 4) * pct), segments * 4);

  for (int s = 0; s < segments; s++) {
    int sx = bar_x + s * (seg_w + seg_gap);
    int sq = s * 4;
    if (sq + 4 <= fq) {
      it.filled_rectangle(sx, bar_y, seg_w, seg_h, fill_color);
    } else if (sq < fq) {
      int fw = (seg_w * (fq - sq)) / 4;
      if (fw > 0)      it.filled_rectangle(sx,      bar_y, fw,         seg_h, fill_color);
      if (fw < seg_w)  it.rectangle(sx + fw, bar_y, seg_w - fw, seg_h, dim_color);
    } else {
      it.rectangle(sx, bar_y, seg_w, seg_h, dim_color);
    }
  }
}

// ── E-ink: level bar ratio ────────────────────────────────────────────────────
// Maps a sensor value to 0..1 piecewise across 4 tiers (each = 0.25 of the range).
inline float level_ratio(float value, float good, float moderate, float poor, float vmax) {
  if (std::isnan(value) || value <= 0.0f) return 0.0f;
  float r;
  if      (value < good)     r = 0.25f * (value / good);
  else if (value < moderate) r = 0.25f + 0.25f * ((value - good)     / (moderate - good));
  else if (value < poor)     r = 0.50f + 0.25f * ((value - moderate) / (poor - moderate));
  else { float span = std::max(1e-3f, vmax - poor);
         r = 0.75f + 0.25f * std::min(1.0f, (value - poor) / span); }
  return std::max(0.0f, std::min(1.0f, r));
}

// ── E-ink: sensor cell ────────────────────────────────────────────────────────
// Draws: icon (top-left), optional label, centered value at (cx, y_val),
// unit at (cx, y_unit), optional filled level bar.
inline void draw_sensor_cell(esphome::display::Display &it,
                      int cx, int icon_x, int icon_y,
                      esphome::font::Font *icon_font, esphome::font::Font *label_font,
                      esphome::font::Font *value_font, esphome::font::Font *unit_font,
                      esphome::Color icon_color, esphome::Color value_color,
                      esphome::Color unit_color, esphome::Color bar_color,
                      const char *icon_glyph, const char *label, int label_x, int label_y,
                      const char *value_fmt, float value, int y_val, int y_unit,
                      const char *unit_str, int bar_x, int bar_y, int bar_w, int bar_h,
                      float ratio) {
  it.print(icon_x, icon_y, icon_font, icon_color, esphome::display::TextAlign::TOP_LEFT, icon_glyph);
  if (label != nullptr)
    it.printf(label_x, label_y, label_font, icon_color, esphome::display::TextAlign::TOP_LEFT, "%s", label);
  if (std::isnan(value))
    it.printf(cx, y_val, value_font, value_color, esphome::display::TextAlign::CENTER, "--");
  else
    it.printf(cx, y_val, value_font, value_color, esphome::display::TextAlign::CENTER, value_fmt, value);
  it.printf(cx, y_unit, unit_font, unit_color, esphome::display::TextAlign::CENTER, "%s", unit_str);

  if (ratio >= 0.0f && bar_w > 0 && bar_h > 0) {
    int filled = (int)std::round(std::max(0.0f, std::min(1.0f, ratio)) * (float)bar_w);
    it.rectangle(bar_x, bar_y, bar_w, bar_h, bar_color);
    if (filled > 0) it.filled_rectangle(bar_x, bar_y, filled, bar_h, bar_color);
  }
}

// ── Trend arrows ──────────────────────────────────────────────────────────────
enum TrendDir { TREND_FLAT, TREND_UP, TREND_DOWN };

inline TrendDir update_trend(float value, float &prev_ref, float epsilon) {
  if (std::isnan(value)) return TREND_FLAT;
  TrendDir dir = TREND_FLAT;
  if (!std::isnan(prev_ref)) {
    float delta = value - prev_ref;
    if      (delta >  epsilon) dir = TREND_UP;
    else if (delta < -epsilon) dir = TREND_DOWN;
  }
  prev_ref = value;
  return dir;
}

// MDI glyphs: menu-up=U+F035D, menu-down=U+F035B, minus=U+F0374
inline const char* trend_glyph(TrendDir d) {
  switch (d) {
    case TREND_UP:   return "\U000F035D";
    case TREND_DOWN: return "\U000F035B";
    default:         return "\U000F0374";
  }
}
