#include <gtest/gtest.h>
#include <inc/auto_lock.h>

namespace SMART_EVENT {
    struct TestData {
        int val ;
        SmartEvent wait_signal;
    };
    void *fnSet1(void *data)
    {
        auto *pData = (TestData *)data ;
        pData->val = 1;
    }

    void *fnWaitSignal(void *data)
    {
        auto *pData = (TestData *)data ;
        pData->wait_signal.WaitForEvent(true);
    }

    TEST(Single_pThread, ThreadCreateAndWaitExit)
    {
        pthread_t p_thread;
        TestData data = {0, };
        int status ;
        int thr_id ;

        ASSERT_EQ(data.val, 0);
        thr_id = pthread_create(&p_thread, NULL, fnSet1, (void *)&data);
        pthread_join(p_thread, (void **)&status);
        ASSERT_EQ(data.val, 1);
    }

    TEST(Single_pThread, Timeout)
    {
        struct timespec ts;
        pthread_t p_thread;
        TestData data = {0, };
        int thr_id ;
        int status ;

        ASSERT_EQ(data.val, 0);
        thr_id = pthread_create(&p_thread, NULL, fnWaitSignal, (void *)&data);

        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 1;

        int ret = pthread_timedjoin_np(p_thread, NULL, &ts);

        ASSERT_EQ(ret, ETIMEDOUT);

        data.wait_signal.SignalEvent(true);
        pthread_join(p_thread, (void **)&status);
    }

    TEST(Single_pThread, WaitForEvent)
    {
        struct timespec ts;
        pthread_t p_thread;
        TestData data;
        int thr_id ;
        int ret;
        int status;

        thr_id = pthread_create(&p_thread, NULL, fnWaitSignal, (void *)&data);

        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 1;

        ret = pthread_timedjoin_np(p_thread, NULL, &ts);
        ASSERT_EQ(ret, ETIMEDOUT);

        data.wait_signal.SignalEvent(true);

        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 1;

        ret = pthread_timedjoin_np(p_thread, NULL, &ts);
        ASSERT_EQ(ret, 0);

        pthread_join(p_thread, (void **)&status);
    }
}