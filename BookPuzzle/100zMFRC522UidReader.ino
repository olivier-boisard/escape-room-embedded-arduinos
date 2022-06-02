class Mfrc522UidReader {
  public:
    Mfrc522UidReader(MFRC522& mfrc522) : mfrc522(mfrc522) {}

    bool operator()(PiccUid* output) {
      bool readSuccessful = false;
      startMfrc522();
      if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        readSuccessful = true;
        MFRC522::Uid& uid = mfrc522.uid;
        size_t uidSize = uid.size;
        output->size = uidSize;
        for (size_t i = 0 ; i < uidSize ; i++) {
          output->value[i] = uid.uidByte[i];
        }
      }
      stopMfrc522();
      return readSuccessful;
    }

  private:
    MFRC522& mfrc522;

    void startMfrc522() {
      mfrc522.PCD_Init();
      delay(10);
    }

    void stopMfrc522() {
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();
    }
};
