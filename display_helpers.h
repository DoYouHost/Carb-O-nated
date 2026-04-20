#pragma once

#include <algorithm>
#include <cmath>

template<typename Display>
inline void draw_co2_bar(Display &it, float co2, Color fill_color, Color dim_color) {
  constexpr int segments = 18;
  constexpr int seg_w = 11;
  constexpr int seg_h = 13;
  constexpr int seg_gap = 1;
  constexpr int bar_x = 7;
  constexpr int bar_y = 97;
  constexpr int max_co2 = 3000;

  float pct = (!std::isnan(co2) && co2 > 0.0f) ? std::min(1.0f, co2 / (float) max_co2) : 0.0f;
  int filled_quarters = (int) ((segments * 4) * pct);
  if (filled_quarters > segments * 4) filled_quarters = segments * 4;

  for (int s = 0; s < segments; s++) {
    int sx = bar_x + s * (seg_w + seg_gap);
    int seg_quarters = s * 4;

    if (seg_quarters + 4 <= filled_quarters) {
      it.filled_rectangle(sx, bar_y, seg_w, seg_h, fill_color);
    } else if (seg_quarters < filled_quarters) {
      int part = filled_quarters - seg_quarters;
      int fill_w = (seg_w * part) / 4;
      if (fill_w > 0) {
        it.filled_rectangle(sx, bar_y, fill_w, seg_h, fill_color);
      }
      if (fill_w < seg_w) {
        it.rectangle(sx + fill_w, bar_y, seg_w - fill_w, seg_h, dim_color);
      }
    } else {
      it.rectangle(sx, bar_y, seg_w, seg_h, dim_color);
    }
  }
}
