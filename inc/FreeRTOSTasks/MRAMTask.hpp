#pragma once

#include "Task.hpp"
#include "MR4A08BUYS45.hpp"
#include "LCLDefinitions.hpp"

class MRAMTask : public Task {
private:
    const uint16_t DelayMs = 2000;

    const static inline uint16_t TaskStackDepth = 1000;

    StackType_t taskStack[TaskStackDepth];

    MRAM mram{SMC::NCS0};

    LCL &mramLCL = LCLDefinitions::lclArray[LCLDefinitions::MRAM];

    uint32_t areYouAliveAddress = 0;

    uint8_t areYouAliveValue = 27;

public:
    void execute();

    MRAMTask() : Task("MRAMTask") {}

    static inline TaskHandle_t mramTaskHandle;

    void createTask() {
        mramTaskHandle = xTaskCreateStatic(vClassTask<MRAMTask>, this->TaskName,
                          MRAMTask::TaskStackDepth, this, tskIDLE_PRIORITY + 2, this->taskStack,
                          &(this->taskBuffer));
    }

    bool isMRAMAlive();
};

inline std::optional<MRAMTask> mramTask;
