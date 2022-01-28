class UidChecker {
  public:

    UidChecker() {}

    void setExpectedUid(const MFRC522::Uid& expectedUid) {
      size_t uidSize = expectedUid.size;
      if (uidSize > MAX_UID_SIZE) { // TODO raise error somehow
        uidSize = MAX_UID_SIZE;
      }
      this->expectedUid.size = uidSize;
      for (size_t i = 0 ; i < uidSize ; i++) {
        this->expectedUid.uidByte[i] = expectedUid.uidByte[i];
      }
    }

    bool checkUid(const MFRC522::Uid& uid) {
      if (uid.size != expectedUid.size) {
        return false;
      }
    
      bool output = true;
      for (size_t i = 0 ; i < expectedUid.size ; i++) {
        if (uid.uidByte[i] != expectedUid.uidByte[i]) {
          output = false;
          break;
        }
      }
      return output;
    }
  
  private:
    MFRC522::Uid expectedUid{0};
    constexpr static size_t MAX_UID_SIZE = 4;
};
