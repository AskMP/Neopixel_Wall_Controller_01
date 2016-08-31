/*****
 * Most of the functionality is spread into individual tabs pertaining 
 * to their usage. All non-standard or library methods use a PHP style
 * underscore method of seperating words rather than the camelCase method
 * employed by libraries. This is to help ensure that methods that are
 * defined within the sketch are clearly differentiated than those
 * in libraries.
 */
  
// Easy to access global settings
#define STARTING_ANIMATION 5
#define DEFAULT_SHOW_ON_SET_STRIP true
#define DEFAULT_SHOW_ON_SET_ALL true
#define REQUIRE_NEWLINE_FOR_SERIALEVENT false
#define DEBUG_MODE false

// Some basic colours for easy access
#define WHITE  0xFFFFFF
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define BRAND1  0xCC00CC
#define BRAND2  0x00FF00

#include <Adafruit_NeoPixel.h>

// How many panels there are that have LED strips
const int panel_count = 16;

int FPS = 60;

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
  6, // Red
  53  // Brown
};

// Defaulting to 60 pixels each until we know actual numbers
const int panel_pin_counts[panel_count] = {
   59,  // 23 Gray
   110, // 25 Purple
   35,  // 27 Blue
   57,  // 29 Green
   155, // 31 Yellow
   78,  // 33 Orange
   41,  // 35 Red
   55,  // 37 Brown
   103, // 39 Gray
   
   95,  // 41 Purple
   68,  // 43 Blue
   65,  // 45 Green
   43,  // 47 Yellow
   112, // 49 Orange
   149, // 51 Red
   109  // 53 Brown
};

// This will likely be updated later to be captured dynamically in the setup rather than static
// although not a major issue if set manually
const int max_pixel_count = 155;
int total_pixel_count = 0;

// Used in many animation
int current_colour[panel_count] = {0};
int target_colour[panel_count] = {0};

// Setup the panels array using the above count. All the panels will be in an array for easy access
Adafruit_NeoPixel panels[panel_count];

void setup() {
  Serial.begin(9600);
  Serial.println("Potential Animations:");
  Serial.println("---------------------------------------------------------------");
  Serial.println("0  Turn all lights off");
  Serial.println();
  Serial.println("1  The whole wall turns a single colour and the spectrum rotates");
  Serial.println("2  Flash random panels");
  Serial.println("3  Every other panel is purple/green chase");
  Serial.println("4  Flash random panels unique colours");
  Serial.println("5  Pulse the panel(s) random colours");
  Serial.println();
  Serial.println("6  Each panel is a single colour of the spectrum and rotates");
  Serial.println("7  Each panel has a rainbow and it rotates the spectrum");
  Serial.println("8  Set Solid Purple");
  Serial.println("9  Set Solid Green");
  Serial.println("10  Chase animation Purple");
  Serial.println("11  Chase animation Green");
  Serial.println("12  Chase animation White");
  Serial.println("13  Similar to camera flashes, randomly flash the LEDs white");


  
  initialize_panels();
  initialize_animations();

  for (int p = 0; p < panel_count; p ++) total_pixel_count += panel_pin_counts[p];
}

void loop() {
  // Ensure animations are non-blocking
  next_frame();
}

// There is a "serialEvents" in the communcations tab that manages all serial data
