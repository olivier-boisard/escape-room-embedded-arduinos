class NewUidObserverInterface {
  public:
    virtual void run(const PiccUid& uid) = 0;
  
    virtual ~NewUidObserverInterface() {}
};
