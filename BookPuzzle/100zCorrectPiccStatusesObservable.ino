class CorrectPiccStatusesObservable : public CallbackStackMixin<bool> {
  public:
    CorrectPiccStatusesObservable(size_t nPiccReaders) : nPiccReaders(nPiccReaders) {
      if (nPiccReaders > BUFFER_SIZE) {
        // TODO raise error somehow
      }
      for (size_t i = 0 ; i < nPiccReaders ; i++) {
        statuses[i] = PiccReaderStatus::noPicc;
      }
    }
    
    void updatePiccReaderStatus(size_t piccReaderId, PiccReaderStatus status) {
      if (piccReaderId > nPiccReaders) {
        //TODO handle error
      }
      statuses[piccReaderId] = status;
      callCallbacks(allPiccAreCorrect());
    }
    
    virtual ~CorrectPiccStatusesObservable() = default;  
  
  private:

    bool allPiccAreCorrect() {
      bool allPiccAreCorrect = nPiccReaders > 0;
      for (size_t i = 0 ; i < nPiccReaders ; i++) {
        if (statuses[i] != PiccReaderStatus::correctPicc) {
          allPiccAreCorrect = false;
          break;
        }
      }
      return allPiccAreCorrect;
    }
  
    constexpr static size_t BUFFER_SIZE = 8;
    size_t nPiccReaders;
    PiccReaderStatus statuses[BUFFER_SIZE];
};
