/*****
 * Most of the functionality is spread into individual tabs pertaining 
 * to their usage. All non-standard or library methods use a PHP style
 * underscore method of seperating words rather than the camelCase method
 * employed by libraries. This is to help ensure that methods that are
 * defined within the sketch are clearly differentiated than those
 * in libraries.
 */

// Easy to access global settings
int  STARTING_ANIMATION = 2;
int  FPS = 60;
bool DEFAULT_SHOW_ON_SET_STRIP = true;
bool DEFAULT_SHOW_ON_SET_ALL= true;
bool REQUIRE_NEWLINE_FOR_SERIALEVENT = false;
bool DEBUG_MODE = false;

#include <Adafruit_NeoPixel.h>

// How many panels there are that have LED strips
const int panel_count = 16;

// Using the Arduino mega, we can use the odd pin numbers of the very end. These will be colour
// coded upon installation.
const int panel_pins[panel_count] = {
  23, // Gray
  25, // Purple
  27, // Blue
  29, // Green
  31, // Yellow
  33, // Orange
  35, // Red
  37, // Brown
  39, // Gray
  41, // Purple
  43, // Blue
  45, // Green
  47, // Yellow
  49, // Orange
  51, // Red
  53  // Brown
};

// Defaulting to 60 pixels each until we know actual numbers
const int panel_pin_counts[panel_count] = {
   59, // 6:45 left
   110, // 7:00 left
   35, // 11:00-a left
   57, // 11:00-b left
   155, // big magnet left
   78, // zigzag-y left
   41, // small top left
   55, // Kite  left
   103, // left
   95,  // right
   68,  // right
   65,  // right
   43,  // right
   112, // right
   149, // right
   109  // right
};

// This will likely be updated later to be captured dynamically in the setup rather than static
// although not a major issue if set manually
const int max_pixel_count = 155;

// Used in many animation
int current_colour[panel_count] = {0};
int target_colour[panel_count] = {0};
String animation_data = "";

// Setup the panels array using the above count. All the panels will be in an array for easy access
Adafruit_NeoPixel panels[panel_count];

void setup() {
  initialize_panels();
  initialize_animations();
  Serial.begin(9600);
  delay(500);
  Serial.println("Ready!");
}

void loop() {
  // Ensure animations are non-blocking
  next_frame();
  //delay(int(1000 / FPS));
}

// There is a "serialEvents" in the communcations tab that manages all serial data
