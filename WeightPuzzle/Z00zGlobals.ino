SerialAndInternalCommunicationManager serialAndInternalCommunicationManager;
HX711 hx711;
HX711Handler hx711Handler(hx711, SCALE, MIN_DIFF);

auto sendReading = [&hx711Handler, serialAndInternalCommunicationManager] (long reading) {
  constexpr size_t MAX_BUFFER_SIZE = 64;
  byte buffer[MAX_BUFFER_SIZE];
  constexpr byte WEIGHT_STATUS_CODE = 0x1D;
  constexpr byte END_MESSAGE_CODE = 0x00;
  size_t nWrittenBytes = 0;

  buffer[nWrittenBytes++] = WEIGHT_STATUS_CODE;
  nWrittenBytes += writeLongInBuffer(reading, buffer);
  buffer[nWrittenBytes++] = END_MESSAGE_CODE;
  serialAndInternalCommunicationManager.write(buffer, nWrittenBytes);
};

BoardDriver boardDriver(
  serialAndInternalCommunicationManager,
  processHandshake
);
