class BoardDriver {
  public:
    BoardDriver(const function<size_t(byte[], size_t)>& readByteArray, ByteArrayWriter& byteArrayWriter)
      : readByteArray(readByteArray), byteArrayWriter(byteArrayWriter) {}
  
    void read() {
      byte handshakeCode = 0x10;
      byte errorCode = 0xFF;
      byte expectedIncomingCode[] = {0x01, 0xEE, 0x35, 0xD7, 0x2A, 0x80, 0x58, 0xEA};
      byte firmwareId[] = {0x85, 0xF2, 0x9E, 0xE3, 0x43, 0x19, 0xEA, 0xF6};
      size_t inputBufferSize = 16;
      byte inputBuffer[inputBufferSize];
      
      if (readByteArray(inputBuffer, inputBufferSize) > 0) {
        if (inputBuffer[0] == handshakeCode) {
          byteArrayWriter.write(handshakeCode);
          if (arrayEquals(sizeof(expectedIncomingCode), inputBuffer + 1, expectedIncomingCode)) {
            byteArrayWriter.write(firmwareId, sizeof(firmwareId));
          } else {
            byteArrayWriter.write(errorCode);
          }
        } else {
          byteArrayWriter.write(errorCode);
        }
        byteArrayWriter.flush();
      }
    }

  private:
    function<size_t(byte[], size_t)> readByteArray;
    ByteArrayWriter& byteArrayWriter;
};
