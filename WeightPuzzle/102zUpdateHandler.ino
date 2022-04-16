class UpdateHandler {
  public:
    UpdateHandler(StatusRequestProcessor& statusRequestProcessor, InternalCommunicationManagerMixin& internalCommunicationManager) :
      statusRequestProcessor(statusRequestProcessor),
      internalCommunicationManager(internalCommunicationManager) {}
  
    void operator()() {
      if (statusRequestProcessor.isStatusUpdated()) {
        constexpr size_t bufferSize = 8;
        constexpr size_t messageSize = 2;
        constexpr byte MESSAGE_END_CODE = 0x00;
        byte messageBuffer[bufferSize]= {BoardDriver::STATUS_REQUEST_CODE, MESSAGE_END_CODE};
        internalCommunicationManager.setInternalMessage(messageBuffer, messageSize);
      }
    }
  
  private:
    StatusRequestProcessor& statusRequestProcessor;
    InternalCommunicationManagerMixin& internalCommunicationManager;
};
