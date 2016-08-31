// Any message coming from serial will be a global element.
String cmd = "";

void serialEvent() {
  while(Serial.available()) {
    char msg = (char) Serial.read();
    cmd += msg;
    if (REQUIRE_NEWLINE_FOR_SERIALEVENT) {
      if (msg == '\n') {
        cmd.trim();
        process_command();
        cmd = "";
      }
    } else {
      process_command();
      cmd = "";
    }
  }
}

// All input communication is run through here
void process_command() {
  if (cmd == "" || cmd == "\n" || cmd == "\r") return;
  switch (num(cmd)) {
    case 0:  init_off(); break;
    
    case 1:  init_basic_rainbow_animation(); break;
    case 6:  init_unique_rainbow_animation(); break;
    case 7:  init_panel_rainbow(); break;

    // IDLE
    case 5:  init_pulse_panel(); break;
    
    case 13:  init_sparkle_animation(); break;
    case 2:  init_panel_flash(3, false); break;
    case 4:  init_panel_flash(6, true); break;
    
    case 8:  init_solid_colour(BRAND1); break;
    case 9:  init_solid_colour(BRAND2); break;
    case 10:  init_colour_chase_animation(BRAND1); break;
    case 11: init_colour_chase_animation(BRAND2); break;
    case 12: init_colour_chase_animation(WHITE); break;
    case 3: init_even_odd_branding(); break;
    }
}
