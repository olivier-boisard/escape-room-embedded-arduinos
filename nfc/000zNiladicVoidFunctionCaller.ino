class NiladicVoidFunctionCaller {
  public:
    void addCallback(const NiladicVoidFunction* callback) {
      if (nCallbacks == MAX_N_CALLBACKS) {// TODO raise error somehow
        return;
      }
      callbacks[nCallbacks++] = callback;
   }

   void callCallbacks() {
    for (size_t i = 0 ; i < nCallbacks ; i++) {
        callbacks[i]->run();
     }
   }
  
  private:
    const static size_t MAX_N_CALLBACKS = 8;
    NiladicVoidFunction* callbacks[MAX_N_CALLBACKS];
    size_t nCallbacks = 0;
};
