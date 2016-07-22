void initialize_panels() {
  for (int i = 0; i < panel_count; i++) {
    panels[i] = Adafruit_NeoPixel(panel_pin_counts[i], panel_pins[i], NEO_GRB + NEO_KHZ800);
    panels[i].begin();
  }
  show_all_panels();
}

// Given a colour, change everything to match it and show on each strip
void set_all_panels(uint32_t colour, bool show) {
  int i = 0;
  int p = 0;
  for (i; i < panel_count; i++) for (p = 0; p < panels[i].numPixels(); p++) panels[i].setPixelColor(p, colour);
  if (show) show_all_panels();
}
void set_all_panels(uint32_t colour) { set_all_panels(colour, DEFAULT_SHOW_ON_SET_ALL); } // Overloading to allow for default always show setting
void show_all_panels() { for (int i; i < panel_count; i++) panels[i].show(); }

void set_panel_pixels(int panel, uint32_t colour, bool show) {
  int p = 0;
  if (panel < panel_count) {
    for (p = 0; p < panels[panel].numPixels(); p++) panels[panel].setPixelColor(p, colour);
    if (show) show_panel_pixels(panel);
  }
}
void set_panel_pixels(int panel, uint32_t colour) { set_panel_pixels(panel, colour, DEFAULT_SHOW_ON_SET_STRIP); } // Overloading to allow for default always show setting
void show_panel_pixels(int panel) { panels[panel].show(); }
