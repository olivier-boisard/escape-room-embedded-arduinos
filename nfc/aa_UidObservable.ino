class UidObservable {
  public:
    void addUidObserver(const UidObserver* callback) {
      if (nObservers == MAX_N_OBSERVERS) {// TODO raise error somehow
        return;
      }
      observers[nObservers++] = callback;
   }

   void notifyObservers(const PiccUid& uid) {
    for (size_t i = 0 ; i < nObservers ; i++) {
        observers[i]->update(uid);
     }
   }
  
  private:
    constexpr static size_t MAX_N_OBSERVERS = 8;
    UidObserver* observers[MAX_N_OBSERVERS];
    size_t nObservers = 0;
};
