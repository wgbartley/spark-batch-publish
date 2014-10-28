#ifndef __BATCHPUBLISH_H__
#define __BATCHPUBLISH_H__

#include "application.h"

class BatchPublish {
    public:
        BatchPublish(String eventName, uint32_t ttl, Spark_Event_TypeDef visibility);
        
        void setOpts(String eventName, uint32_t ttl, Spark_Event_TypeDef visibility);
        
        void setOpt(String eventName);
        void setOpt(uint32_t ttl);
        void setOpt(Spark_Event_TypeDef visibility);
        
        bool publish(String name, String data);
        bool publish(String name, String data, bool force_send);
        
        bool publish(String name, float data);
        bool publish(String name, float data, bool force_send);
        
        bool publish(String name, double data);
        bool publish(String name, double data, bool force_send);
        
        bool publish(String name, int data);
        bool publish(String name, int data, bool force_send);
        
        bool publish(String name, uint32_t data);
        bool publish(String name, uint32_t data, bool force_send);
        
        uint8_t send();
    
    
    private:
        String _channel;
        uint32_t _ttl;
        Spark_Event_TypeDef _visibility;
        String _queue;
        
        bool enqueue(String name, String data, bool send);
};

#endif
