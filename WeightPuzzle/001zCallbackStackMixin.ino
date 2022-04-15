template<class... Args>
class CallbackStackMixin {
  public:
    template<class Callback>
    void addCallback(Callback& callback) {
      callbacks[nCallbacks++] = callback;
    }
    
    template<class Callback>
    void addCallback(Callback&& callback) = delete;
    
    void callCallbacks(Args... args) {
      for (size_t i = 0 ; i < nCallbacks ; ++i) {
        callbacks[i](args...);
      }
    }
  
  private:
    constexpr static size_t MAX_SIZE = 4;
    function<void(Args...)> callbacks[MAX_SIZE];
    size_t nCallbacks = 0;
};
