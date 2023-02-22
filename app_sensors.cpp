/***
   Scan, register and delegate to devies on the i2c bus
 ***/

#include "i2c_devices.h"
/***
 * It's really just about that bus chip.  So kramden is a library for registering callbacks to 
 * named devices and reading/writing that to a serialized config.  You could use durable memory 
 * as the primary config space and reflect that to SPIFFS at application lifecycle events
 * 
 * The config mgmt uses protocol buffers.  These same buffers are used for events and messages. the serialization boundary enables thread isolation.
 * 
 * The library contains:
 * * registry of devices populated in part by discover and from stored config
 *             each device descriptor either from i2c_devices.h or the config ...
 * 
 * * each registry item is either a device_t struct or a device_event_t struct. The former
 *             can be passed as the target of a call_device function. The latter 
 *             can be enabled by passing it and a trigger func to register_device_event.
 * 
 * register_device_event copies the device_event_t into a queue item with a recurring flag 
 *             set. Things with a recurring flag are requeued when they are popped.
 *             register_device_event is executed as a queue + service thread pool which
 *             which iterates through the list of devices, checks conditions and optionally
 *             call the trigger.  An example of a trigger might be a subscription to a sensor. 
 *             The trigger call is pumping a stream of data, in this case an mDNS broadcast.
 * 
 * call_device function checks the device_t structure for an address and a module name.  calls 
 *             load_library on that shit to get a function pointer if there is not one already 
 *             for that module. Using dynamic loading to enable custom drivers to be loaded on
 *             to an SD card. If the response buffer provided is sufficient for the serialized 
 *             response then the response will be copied to that and the return value will be 0.
 *             A negative number indicates the response object size and the provided buffer was 
 *             insufficient. A positive number indicates that the pointer was reassigned because 
 *             buffsize argument was -1 indicating an unallocated pointer
 * 
 * discover function interrogates 
 ***/


/*** TOTAL SIDEBAR  
 * Also really curious about distributed computing on this platform for device coordination
 * Discover - configure - trust - assemble - purpose
 * Every device must have atleast one action, trigger and sensor. And action is a call to make 
 * the device do something. Trigger is provided a callback which takes a device_event struct 
 * reference and enables the device to raise events. sensor is a read call which can be about 
 * internal state or external sensing.
 ***/