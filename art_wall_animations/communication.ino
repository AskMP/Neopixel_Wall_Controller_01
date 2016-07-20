// Any message coming from serial will be a global element.
String cmd = "";

void serialEvent() {
  while(Serial.available()) {
    char msg = (char) Serial.read();
    cmd += msg;
    if (REQUIRE_NEWLINE_FOR_SERIALEVENT) {
      if (msg == '\n') {
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
  switch (num(cmd)) {
    case 0:
      set_all_panels(0, true);
      Serial.println("clear pixels");
      break;
    case 1:
      set_all_panels(Color(200, 200, 200));
      Serial.println("animation 1");
      break;
    case 2:
      set_all_panels(Color(200, 0, 0));
      Serial.println("animation 2");
      break;
    case 3:
      set_all_panels(Color(0, 200, 0));
      Serial.println("animation 3");
      break;
    case 4:
      set_all_panels(Color(0, 0, 200));
      Serial.println("animation 4");
      break;
  }
}
