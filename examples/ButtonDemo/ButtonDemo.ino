#include <Arduino.h>
#include <Button.h>

static void on_button(void* instance, String name, bool pressed, bool firstTime);
static bool on_get_button_state(String name);

Button button1(NULL, "Button1", false, 70, 10, on_button, on_get_button_state);

void setup() {
  Serial.begin(115200);
}
void loop() {
  button1.Check(millis());
}
void on_button(void* instance, String name, bool pressed, bool firstTime) {
  Serial.print("Name: ");
  Serial.print(name);
  Serial.print(", Pressed: ");
  Serial.print(pressed);
  Serial.print(", First Time: ");
  Serial.print(firstTime);
  Serial.println();
}
bool on_get_button_state(String name) {
  return millis() % 10000 < 5000;
}