#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef uint8_t RTOS_TaskCnt;
typedef uint8_t RTOS_TaskStatus;
typedef unsigned RTOS_ScheduleCntType;
typedef void (*RTOS_FunctionPointerType)(void *);

#define RTOS_CRITICAL_SECTION_ENTER()
#define RTOS_CRITICAL_SECTION_EXIT()
enum RTOS_TaskStatus { READY };

extern RTOS_TaskCnt RTOS_NrOfTasks;

typedef struct {
  RTOS_FunctionPointerType startAddress;
  void *args;
  RTOS_TaskStatus status;
  RTOS_ScheduleCntType scheduleCount;
} RTOS_Task;

typedef RTOS_Task *RTOS_TaskHandle;
extern RTOS_TaskHandle RTOS_Tasks[];
extern  RTOS_TaskHandle RTOS_ActiveTask;

RTOS_TaskHandle RTOS_StaticRegisterTask(RTOS_FunctionPointerType taskFunction, void * const parameters) {
  RTOS_TaskHandle task = RTOS_Tasks[RTOS_NrOfTasks++];
  task->startAddress = taskFunction;
  task->args = parameters;
  return task;
}
void RTOS_RTCScheduler(void) {
  for (RTOS_TaskCnt taskCnt = 0; taskCnt < RTOS_NrOfTasks; taskCnt++) {
    RTOS_TaskHandle task = RTOS_Tasks[taskCnt];
    if (task->status == READY) {
      RTOS_CRITICAL_SECTION_ENTER();
      task->scheduleCount++;
      RTOS_CRITICAL_SECTION_EXIT();
      RTOS_ActiveTask = task;
      task->startAddress(task->args);
    }
  }
}
