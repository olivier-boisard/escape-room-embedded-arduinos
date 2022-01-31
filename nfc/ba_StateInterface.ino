typedef enum {
  noCard = 0,
  cardIsPresent = 1,
  configurationNoCard = 2,
  configurationCardIsPresent = 3
} State;

class StateInterface {
  public:
    virtual State run() = 0;

    virtual ~StateInterface() {}
};
