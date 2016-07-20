int current_frame = 0;
int max_frames = 1;
int current_animation = 0;

// Some basic colours for easy access
#define WHITE = 0xFFFFFF;
#define RED   = 0xFF0000;
#define GREEN = 0x00FF00;
#define BLUE  = 0x0000FF;
#define BRAND = 0xC9CC00;

void initialize_animations() {
  current_animation = STARTING_ANIMATION || 0;
  if (current_animation != 0) {
    cmd = String(current_animation);
    process_command();
  }
}

// Always run this method every loop.
void next_frame() {
  current_frame += (current_frame < max_frames) ? 1 : -1 * max_frames;
  switch (current_animation) {
    case 1:
      basic_rainbow_animation_frame();
      break;
    case 2:
      unique_rainbow_animation_frame();
      break;
  }
}

/***
 * Sets all panels to the same rainbow colour and animate per the frame rate.
 */
void init_basic_rainbow_animation() {
  current_animation = 1;
  current_frame = 0;
  max_frames = 254;
}
void basic_rainbow_animation_frame() {
  // Use the current frame to get the colour position and set all pixels to it
  set_all_panels(Wheel(current_frame), true);
}

/***
 * Set each panel to a unique colour of the rainbow and animate per the frame rate.
 */
void init_unique_rainbow_animation() {
  current_animation = 2;
  current_frame = 0;
  max_frames = 254;
}
void unique_rainbow_animation_frame() {
  // Using the current frame capture the colour at the index of 0 to 254 of the colour wheel
  for (int p = 0; p < panel_count; p++) set_panel_pixels(Wheel(int(max_frames / panel_count * p) + current_frame), false);
  show_all_panels();
}

