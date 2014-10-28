batch-publish
=============

About
-----
A utility for queuing or batching of key values for [Spark.publish()](http://docs.spark.io/firmware/#spark-publish).  Useful if you want to publish several things at once but don't want to exceed the burst limit.  Since it reduces the number of calls to <code>Spark.publish()</code>, there is a slight speed boost as well.


How it Works
------------
It works by simply adding your key &rarr; value data into a JSON object limited to 61 characters (the 63-character limit plus <code>{</code> and <code>}</code> encapsulating braces.  If there are multiple sets per batch, they will be separated with commas (<code>,</code>).  Once the batched sets reach or exceed the character limit, they will be published via <code>Spark.publish()</code>.  If a set is longer than the character limit, the <code>.publish()</code> function will return false.

Brevity of key names and values is recommended.  The fewer characters you use, the more efficient this utility will be.


Functions
---------

 - <code>BatchPublish(String eventName, uint32_t ttl, Spark_Event_TypeDef visibility)</code>
  - These arguments correspond to the <code>Spark.publish()</code> options
  - <code>String eventName</code> - The name of the channel to publish events to
  - <code>uint32_t ttl</code> - The time-to-live
  - <code>Spark_Event_TypeDef visibility</code> - Available values are <code>PUBLIC</code> or <code>PRIVATE</code>
 - <code>setOpts(String eventName, uint32_t ttl, Spark_Event_TypeDef visibility)</code>
  - Allows you to change the options on-the-fly.  However, be sure to use <code>send()</code> (see below) before you need to change options to make sure any batched data using the old options is sent.
 - <code>setOpt(String eventName)</code>, <code>setOpt(uint32_t ttl)</code>, and <code>setOpt(Spark_EventTypeDef visibility)</code>
  - Allows you to change individual options on-the-fly one at a time.  Be sure to use <code>send()</code> (see below) before you need to change options to make sure any batched data using the old options is sent.
 - <code>publish(String name, data, &lt;bool force_send&gt;)</code>
  - Put key &rarr; value pair into the queue.  If the queue meets or exceeds the character limit, <code>Spark.publish()</code> will be called and the queue will start over with the key => value set passed to it.
  - <code>data</code> can be (nearly?) any type of type: <code>Sring</code>, <code>float</code>, <code>double</code>, <code>int</code>, <code>uint32_t</code>
  - <code>bool force_send</code> - Optional argument to force a <code>Spark.publish()</code> immediately after this key &rarr; value set is added to the queue.  This can be useful when publishing the last set in a <code>loop()</code> before a long delay, or before changing the options using <code>setOpts()</code> or <code>setOpt</code>.
 - <code>send()</code>
  - Force a send of all data in the batch.  There are no arguments for this function.


Example
-------

The following example is also available in <code>firmware/examples/example.ino</code>.

```cpp
#include "batch-publish.h"

// Set up batch publish
BatchPublish Batch("my-event", 60, PRIVATE);


void setup() {
		// Publish a boot event and send it immediately
		Batch.publish("boot", 1, true);
}


void loop() {
		// Publish several metric values
		int metric_value = 0;
		Batch.publish("metric_1", metric_value);

		metric_value = 1;
		Batch.publish("metric_2", metric_value);

		metric_value = 2;
		Batch.publish("metric_3", metric_value);

		metric_value = 3;
		Batch.publish("metric_4", metric_value);

		metric_value = 5;
		Batch.publish("metric_5", metric_value);


		// Force the queue to send anything left over
		Batch.send();


		// Arbitrary delay
		delay(2000);
}

```
