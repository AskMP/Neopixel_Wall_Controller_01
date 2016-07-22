int current_frame = 0;
int max_frames = 1;
int current_animation = 0;

// Some basic colours for easy access
#define WHITE  0xFFFFFF
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define BRAND  0xC9CC00

void initialize_animations() {
  current_animation = STARTING_ANIMATION || 0;
  randomSeed(analogRead(0));
  if (current_animation != 0) {
    cmd = String(current_animation);
    process_command();
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
    default:
      current_frame = 0;
  }
  current_frame += (current_frame < max_frames) ? 1 : -1 * max_frames;
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

