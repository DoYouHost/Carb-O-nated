#!/usr/bin/env python3
"""
Generate bitmap assets for ESPHome display to enable GPU-accelerated rendering
instead of CPU-intensive dynamic calculations.
"""
import os
from PIL import Image, ImageDraw
import math

# Create assets directory
os.makedirs('assets', exist_ok=True)

# Display dimensions
WIDTH = 240
HEIGHT = 135

def create_background_gradient():
    """Create gradient background from dark blue-purple at top to slightly lighter at bottom"""
    img = Image.new('RGB', (WIDTH, HEIGHT), (4, 4, 16))
    pixels = img.load()
    
    for y in range(HEIGHT):
        # Subtle gradient from (4,4,16) to (8,8,24)
        r = 4 + int((y / HEIGHT) * 4)
        g = 4 + int((y / HEIGHT) * 4)
        b = 16 + int((y / HEIGHT) * 8)
        for x in range(WIDTH):
            pixels[x, y] = (r, g, b)
    
    img.save('assets/bg_gradient.png')
    print("✓ Created assets/bg_gradient.png")

def create_glow_bars():
    """Create animated glow bars (not used - causes transparency artifacts)"""
    # Glow bars removed due to transparency blending issues
    print("⊘ Skipped assets/glow_bar_*.png (transparency artifacts)")

def create_particles():
    """Create animated particle effects (8 frames for floating particles) - wide coverage"""
    frames = 8
    particle_size = 3
    width = 150  # Much wider area for particles
    height = 20
    
    for frame in range(frames):
        img = Image.new('RGBA', (width, height), (0, 0, 0, 0))
        draw = ImageDraw.Draw(img)
        
        # Create 6 floating particles spread across wider area
        particle_positions = [
            (15, 15 - (frame * 1.5) % 20),   # Rising particle 1 (left)
            (30, 10 + (frame * 1.2) % 18),   # Falling particle 1
            (55, 12 - (frame * 1.8) % 20),   # Rising particle 2 (center-left)
            (80, 8 + (frame * 1.5) % 18),    # Falling particle 2 (center)
            (105, 14 - (frame * 1.3) % 20),  # Rising particle 3 (center-right)
            (130, 9 + (frame * 1.6) % 18),   # Falling particle 3 (right)
        ]
        
        for px, py in particle_positions:
            # Adjust alpha based on position for fade effect
            if py < 0 or py > height:
                continue
            
            # Color transitions through the animation
            hue_shift = (frame * 30) % 360
            if hue_shift < 120:
                color = (100, 200 + int(55 * frame / 8), 255)  # Blue-cyan
            else:
                color = (100, 200 - int(55 * (frame - 4) / 4), 255)  # Back to blue
            
            alpha = int(180 - abs(py - 10) * 15)
            draw.ellipse([(px - particle_size//2, int(py - particle_size//2)), 
                         (px + particle_size//2, int(py + particle_size//2))],
                        fill=(*color, alpha))
        
        img.save(f'assets/particles_{frame:02d}.png')
    print(f"✓ Created assets/particles_*.png ({frames} frames - wide coverage)")

def create_connectors():
    """Create animated connector bezier curves with glowing dots (8 frames)"""
    frames = 8
    width, height = 80, 10
    
    for frame in range(frames):
        img = Image.new('RGBA', (width, height), (0, 0, 0, 0))
        draw = ImageDraw.Draw(img)
        
        # Animated flow position
        flow_pos = (frame / frames)
        
        # Draw smooth bezier-like curve from top to bottom
        for x in range(width):
            # Smooth sine wave curve
            t = x / width
            curve_y = height // 2 + int(3 * math.sin(t * math.pi))
            
            # Main glowing line with gradient
            color_intensity = int(255 * (1 - abs(x - flow_pos * width) / (width * 0.35)))
            if color_intensity > 30:
                # Blue to cyan gradient
                r = 80 + int(50 * t)
                g = 150 + int(100 * t)
                b = 255
                draw.ellipse([(x - 1, curve_y - 1), (x + 1, curve_y + 1)], 
                            fill=(r, g, b, color_intensity))
        
        # Draw flowing energy particle at the flow position
        particle_x = int(flow_pos * width)
        particle_y = height // 2
        # Outer glow
        draw.ellipse([(particle_x - 4, particle_y - 4), (particle_x + 4, particle_y + 4)], 
                    fill=(100, 200, 255, 120))
        # Inner bright core
        draw.ellipse([(particle_x - 2, particle_y - 2), (particle_x + 2, particle_y + 2)], 
                    fill=(200, 240, 255, 255))
        
        img.save(f'assets/connector_{frame:02d}.png')
    print(f"✓ Created assets/connector_*.png ({frames} frames - improved design)")

def create_init_screen():
    """Create init screen background"""
    img = Image.new('RGB', (WIDTH, HEIGHT), (5, 5, 20))
    img.save('assets/init_screen.png')
    print("✓ Created assets/init_screen.png")

def create_bar_segments():
    """Create individual bar segment variations for dynamic bar rendering"""
    seg_w = 11
    seg_h = 11
    
    # Empty segment
    img = Image.new('RGBA', (seg_w, seg_h), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)
    draw.rectangle([(0, 0), (seg_w - 1, seg_h - 1)], fill=(20, 20, 28, 255), outline=(45, 45, 55, 255), width=1)
    img.save('assets/seg_empty.png')
    
    # Filled segments with different colors and pulse levels
    colors = [
        ((0, 255, 51), "green"),   # Excellent (0-25%)
        ((255, 204, 0), "yellow"), # Moderate (25-50%)
        ((255, 102, 0), "orange"), # Poor (50-75%)
        ((255, 0, 0), "red"),      # Critical (75-100%)
    ]
    
    pulse_levels = [0.6, 0.75, 0.9, 1.0]  # Animation frames
    
    for color, name in colors:
        for frame, pulse in enumerate(pulse_levels):
            pulse_color = tuple(int(c * pulse) for c in color)
            img = Image.new('RGBA', (seg_w, seg_h), (0, 0, 0, 0))
            draw = ImageDraw.Draw(img)
            draw.rectangle([(0, 0), (seg_w - 1, seg_h - 1)], fill=(*pulse_color, 255), outline=(45, 45, 55, 255), width=1)
            img.save(f'assets/seg_{name}_{frame}.png')
    
    print("✓ Created assets/seg_*.png (4 colors × 4 pulse frames = 16 segments + 1 empty = 17 assets)")

def create_corner_brackets():
    """Create corner bracket decorations"""
    size = 8
    for corner in ['tl', 'tr', 'bl', 'br']:
        img = Image.new('RGBA', (size, size), (0, 0, 0, 0))
        draw = ImageDraw.Draw(img)
        
        # Draw corner bracket lines based on position
        if 'l' in corner:  # Left
            draw.line([(0, 0), (size, 0)], fill=(100, 200, 255, 255), width=1)
            draw.line([(0, 0), (0, size)], fill=(100, 200, 255, 255), width=1)
        if 'r' in corner:  # Right
            draw.line([(0, 0), (size, 0)], fill=(100, 200, 255, 255), width=1)
            draw.line([(size, 0), (size, size)], fill=(100, 200, 255, 255), width=1)
        if 'b' in corner:  # Bottom
            draw.line([(0, size), (size, size)], fill=(100, 200, 255, 255), width=1)
        
        img.save(f'assets/corner_{corner}.png')
    
    print("✓ Created assets/corner_*.png")

if __name__ == '__main__':
    print("Generating bitmap assets...")
    create_background_gradient()
    create_particles()
    create_init_screen()
    create_bar_segments()  # New: 17 minimal segments instead of 292 full bars
    create_corner_brackets()
    print("\n✓ All assets generated successfully!")
