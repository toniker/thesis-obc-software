#include "CAN/ApplicationLayer.hpp"
#include "Services/EnvironmentalTestingService.hpp"

void EnvironmentalTestingService::executeBusSwitch(Message message) {
    auto newBus = static_cast<CAN::Driver::ActiveBus>(message.data[0]);
    CAN::Application::sendBusSwitchoverMessage(newBus);
}
