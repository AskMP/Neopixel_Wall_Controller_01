/*****
 * Most of the functionality is spread into individual tabs pertaining 
 * to their usage. All non-standard or library methods use a PHP style
 * underscore method of seperating words rather than the camelCase method
 * employed by libraries. This is to help ensure that methods that are
 * defined within the sketch are clearly differentiated than those
 * in libraries.
 */

// Easy to access global settings
int  FPS = 60;
bool DEFAULT_SHOW_ON_SET_STRIP = true;
bool DEFAULT_SHOW_ON_SET_ALL= true;
bool REQUIRE_NEWLINE_FOR_SERIALEVENT = true;
bool DEBUG_MODE = false;

void setup() {
  initialize_panels();
  initialize_animations();
  Serial.begin(9600);
}

void loop() {
  // Ensure animations are non-blocking
  next_frame();
  delay(int(1000 / FPS));
}

// There is a "serialEvents" in the communcations tab that manages all serial data
