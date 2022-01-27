#define MAX_UID_SIZE 10

class UidChecker {
  public:

    UidChecker() {}
    
    UidChecker(const UidChecker& other) {
      setExpectedUid(other.expectedUid);
    }

    const UidChecker& operator=(const UidChecker& other) {
      setExpectedUid(other.expectedUid);
    }

    virtual ~UidChecker() {}

    void setExpectedUid(const MFRC522::Uid& expectedUid) {
      size_t uidSize = expectedUid.size;
      if (uidSize > MAX_UID_SIZE) { // TODO this should somehow raise a warning
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
};
