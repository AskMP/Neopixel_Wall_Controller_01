// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b) {
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

// Some type conversion helpers to clean and convert various inputs to other types
String str(String val) {
  val.trim();
  val = (val.substring(val.length() - 1) == "\"") ? val.substring(0, val.length() - 1) : val;
  val = (val.substring(0, 1) == "\"") ? val.substring(1) : val;
  val.trim();
  return val;
}

int num(String val) {
  char buff[12];
  val.trim();
  val.toCharArray(buff, 12);
  return atoi(buff);
}


bool conditional(String val) {
  val = str(val);
  if (val == "0" || val == "false" || val =="-1") return false;
  else return true;
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

