class NiladicVoidFunctionCaller {
  public:
    void addCallback(const function<void()>& callback) {
      if (nCallbacks == MAX_N_CALLBACKS) {// TODO raise error somehow
        return;
      }
      callbacks[nCallbacks++] = callback;
   }

   void callCallbacks() {
    for (size_t i = 0 ; i < nCallbacks ; i++) {
        callbacks[i]();
     }
   }
  
  private:
    const static size_t MAX_N_CALLBACKS = 8;
    function<void()> callbacks[MAX_N_CALLBACKS];
    size_t nCallbacks = 0;
};
