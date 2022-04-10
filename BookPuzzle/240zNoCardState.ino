class NoPiccState : public CallbackStackMixin<PiccReaderStatus> {
  public:
    NoPiccState(const function<bool(PiccUid*)>& readUid, const function<bool(const PiccUid& uid)>& checkUid)
      : readUid(readUid), checkUid(checkUid) {}
  
    State operator()() {
      State newState = State::noPicc;
      PiccUid uid;
      if (readUid(&uid)) {
        newState = State::piccIsPresent;
        callCallbacks(checkUid(uid) ? PiccReaderStatus::correctPicc : PiccReaderStatus::wrongPicc);
      }
      return newState;
   }

  private:
   function<bool(PiccUid*)> readUid;
   function<bool(const PiccUid& uid)> checkUid;
};
