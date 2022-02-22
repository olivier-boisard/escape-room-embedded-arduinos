void setup() {
  // Start serial
  Serial.begin(9600);
  
  // Set expected UID
  PiccUid validUid;
  if (readUidFromEeprom(&validUid)) {
    uidChecker.setExpectedUid(validUid);
  } else {
    //TODO raise error somehow
  }

  // Wiring
  configurationNoCardState.addCallback(updateUidChecker);
  configurationNoCardState.addCallback(writeUid);
  stateMachine.addStateFunction(State::noCard, noCardState);
  stateMachine.addStateFunction(State::cardIsPresent, cardIsPresentState);
  stateMachine.addStateFunction(State::configurationNoCard, configurationNoCardState);
  stateMachine.addStateFunction(State::configurationCardIsPresent, configurationCardIsPresentState);
  stateMachine.addCallback(sendStatusRequestCommandWrapper);
  configurationButton.addCallback(configurationModeToggler);
  magnetButton.addCallback(toggleMagnetWrapper);
  noCardState.addCallback(controlMagnetWithPicc);
  noCardState.addCallback(setPiccReaderZeroState);

  // Initialize MFRC522 driver
  mfrc522.PCD_Init();

  // Set pin modes
  pinMode(CONFIG_BUTTON_INPUT_PIN, INPUT);
  pinMode(MAGNET_BUTTON_INPUT_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(MAGNET_CONTROL_OUTPUT_PIN, OUTPUT);

  // Initialize pin values
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(MAGNET_CONTROL_OUTPUT_PIN, LOW);
}
