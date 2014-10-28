#include "BatchPublish.h"
#include "application.h"

BatchPublish::BatchPublish(String eventName, uint32_t ttl, Spark_Event_TypeDef visibility) {
    setOpts(eventName, ttl, visibility);
}


void BatchPublish::setOpts(String eventName, uint32_t ttl, Spark_Event_TypeDef visibility) {
    _channel.reserve(64);
    _queue.reserve(64);
    
    channel.trim();
    
    _channel = channel;
    _ttl = ttl;
    _visibility = visibility;
}


void BatchPublish::setOpt(String eventName) { _channel = channel; }
void BatchPublish::setOpt(uint32_t ttl) { _ttl = ttl; }
void BatchPublish::setOpt(Spark_Event_TypeDef visibility) { _visibility = visibility; }


bool BatchPublish::enqueue(String name, String data, bool force_send) {
    String tmp;
    tmp.reserve(64);
    
    name.trim();
    data.trim();
    
    if(_queue.length()>0)
        tmp += ",";
    
    tmp += "\""+name+"\":"+data;
    
    tmp.trim();
    
    if(tmp.length()>62) {
        return false;
    } else if(tmp.length()+_queue.length()>62) {
        send();
        return enqueue(name, data, force_send);
    } else {
        _queue += tmp;
        
        if(force_send==true)
            send();
        
        return true;
    }
}


uint8_t BatchPublish::send() {
    _queue.trim();
    
    _queue = "{"+_queue+"}";
    
    uint8_t retval = _queue.length();
    
    if(_queue.length()>0) {
        Spark.publish(_channel, _queue, _ttl, _visibility);
        _queue = "";
    }
    
    return retval;
}


bool BatchPublish::publish(String name, String data) {
    return enqueue(name, data, false);
}


bool BatchPublish::publish(String name, String data, bool force_send) {
    return enqueue(name, data, force_send);
}


bool BatchPublish::publish(String name, float data) {
    return enqueue(name, (String) data, false);
}


bool BatchPublish::publish(String name, float data, bool force_send) {
    return enqueue(name, (String) data, force_send);
}


bool BatchPublish::publish(String name, double data) {
    return enqueue(name, (String) data, false);
}


bool BatchPublish::publish(String name, double data, bool force_send) {
    return enqueue(name, (String) data, force_send);
}


bool BatchPublish::publish(String name, int data) {
    return enqueue(name, (String) data, false);
}


bool BatchPublish::publish(String name, int data, bool force_send) {
    return enqueue(name, (String) data, force_send);
}


bool BatchPublish::publish(String name, uint32_t data) {
    return enqueue(name, (String) data, false);
}


bool BatchPublish::publish(String name, uint32_t data, bool force_send) {
    return enqueue(name, (String) data, force_send);
}
