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

void resetBuffer(char buffer[], size_t bufferSize) {
  for (size_t i = 0 ; i < SSID_MAX_LENGTH ; i++) {
    buffer[i] = 0x00;
  }
}
