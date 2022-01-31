class MFRC522UidReader : public AbstractPiccUidFactory {
  public:
    MFRC522UidReader(const MFRC522* mfrc522) : mfrc522(mfrc522) {}

    bool generate(PiccUid* output) {
      bool readSuccessful = false;
      if (mfrc522->PICC_IsNewCardPresent() && mfrc522->PICC_ReadCardSerial()) {
        readSuccessful = true;
        MFRC522::Uid& uid = mfrc522->uid;
        size_t uidSize = uid.size;
        output->size = uidSize;
        for (size_t i = 0 ; i < uidSize ; i++) {
          output->value[i] = uid.uidByte[i];
        }
      }
      return readSuccessful;
    }

  private:
    MFRC522* mfrc522;
};
