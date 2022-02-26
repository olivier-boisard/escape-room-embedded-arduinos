class NoCardState : public CallbackStackMixin<PiccReaderStatus> {
  public:
    NoCardState(const function<bool(PiccUid*)>& readUid, const function<bool(const PiccUid& uid)>& checkUid)
      : readUid(readUid), checkUid(checkUid) {}
  
    State operator()() {
      State newState = State::noCard;
      PiccUid uid;
      if (readUid(&uid)) {
        callCallbacks(checkUid(uid) ? correctPicc : wrongPicc);
      }
      return newState;
   }

  private:
   function<bool(PiccUid*)> readUid;
   function<bool(const PiccUid& uid)> checkUid;
};
