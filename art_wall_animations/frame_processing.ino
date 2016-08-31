int current_frame = 0;
int max_frames = 1;
int current_animation = 0;
int animation_data1 = 0;
int animation_data2 = 0;
int animation_data3 = 0;
int animation_data4 = 0;
int animation_data5 = 0;
int animation_data6 = 0;

uint32_t animation_colour1 = 0;
uint32_t animation_colour2 = 0;

bool useBrand1 = false;

void initialize_animations() {
  current_animation = STARTING_ANIMATION;
  randomSeed(analogRead(0));
  if (current_animation != 0) {
    cmd = String(current_animation);
    process_command();
    cmd = "";
  }
}

// Always run this method every loop.
void next_frame() {
  switch (current_animation) {
    case 1:
      basic_rainbow_animation_frame();
      break;
    case 2:
      unique_rainbow_animation_frame();
      break;
    case 3:
      sparkle_animation();
      break;
    case 4:
      chase_animation();
      break;
    case 5:
      pulse_panel();
      break;
    case 6:
      panel_flash();
      break;
    case 7:
      solid_colour();
      break;
    case 8:
      even_odd_branding();
      break;
    case 9:
      panel_rainbow();
      break;
    default:
      current_frame = 0;
  }
  current_frame += (current_frame < max_frames) ? 1 : -1 * max_frames;
}

void init_off() {
  set_all_panels(0, true);
  current_animation = 0;
  current_frame = 0;
}

/***
 * Sets all panels to the same rainbow colour and animate per the frame rate.
 */
void init_basic_rainbow_animation() {
  FPS = 60;
  current_animation = 1;// The animation ID
  current_frame = 0;    // Reset the current frame location
  max_frames = 254;     // We use 255 steps as a max since we will be using it for colour location from 0 to 255 (256 colours)
}
void basic_rainbow_animation_frame() {
  // Use the current frame to get the colour position and set all pixels to it
  set_all_panels(Wheel(current_frame), true);
  current_frame += 4; // Added for faster FPS
}

/***
 * Set each panel to a unique colour of the rainbow and animate per the frame rate.
 */
void init_unique_rainbow_animation() {
  FPS = 60;
  current_animation = 2;// The animation ID
  current_frame = 0;    // Reset the current frame location
  max_frames = 255;     // We use 255 steps as a max since we will be using it for colour location from 0 to 255 (256 colours)
}
void unique_rainbow_animation_frame() {
  // Using the current frame capture the colour at the index of 0 to 254 of the colour wheel
  int col;
  int division = max_frames / panel_count;
  for (int p = 0; p < panel_count; p++) {
    col = division * p + current_frame;
    col -= (col >= 255) ? 255 : 0;
    set_panel_pixels(p, Wheel(col));
  }
  current_frame += 4; // Added for faster FPS
}
/***
 * 
 */
void init_sparkle_animation() {
  FPS = 60;
  current_animation = 3;
  current_frame = 0;
  max_frames = FPS / 2;
}

void sparkle_animation() {
  int rgb[3];
  float density = 0.2;
  
  int decrease_step = int(255 / max_frames);
  for (int p = 0; p < panel_count; p++) {
    for (int i = 0; i < panels[p].numPixels(); i++) {
      if (panels[p].getPixelColor(i) > 0) {
        toRGB(panels[p].getPixelColor(i), &rgb[0], &rgb[1], &rgb[2]);
        rgb[0] -= (rgb[0] <= decrease_step) ? decrease_step : rgb[0];
        rgb[1] -= (rgb[1] <= decrease_step) ? decrease_step : rgb[1];
        rgb[2] -= (rgb[2] <= decrease_step) ? decrease_step : rgb[2];
        panels[p].setPixelColor(i, Color(rgb[0], rgb[1], rgb[2]));
      }
    }
    for (int i = 0; i < int(panels[p].numPixels() * density); i++) {
      panels[p].setPixelColor(int(random(panels[p].numPixels())), WHITE);
    }
    panels[p].show();
  }
}

/***
 * 
 */
void init_chase_animation() {
  useBrand1 = !useBrand1;
  animation_colour1 = (useBrand1) ? BRAND1 : BRAND2;
  init_colour_chase_animation(animation_colour1);
}

void init_colour_chase_animation(uint32_t colour) {
  FPS = 60;
  current_animation = 4;
  current_frame = 0;
  max_frames = 54;
  set_all_panels(0, true);
  animation_colour1 = colour;
}

void chase_animation() {
  int curr = current_frame;
  for (int p = 0; p < panel_count; p++) {
    for (int i = 0; i < panels[p].numPixels(); i ++) {
      if (curr % 5 == 0) {
        panels[p].setPixelColor(i, animation_colour1);
      } else {
        panels[p].setPixelColor(i, 0);
      }
      curr++;
    }
  }
  show_all_panels();
};

void init_pulse_panel() {
  current_animation = 5;
  current_frame = 0;
  max_frames = 100;
  animation_data1 = 0;
  animation_data2 = 0;
  animation_data3 = 0;
  animation_data4 = 0;
  animation_data5 = 0;
  animation_data6 = 0;
  set_all_panels(0, true);
}

void pulse_panel() {
  int possiblePanels[panel_count] = {-1};
  int currPanels[6] = {
    animation_data1,
    animation_data2,
    animation_data3,
    animation_data4,
    animation_data5,
    animation_data6
  };
  int rgb[3];
  double multiplier = (double(100 / double(max_frames / 2)) * double((max_frames / 2) - abs((max_frames / 2) - current_frame))) / 100;
  if (current_frame == 0) {
    for (int p = 0; p < panel_count; p++) possiblePanels[p] = p;
    size_t n = sizeof(possiblePanels) / sizeof(possiblePanels[0]);
    for (size_t pp = 0; pp < n; pp++) {
      size_t new_pp = random(0, n - 1);
      int t = possiblePanels[pp];
      possiblePanels[pp] = possiblePanels[new_pp];
      possiblePanels[new_pp] = t;
    }
    for (int cp = 0; cp < sizeof(currPanels); cp++) {
      currPanels[cp] = possiblePanels[cp];
    }
    animation_data1 = currPanels[0];
    animation_data2 = currPanels[1];
    animation_data3 = currPanels[2];
    animation_data4 = currPanels[3];
    set_all_panels(0, true);
    animation_colour1 = Wheel(random(254));
  }
  toRGB(animation_colour1, &rgb[0], &rgb[1], &rgb[2]);
  for (int p = 0; p < sizeof(currPanels); p++) {
    set_panel_pixels(currPanels[p], Color(rgb[0] * multiplier, rgb[1] * multiplier, rgb[2] * multiplier), true);
  }
}

void init_panel_flash(int panel_qty, bool randomize) {
  current_animation = 6;
  current_frame = 0;
  max_frames = 1;
  animation_data1 = panel_qty;
  animation_data2 = (randomize) ? 1 : 0;
  set_all_panels(0, true);
}

void panel_flash() {
  set_all_panels(0, true);
  int animation_panels[panel_count] = {-1};
  int curr_panel = 0;
  uint32_t curr_colour = 0;
  for (int i = 0; i < animation_data1; i++) {
    curr_panel = random(panel_count);
    for (int p = 0; p < animation_data1; p++) {
      while (curr_panel == animation_panels[p]) curr_panel = random(panel_count);
    }
    curr_colour = (animation_data2 == 1) ? Wheel(random(254)) : WHITE;
    //curr_colour = (animation_data2 == 1) ? random(2) == 1 ? BRAND1 : BRAND2 : WHITE;
    set_panel_pixels(curr_panel, curr_colour);
  }
  if (animation_data2 == 1) {
    delay(1000 / 10);
  } else {
    delay(1000 / 15);
  }
  
}

void init_solid_colour(uint32_t colour) {
  current_animation = 7;
  animation_colour1 = colour;
  current_frame = 0;
  max_frames = 1;
}

void solid_colour() {
  set_all_panels(animation_colour1, true);
}

void init_even_odd_branding() {
  current_animation = 8;
  animation_colour1 = BRAND1;
  animation_colour2 = BRAND2;
  current_frame = 0;
  max_frames = 54;
}

void even_odd_branding() {
  int curr = 0;
  uint32_t curr_colour = 0;
  for (int p = 0; p < panel_count; p++) {
    curr_colour = (p % 2 == 1) ? animation_colour1 : animation_colour2;
    curr = current_frame;
    for (int i = 0; i < panels[p].numPixels(); i++) {
      if (curr % 7 == 0) {
        panels[p].setPixelColor(i, curr_colour);
      } else {
        panels[p].setPixelColor(i, 0);
      }
      curr++;
    }
    show_panel_pixels(p);
  }
}

void init_panel_rainbow() {
  current_animation = 9;
  max_frames = 255;
  current_frame = 0;
}

void panel_rainbow() {
  int i = 0;
  int p = 0;
  int wheelPos = 0;
  for (p = 0; p < panel_count; p++) {
    for (i = 0; i < panels[p].numPixels(); i ++) {
      wheelPos = 255 / panels[p].numPixels() * i + current_frame;
      panels[p].setPixelColor(i, Wheel(wheelPos));
    }
    show_panel_pixels(p);
  }
  current_frame += 4;
}

