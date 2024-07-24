class Mfrc522UidReader {
  public:
    Mfrc522UidReader(MFRC522& mfrc522, int maxRetries = 3) 
      : mfrc522(mfrc522), initialized(false), maxRetries(maxRetries) {}

    bool operator()(PiccUid* output) {
        if (!initialized) {
            initializeReader();
        }

        bool success = false;
        for (int attempt = 0; attempt < maxRetries; ++attempt) {
            if (attempt > 0) {
                delay(10); // Small delay before retrying
            }

            if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
                // Copy UID to output
                MFRC522::Uid& uid = mfrc522.uid;
                size_t uidSize = uid.size;
                output->size = uidSize;
                for (size_t i = 0; i < uidSize; i++) {
                    output->value[i] = uid.uidByte[i];
                }

                // Halt PICC
                mfrc522.PICC_HaltA();
                // Stop encryption on PCD
                mfrc522.PCD_StopCrypto1();

                success = true;
                break; // Exit the retry loop on success
            }
        }

        if (!success) {
            resetReader(); // Reset the reader after maxRetries failures
        }

        return success;
    }

  private:
    MFRC522& mfrc522;
    bool initialized;
    int maxRetries;

    void initializeReader() {
        mfrc522.PCD_Init();
        delay(50); // Ensure enough delay for initialization
        initialized = true;
    }

    void resetReader() {
        mfrc522.PCD_Reset();
        delay(50); // Ensure enough delay for reset
        mfrc522.PCD_Init();
        delay(50); // Ensure enough delay for initialization
    }
};
