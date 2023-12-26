#include "CANTestTask.hpp"
#include "CANGatekeeperTask.hpp"

void CANTestTask::execute() {
    CAN::Frame frame = {CAN::NodeID};
    for (auto i = 0; i < CAN::Frame::MaxDataLength; i++) {
        frame.data.at(i) = i;
    }

    while (true) {
        CAN::Application::sendPingMessage(CAN::ADCS, false);
        canGatekeeperTask->send(frame);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}