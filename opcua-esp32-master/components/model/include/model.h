#include "open62541.h"

/* GPIO Numbers */
// #define BLINK_GPIO 2
#define DHT22_GPIO 4
#define RELAY_0_GPIO 32
#define RELAY_1_GPIO 33
#define RELAY_2_GPIO 26
#define Pot 34

// #define RELAY_2_GPIO 26
// #define RELAY_3_GPIO 27

// /* Led Method */
// UA_StatusCode
// ledProcessCallBack(UA_Server *server,
//                    const UA_NodeId *sessionId, void *sessionHandle,
//                    const UA_NodeId *methodId, void *methodContext,
//                    const UA_NodeId *objectId, void *objectContext,
//                    size_t inputSize, const UA_Variant *input,
//                    size_t outputSize, UA_Variant *output);

// void
// addLEDMethod(UA_Server *server);

//________________________________________________________________ Temperatura ______________________________________________________________________

/* Temperature */
UA_StatusCode
readCurrentTemperature(UA_Server *server,
                       const UA_NodeId *sessionId, void *sessionContext,
                       const UA_NodeId *nodeId, void *nodeContext,
                       UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                       UA_DataValue *dataValue);

void addCurrentTemperatureDataSourceVariable(UA_Server *server);

//________________________________________________________________ Umidade ______________________________________________________________________
/* Umidade*/
UA_StatusCode
readCurrentUmidade(UA_Server *server,
                   const UA_NodeId *sessionId, void *sessionContext,
                   const UA_NodeId *nodeId, void *nodeContext,
                   UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                   UA_DataValue *dataValue);

void addCurrentUmidadeDataSourceVariable(UA_Server *server);

//________________________________________________________________ Voltage, air quality ______________________________________________________________________

// potenciometer

UA_StatusCode
readCurrentVoltage(UA_Server *server,
                   const UA_NodeId *sessionId, void *sessionContext,
                   const UA_NodeId *nodeId, void *nodeContext,
                   UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                   UA_DataValue *dataValue);

void addCurrentVoltageDataSourceVariable(UA_Server *server);

//________________________________________________________________ Relay 1 and relay 2 ______________________________________________________________________

/* Relay 1 */
UA_StatusCode
readRelay1State(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue);

UA_StatusCode
setRelay1State(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeId, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data);

void addRelay1ControlNode(UA_Server *server);

/* Relay 2 */
UA_StatusCode
readRelay2State(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue);

UA_StatusCode
setRelay2State(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeId, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data);

void addRelay2ControlNode(UA_Server *server);

//________________________________________________________________ RFID 1 ______________________________________________________________________

UA_StatusCode
readRFID(UA_Server *server,
         const UA_NodeId *sessionId, void *sessionContext,
         const UA_NodeId *nodeId, void *nodeContext,
         UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
         UA_DataValue *dataValue);

void addRFID(UA_Server *server);

UA_StatusCode
readRFIDFlag1(UA_Server *server,
              const UA_NodeId *sessionId, void *sessionContext,
              const UA_NodeId *nodeId, void *nodeContext,
              UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
              UA_DataValue *dataValue);

UA_StatusCode
setRFIDFlag1(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             const UA_NumericRange *range, const UA_DataValue *data);

void addRFIDFlag1ControlNode(UA_Server *server);

//________________________________________________________________ RFID 2 ______________________________________________________________________

UA_StatusCode
readRFID2(UA_Server *server,
          const UA_NodeId *sessionId, void *sessionContext,
          const UA_NodeId *nodeId, void *nodeContext,
          UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
          UA_DataValue *dataValue);

void addRFID2(UA_Server *server);

UA_StatusCode
readRFIDFlag2(UA_Server *server,
              const UA_NodeId *sessionId, void *sessionContext,
              const UA_NodeId *nodeId, void *nodeContext,
              UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
              UA_DataValue *dataValue);

UA_StatusCode
setRFIDFlag2(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             const UA_NumericRange *range, const UA_DataValue *data);

void addRFIDFlag2ControlNode(UA_Server *server);

//________________________________________________________________ AirQuality ______________________________________________________________________

UA_StatusCode
readAirQuality(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeId, void *nodeContext,
               UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
               UA_DataValue *dataValue);

void addAirQuality(UA_Server *server);
//________________________________________________________________ RFID INIT ______________________________________________________________________

void RC522Init();
void RC522Init_2();
