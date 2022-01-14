#define DEBOUNCE_DELAY_PER_CHECK_MS 10
#define DEBOUNCE_N_CHECKS 5

bool configSwitchWasReleased = true;

void loop() {
  if (digitalRead(SWITCH_INPUT_PIN) == LOW) {
    bool configSwitchPressed = true;
    for (int i = 0 ; i < DEBOUNCE_N_CHECKS ; i++) {
      delay(DEBOUNCE_DELAY_PER_CHECK_MS);
      if (digitalRead(SWITCH_INPUT_PIN) != LOW) {
        configSwitchPressed = false;
        break;
      }
    }
    if (configSwitchPressed && configSwitchWasReleased) {
      configSwitchWasReleased = false;
      piccProcessor.toggleConfigurationMode();
    }
  } else {
    configSwitchWasReleased = true;
  }
  
  piccProcessor.process();
  delay(LOOP_DELAY_MS);
}
