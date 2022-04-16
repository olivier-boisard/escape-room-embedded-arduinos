class UpdateHandler {
  public:
    UpdateHandler(StatusRequestProcessor& statusRequestProcessor, InternalCommunicationManagerMixin& internalCommunicationManager) :
      statusRequestProcessor(statusRequestProcessor),
      internalCommunicationManager(internalCommunicationManager) {}
  
    void operator()() {
      if (statusRequestProcessor.isStatusUpdated()) {
        constexpr size_t bufferSize = 8;
        constexpr size_t messageSize = 1;
        byte messageBuffer[bufferSize]= {BoardDriver::STATUS_REQUEST_CODE};
        internalCommunicationManager.setInternalMessage(messageBuffer, messageSize);
      }
    }
  
  private:
    StatusRequestProcessor& statusRequestProcessor;
    InternalCommunicationManagerMixin& internalCommunicationManager;
};
