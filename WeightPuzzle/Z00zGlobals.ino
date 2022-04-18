SerialAndInternalCommunicationManager serialAndInternalCommunicationManager;

HX711 hx711;
HX711Handler hx711Handler(hx711, SCALE, MIN_DIFF);

StatusRequestProcessor statusRequestProcessor(LONG_AS_STR_N_DIGITS);
ConfigurationRequestProcessor configurationRequestProcessor(LONG_AS_STR_N_DIGITS);

auto updateReadingInStatus = [&statusRequestProcessor] (long reading) {
  statusRequestProcessor.setWeightInGrams(reading);
};

auto updateStatusWithConfiguration = [&statusRequestProcessor] (const Configuration& configuration) {
  statusRequestProcessor.setMinWeightInGrams(configuration.minWeightInGrams);
  statusRequestProcessor.setMaxWeightInGrams(configuration.maxWeightInGrams);
  statusRequestProcessor.setHoldingTimeInMs(configuration.holdingTimeInMs);
};

BoardDriver boardDriver(
  serialAndInternalCommunicationManager,
  processHandshake,
  statusRequestProcessor,
  configurationRequestProcessor
);

UpdateHandler handleUpdate(statusRequestProcessor, serialAndInternalCommunicationManager);
