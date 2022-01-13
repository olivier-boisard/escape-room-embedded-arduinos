#define UID_MAX_SIZE 7

class UidChecker {
  public:
    UidChecker(const MFRC522::Uid& expectedUid) : expectedUid(expectedUid) {}

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
    MFRC522::Uid expectedUid;
};
