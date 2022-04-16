SerialAndInternalCommunicationManager serialAndInternalCommunicationManager;

HX711 hx711;
HX711Handler hx711Handler(hx711, SCALE, MIN_DIFF);

StatusRequestProcessor statusRequestProcessor;

auto updateReadingInStatus = [&statusRequestProcessor] (long reading) {
  statusRequestProcessor.setWeightInGrams(reading);
};

BoardDriver boardDriver(
  serialAndInternalCommunicationManager,
  processHandshake,
  statusRequestProcessor
);

UpdateHandler handleUpdate(statusRequestProcessor, serialAndInternalCommunicationManager);
