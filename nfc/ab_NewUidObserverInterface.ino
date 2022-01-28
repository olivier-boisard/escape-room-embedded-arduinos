class NewUidObserverInterface {
  public:
    virtual void run(const MFRC522::Uid& uid) = 0;
  
    virtual ~NewUidObserverInterface() {}
};
