typedef enum {
  noCard,
  cardIsPresent,
  configurationNoCard,
  configurationCardIsPresent
} State;

class StateInterface {
  public:
    virtual State run() = 0;

    virtual ~StateInterface() {}
};
