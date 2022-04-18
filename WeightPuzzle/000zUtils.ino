size_t writeLongAsAscii(long data, byte outputBuffer[], size_t nDigitsToWrite) {
  String dataAsString = String(data);
  size_t nWrittenBytes = 0;
  
  for (size_t i = 0 ; i < nDigitsToWrite - dataAsString.length() ; i++) {
    outputBuffer[nWrittenBytes++] = '0';
  }

  const char* buffer = dataAsString.c_str();
  for (size_t i = 0 ; i < dataAsString.length() ; i++) {
    outputBuffer[nWrittenBytes++] = buffer[i];
  }
  
  return nWrittenBytes;
}

long readLongFromAscii(byte inputBuffer[], size_t nDigitsToRead) {
  constexpr size_t bufferSize = 16;

  // Get null terminated string
  char buffer[bufferSize];
  size_t index = 0;
  for (size_t i = 0 ; i < nDigitsToRead ; i++) {
    buffer[index++] = (char) inputBuffer[i];
  }
  buffer[index++] = '\0';

  // Convert to long
  return atol(buffer);
}

template<typename T>
bool arrayEquals(size_t size, const T a[], const T b[]) {
  bool output = true;
  for (size_t i = 0 ; i < size ; i++) {
    if (a[i] != b[i]) {
      output = false;
      break;
    }
  }
  return output;
}
