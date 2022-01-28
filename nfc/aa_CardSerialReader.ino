struct PiccUid {
  PiccUid(size_t size, byte value[]) : size(size) {
    for (size_t i = 0 ; i < size ; i++) {
      this->value[i] = value[i];
    }
  }
  
  constexpr static size_t MAX_SIZE = 8;
  size_t size = 0;
  byte value[MAX_SIZE];
};

class UidFactoryInterface {
  public: 
    virtual PiccUid* generate() = 0;
    virtual ~UidFactoryInterface() {}
};

class MFRC522UidReader : public UidFactoryInterface {
  public:
    MFRC522UidReader(const MFRC522* mfrc522) : mfrc522(mfrc522) {}

    PiccUid* generate() {
      PiccUid* output = 0;
      if (mfrc522->PICC_IsNewCardPresent() && mfrc522->PICC_ReadCardSerial()) {
        MFRC522::Uid& uid = mfrc522->uid;
        output = new PiccUid((size_t) uid.size, uid.uidByte);
      }
      return output;
    }

  private:
    MFRC522* mfrc522;
};
