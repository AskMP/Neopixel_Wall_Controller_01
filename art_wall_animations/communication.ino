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
  Serial.println("\"" + String(num(cmd)) + "\"");
  switch (num(cmd)) {
    case 0:
      set_all_panels(0, true);
      Serial.println("clear pixels");
      break;
    case 1:
      init_basic_rainbow_animation();
      Serial.println("Basic Rainbow Animation");
      break;
    case 2:
      init_unique_rainbow_animation();
      Serial.println("Unique Panel Rainbow Animation");
      break;
    case 3:
      init_sparkle_animation();
      Serial.println("Custom sparkle animation? (Hopefully)");
      break;
    case 4:
      set_all_panels(Color(0, 0, 200));
      Serial.println("animation 4");
      break;
  }
}
