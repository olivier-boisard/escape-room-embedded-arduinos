struct PiccUid {
  PiccUid() : size(0) {}

  PiccUid(const PiccUid& other) : size(other.size) {
    copyValue(other.value);
  }

  PiccUid& operator=(const PiccUid& other) {
    size = other.size;
    copyValue(other.value);
  }

  virtual ~PiccUid() {}

  bool operator==(const PiccUid& other) {
    bool output = false;
    if (size == other.size) {
      output = arrayEquals(size, value, other.value);
    }
    return output;
  }
  
  const static size_t MAX_SIZE = 8;
  size_t size = 0;
  byte value[MAX_SIZE];

  private:
    
    void copyValue(const byte value[]) {
      for (size_t i = 0 ; i < size ; i++) {
        this->value[i] = value[i];
      }
    }
};
