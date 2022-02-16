template<class> class function; 

//TODO manage when calling function with null pointer
template<class Return, class... Args>
class function<Return(Args...)> {
public:
    function() : callable(nullptr), optionalFunctionClassInstance(nullptr) {}
    
    template<class Callable, class = decltype(&Callable::operator())>
    function(Callable& callable) : callable(reinterpret_cast<void*>(&Callable::operator())), optionalFunctionClassInstance(&callable) {}
    
    template<class Function>
    function(Function* callable) : callable(reinterpret_cast<void*>(callable)), optionalFunctionClassInstance(nullptr) {}
    
    Return operator()(Args... args) {
        if (optionalFunctionClassInstance) {
            return reinterpret_cast<Return(*)(void*, Args...)>(callable)(optionalFunctionClassInstance, args...);
        }
        return reinterpret_cast<Return(*)(Args...)>(callable)(args...);
    }
    
private:
    void* callable;
    void* optionalFunctionClassInstance;
};
