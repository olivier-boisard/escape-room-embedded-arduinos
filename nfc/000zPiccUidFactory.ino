class PiccUidFactory {
  public: 
    virtual bool generate(PiccUid* output) = 0;
    virtual ~PiccUidFactory() {}
};
