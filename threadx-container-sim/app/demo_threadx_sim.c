#include "tx_api.h"

#include <stdio.h>
#include <stdlib.h>

#define THREAD_STACK_SIZE 2048
#define QUEUE_DEPTH 16
#define MESSAGE_COUNT 10

static TX_THREAD producer_thread;
static TX_THREAD consumer_thread;
static TX_QUEUE message_queue;

static ULONG producer_stack[THREAD_STACK_SIZE / sizeof(ULONG)];
static ULONG consumer_stack[THREAD_STACK_SIZE / sizeof(ULONG)];
static ULONG queue_storage[QUEUE_DEPTH];

static void producer_entry(ULONG thread_input)
{
    ULONG value;

    (void)thread_input;

    for (value = 0; value < MESSAGE_COUNT; value++)
    {
        /* 生产者线程把计数值发送到队列，用于验证 ThreadX queue 和线程调度是否正常。 */
        tx_queue_send(&message_queue, &value, TX_WAIT_FOREVER);
        printf("[producer] send %lu\n", value);

        /* 主动让出一段 tick，避免生产者独占执行流，便于观察消费者线程交替运行。 */
        tx_thread_sleep(10);
    }
}

static void consumer_entry(ULONG thread_input)
{
    ULONG value;
    ULONG received_count = 0;

    (void)thread_input;

    while (received_count < MESSAGE_COUNT)
    {
        /* 消费者线程阻塞等待队列消息，模拟 RTOS 应用中的任务间通信。 */
        tx_queue_receive(&message_queue, &value, TX_WAIT_FOREVER);
        printf("[consumer] receive %lu\n", value);
        received_count++;
    }

    printf("ThreadX container simulation finished.\n");
    exit(0);
}

void tx_application_define(void *first_unused_memory)
{
    (void)first_unused_memory;

    /* 队列消息大小使用 TX_1_ULONG，与 queue_storage 的 ULONG 存储单元保持一致。 */
    tx_queue_create(
        &message_queue,
        "message queue",
        TX_1_ULONG,
        queue_storage,
        sizeof(queue_storage));

    tx_thread_create(
        &producer_thread,
        "producer thread",
        producer_entry,
        0,
        producer_stack,
        sizeof(producer_stack),
        2,
        2,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    tx_thread_create(
        &consumer_thread,
        "consumer thread",
        consumer_entry,
        0,
        consumer_stack,
        sizeof(consumer_stack),
        1,
        1,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);
}

int main(void)
{
    tx_kernel_enter();
    return 0;
}
