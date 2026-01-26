code = """      // === SEGMENTED BAR (y: 97-109, safe zone) - scales 0-3000 ppm ===
      int max_co2 = 3000;
      float pct = min(1.0f, co2 / max_co2);
      int segments = 18;
      int filled = (int)((segments * 4) * pct);  // 72 sub-levels for 4x granularity
      if (filled > 72) filled = 72;
      int anim_frame = (t / 150) % 4;  // 4 animation frames, ~600ms cycle
      
      // Use full animated bar image instead of drawing individual segments
      // Using 292 total assets (73 fill levels 0-72 × 4 animation frames)
      switch(filled) {
"""
for i in range(73):
    fmt = f"{i:02d}"
    code += f"        case {i}: it.image(7, 97, anim_frame == 0 ? id(bar_{fmt}_0) : anim_frame == 1 ? id(bar_{fmt}_1) : anim_frame == 2 ? id(bar_{fmt}_2) : id(bar_{fmt}_3)); break;\n"
code += "      }"

with open("bar_code.txt", "w") as f:
    f.write(code)

print("✓ Generated new bar switch code")
