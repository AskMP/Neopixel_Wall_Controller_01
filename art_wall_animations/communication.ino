// Any message coming from serial will be a global element.
String cmd = "";

void serialEvent() {
  while(Serial.available()) {
    char msg = (char) Serial.read();
    cmd += msg;
    if (REQUIRE_NEWLINE_FOR_SERIALEVENT) {
      if (msg == '\n') {
        cmd.substring(0, cmd.length() - 2);
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
    case 0:
      set_all_panels(0, true);
      init_off();
      break;
    case 1:
      init_basic_rainbow_animation();
      break;
    case 2:
      init_unique_rainbow_animation();
      break;
    case 3:
      init_sparkle_animation();
      break;
    case 4:
      init_chase_animation();
      break;
    case 5:
      init_pulse_panel();
      break;
  }
}
