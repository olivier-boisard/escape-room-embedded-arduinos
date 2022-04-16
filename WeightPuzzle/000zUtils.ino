size_t writeLongAsAscii(long data, byte outputBuffer[]) {
  constexpr size_t nDigitsToWrite = 10;
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

long readLongFromAscii(byte inputBuffer[]) {
  long output = 0;
  for (size_t i = 0 ; i < LONG_SIZE_BYTES ; i++) {
    output += inputBuffer[i] << ((LONG_SIZE_BYTES - i - 1) * N_BITS_IN_BYTES);
  }
  return output;
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