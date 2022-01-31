class NewUidObserverInterface {
  public:
    virtual void update(const PiccUid& uid) = 0;
  
    virtual ~NewUidObserverInterface() {}
};
