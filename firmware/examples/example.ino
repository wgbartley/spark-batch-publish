#include "batch-publish/batch-publish.h"

// Set up batch publish
BatchPublish Batch("my-event", 60, PRIVATE);


void setup() {
	// Publish a boot event
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
