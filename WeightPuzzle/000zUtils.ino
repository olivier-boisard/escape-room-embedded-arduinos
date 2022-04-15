size_t writeLongInBuffer(long data, byte outputBuffer[]) {
  byte buffer[LONG_SIZE_BYTES];
  for (size_t i = 0 ; i < LONG_SIZE_BYTES ; i++) {
    buffer[i] = (data >> (i * N_BITS_IN_BYTES)) & 255;
  }
  return LONG_SIZE_BYTES;
}

long readLongFromBuffer(byte inputBuffer[]) {
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
