SerialAndInternalCommunicationManager serialAndInternalCommunicationManager;

HX711 hx711;
HX711Handler hx711Handler(hx711, SCALE, MIN_DIFF);

StatusRequestProcessor statusRequestProcessor(LONG_AS_STR_N_DIGITS);
ConfigurationRequestProcessor configurationRequestProcessor(LONG_AS_STR_N_DIGITS);
ConfigurationToEepromWriter configurationToEepromWriter(EEPROM_ADDRESS);
ConfigurationFromEepromReader configurationFromEepromReader(EEPROM_ADDRESS);
ActiveLowPinController lockController(LOCK_CONTROL_OUTPUT_PIN);

auto updateReadingInStatus = [&statusRequestProcessor] (long reading) {
  statusRequestProcessor.setWeightInGrams(reading);
};

auto updateStatusWithConfiguration = [&statusRequestProcessor] (const Configuration& configuration) {
  statusRequestProcessor.setConfiguration(configuration);
};

UpdateHandler handleUpdate(statusRequestProcessor, serialAndInternalCommunicationManager);

////////////////////////////////// Lock
//TODO integrate this
auto controlLock = [&lockController, &statusRequestProcessor] (bool weightIsCorrectForLongEnough) {
  bool disableLock = weightIsCorrectForLongEnough;
  if (disableLock) {
    lockController.disable();
    statusRequestProcessor.setLockEnabled(false);
  }
};

auto toggleLock = [&lockController, &statusRequestProcessor] () {
  bool lockEnabled = lockController.toggle();
  statusRequestProcessor.setLockEnabled(lockEnabled);
  return lockEnabled;
};
LockCommandProcessor lockCommandProcessor(toggleLock);

///////////////////////////////// Driver
BoardDriver boardDriver(
  serialAndInternalCommunicationManager,
  processHandshake,
  statusRequestProcessor,
  lockCommandProcessor,
  configurationRequestProcessor
);
