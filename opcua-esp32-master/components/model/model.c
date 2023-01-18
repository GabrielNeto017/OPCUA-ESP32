#include "open62541.h"
#include "model.h"

#include "driver/gpio.h"
#include "Potentiometer.h"
#include "dht11.h"
#include "rc522.h"
#include "rc522_2.h"
#include <stdio.h>
#include "string.h"

char RFID1[20];
char RFID2[20];

#define LED_ESP 2
//bool handler = false;
bool stateFlag1 = false;
bool stateFlag2 = false;
int PPM=0;

#define MEMORY_TAG "MEMORY"

static const char *TAG = "app";
//static void configureGPIO();

/* GPIO Configuration */
/*static void
configureGPIO(void) {
    gpio_set_direction(RELAY_0_GPIO, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(RELAY_1_GPIO, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(RELAY_2_GPIO, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(Pot, GPIO_MODE_INPUT);
}*/

// /* LED Method */

// UA_StatusCode
// ledProcessCallBack(UA_Server *server,
//                    const UA_NodeId *sessionId, void *sessionHandle,
//                    const UA_NodeId *methodId, void *methodContext,
//                    const UA_NodeId *objectId, void *objectContext,
//                    size_t inputSize, const UA_Variant *input,
//                    size_t outputSize, UA_Variant *output)
// {
//     UA_Int32 i = 0;
//     UA_Int32 *inputVal = (UA_Int32 *)input->data;
//     UA_String tmp = UA_STRING_ALLOC("Data Received");
//     if (*inputVal > 0)
//     {
//         tmp.data = (UA_Byte *)UA_realloc(tmp.data, tmp.length);
//         while (i < *inputVal + 1)
//         {
//             gpio_pad_select_gpio(BLINK_GPIO);
//             gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
//             gpio_set_level(BLINK_GPIO, 1);
//             vTaskDelay(500 / portTICK_PERIOD_MS);
//             gpio_set_level(BLINK_GPIO, 0);
//             vTaskDelay(500 / portTICK_PERIOD_MS);
//             i++;
//         }
//     }
//     UA_String_clear(&tmp);
//     return UA_STATUSCODE_GOOD;
// }

// void
// addLEDMethod(UA_Server *server)
// {

//     UA_NodeId createdNodeId;
//     UA_ObjectAttributes object_attr = UA_ObjectAttributes_default;

//     object_attr.description = UA_LOCALIZEDTEXT("en-US", "A pump!");
//     object_attr.displayName = UA_LOCALIZEDTEXT("en-US", "Pump1");

//     UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1, 0),
//                             UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                             UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
//                             UA_QUALIFIEDNAME(1, "Pump1"),
//                             UA_NODEID_NUMERIC(2, 1002),
//                             object_attr, NULL, &createdNodeId);

//     UA_Argument inputArgument;
//     UA_Argument_init(&inputArgument);
//     inputArgument.description = UA_LOCALIZEDTEXT("en-US", "Number of times to blink LED!");
//     inputArgument.name = UA_STRING("Blink Count");
//     inputArgument.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
//     inputArgument.valueRank = -1; /* scalar */

//     /* And output argument for a void method is not logical, check here !!! */
//     UA_Argument outputArgument;
//     UA_Argument_init(&outputArgument);
//     outputArgument.description = UA_LOCALIZEDTEXT("en-US", "LED Blinked");
//     outputArgument.name = UA_STRING("Led Blink Method Output");
//     outputArgument.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
//     outputArgument.valueRank = UA_VALUERANK_ONE_DIMENSION;

//     UA_MethodAttributes helloAttr = UA_MethodAttributes_default;
//     helloAttr.description = UA_LOCALIZEDTEXT("en-US", "Enter the number of times you want LED to blin!");
//     helloAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Blink");
//     helloAttr.executable = true;
//     helloAttr.userExecutable = true;
//     UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1, 62541),
//                             UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
//                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT),
//                             UA_QUALIFIEDNAME(1, "Blink"),
//                             helloAttr, &ledProcessCallBack,
//                             1, &inputArgument, 1, &outputArgument, NULL, &createdNodeId);
// }

/*

potenciometer










 

 Relay 1 

UA_StatusCode
readRelay1State(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {
    UA_Boolean relay1_State = gpio_get_level(RELAY_1_GPIO);
    UA_Variant_setScalarCopy(&dataValue->value, &relay1_State,
                             &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
setRelay1State(UA_Server *server,
                  const UA_NodeId *sessionId, void *sessionContext,
                  const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {
    UA_Boolean currentState = gpio_get_level(RELAY_1_GPIO);
    int level = currentState == true ? 0:1;
    gpio_set_level(RELAY_1_GPIO, level);
    UA_Boolean relay1_state_after_write = gpio_get_level(RELAY_1_GPIO);
    UA_StatusCode status = relay1_state_after_write == level ? UA_STATUSCODE_GOOD : UA_STATUSCODE_BADINTERNALERROR;
    return status;
}

void
addRelay1ControlNode(UA_Server *server) {
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Relay1");
    attr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "Control Relay number 1.");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Control Relay number 1.");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource relay1;
    relay1.read = readRelay1State;
    relay1.write = setRelay1State;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        relay1, NULL, NULL);
}



 Relay 2 

UA_StatusCode
readRelay2State(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {
    UA_Boolean relay2_State = gpio_get_level(RELAY_2_GPIO);
    UA_Variant_setScalarCopy(&dataValue->value, &relay2_State,
                             &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
setRelay2State(UA_Server *server,
                  const UA_NodeId *sessionId, void *sessionContext,
                  const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {
    UA_Boolean currentState = gpio_get_level(RELAY_2_GPIO);
    int level = currentState == true ? 0:1;
    gpio_set_level(RELAY_2_GPIO, level);
    UA_Boolean relay2_state_after_write = gpio_get_level(RELAY_2_GPIO);
    UA_StatusCode status = relay2_state_after_write == level ? UA_STATUSCODE_GOOD : UA_STATUSCODE_BADINTERNALERROR;
    return status;
}



void
addRelay2ControlNode(UA_Server *server) {
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Relay2");
    attr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "Control Relay number 2.");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Control Relay number 2.");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource relay2;
    relay2.read = readRelay2State;
    relay2.write = setRelay2State;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        relay2, NULL, NULL);
}


*/

//________________________________________________________________OPC DHT11  ______________________________________________________________________

UA_StatusCode
readCurrentTemperature(UA_Server *server,
                       const UA_NodeId *sessionId, void *sessionContext,
                       const UA_NodeId *nodeId, void *nodeContext,
                       UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                       UA_DataValue *dataValue)
{
    UA_Float temperature = DHT11_read().temperature;
    //printf(" o status do dht11 é %i: \n", DHT11_read().status);
    UA_Variant_setScalarCopy(&dataValue->value, &temperature,
                             &UA_TYPES[UA_TYPES_FLOAT]);
    dataValue->hasValue = true;
    //ESP_LOGI(MEMORY_TAG, "apos da temperatura : %d", esp_get_free_heap_size());
    return UA_STATUSCODE_GOOD;
}

void addCurrentTemperatureDataSourceVariable(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Temperature");
    attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "Temperature");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Ambient Temperature");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
    DHT11_init(GPIO_NUM_4);
    UA_DataSource timeDataSource;
    timeDataSource.read = readCurrentTemperature;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        timeDataSource, NULL, NULL);
}

/* Umidade DHT11*/

UA_StatusCode
readCurrentUmidade(UA_Server *server,
                   const UA_NodeId *sessionId, void *sessionContext,
                   const UA_NodeId *nodeId, void *nodeContext,
                   UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                   UA_DataValue *dataValue)
{
    UA_Float Umidade = DHT11_read().humidity;
    UA_Variant_setScalarCopy(&dataValue->value, &Umidade,
                             &UA_TYPES[UA_TYPES_FLOAT]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

void addCurrentUmidadeDataSourceVariable(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Umidade");
    attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "Umidade");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Ambient Umidade");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
    UA_DataSource timeDataSource;
    timeDataSource.read = readCurrentUmidade;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        timeDataSource, NULL, NULL);
}

//________________________________________________________________OPC RFID1_flag1  ______________________________________________________________________

UA_StatusCode
readRFIDflag1(UA_Server *server,
              const UA_NodeId *sessionId, void *sessionContext,
              const UA_NodeId *nodeId, void *nodeContext,
              UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
              UA_DataValue *dataValue)
{
    UA_Boolean flag1_State = stateFlag1;
    UA_Variant_setScalarCopy(&dataValue->value, &flag1_State,
                             &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
setRFIDflag1(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             const UA_NumericRange *range, const UA_DataValue *data)
{
    memset(RFID1, 0, 20);
    stateFlag1 = false;
    UA_StatusCode status = stateFlag1 == false ? UA_STATUSCODE_GOOD : UA_STATUSCODE_BADINTERNALERROR;
    return status;
}

void addRFIDFlag1ControlNode(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Flag1");
    attr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "Flag1");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Flag1");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource flag1;
    flag1.read = readRFIDflag1;
    flag1.write = setRFIDflag1;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        flag1, NULL, NULL);
}

//________________________________________________________________OPC RFID 1 ______________________________________________________________________

UA_StatusCode
readRFID(UA_Server *server,
         const UA_NodeId *sessionId, void *sessionContext,
         const UA_NodeId *nodeId, void *nodeContext,
         UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
         UA_DataValue *dataValue)
{
    gpio_set_level(LED_ESP, 0);

    //ESP_LOGI(MEMORY_TAG, "Antes de tirar copia : %d", xPortGetFreeHeapSize());


    UA_String RFID_Tag = UA_String_fromChars(RFID1);

    UA_Variant_setScalarCopy(&dataValue->value, &RFID_Tag,
                             &UA_TYPES[UA_TYPES_STRING]);

    //ESP_LOGI(MEMORY_TAG, "apos tirar a copia final: %d", xPortGetFreeHeapSize());

    dataValue->hasValue = true;
    UA_String_deleteMembers(&RFID_Tag);
    return UA_STATUSCODE_GOOD;
}

void addRFID(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "RFID");
    attr.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "RFID");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "RFID");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource RFID_Tag;
    RFID_Tag.read = readRFID;

    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        RFID_Tag, NULL, NULL);
}

//________________________________________________________________ RFID 1 Handler ______________________________________________________________________

void tag_handler(uint8_t *sn)
{ // serial number is always 5 bytes long
    ESP_LOGI(TAG, "Tag: %x %x %x %x %x",
             sn[0], sn[1], sn[2], sn[3], sn[4]

    );

    sprintf(RFID1, "%x %x %x %x %x", sn[0], sn[1], sn[2], sn[3], sn[4]);
    stateFlag1 = true;
}

void RC522Init()
{
    const rc522_start_args_t start_args = {
        .miso_io = 25,
        .mosi_io = 23,
        .sck_io = 19,
        .sda_io = 22,
        .callback = &tag_handler,

        // Uncomment next line for attaching RC522 to SPI2 bus. Default is VSPI_HOST (SPI3)
        .spi_host_id = HSPI_HOST};

    rc522_start(start_args);
}

//____________________________________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________________________________

//________________________________________________________________OPC RFID2_Flag2  ______________________________________________________________________

UA_StatusCode
readRFIDFlag2(UA_Server *server,
              const UA_NodeId *sessionId, void *sessionContext,
              const UA_NodeId *nodeId, void *nodeContext,
              UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
              UA_DataValue *dataValue)
{
    UA_Boolean flag2_State = stateFlag2;
    UA_Variant_setScalarCopy(&dataValue->value, &flag2_State,
                             &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
setRFIDFlag2(UA_Server *server,
             const UA_NodeId *sessionId, void *sessionContext,
             const UA_NodeId *nodeId, void *nodeContext,
             const UA_NumericRange *range, const UA_DataValue *data)
{
    memset(RFID2, 0, 20);
    stateFlag2 = false;
    UA_StatusCode status = stateFlag2 == false ? UA_STATUSCODE_GOOD : UA_STATUSCODE_BADINTERNALERROR;
    return status;
}

void addRFIDFlag2ControlNode(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Flag2");
    attr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "Flag2");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Flag2");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource flag2;
    flag2.read = readRFIDFlag2;
    flag2.write = setRFIDFlag2;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        flag2, NULL, NULL);
}

//________________________________________________________________OPC RFID 2 ______________________________________________________________________

UA_StatusCode
readRFID2(UA_Server *server,
          const UA_NodeId *sessionId, void *sessionContext,
          const UA_NodeId *nodeId, void *nodeContext,
          UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
          UA_DataValue *dataValue)
{

   // ESP_LOGI(MEMORY_TAG, "Antes de tirar copia : %d", xPortGetFreeHeapSize());

    UA_String RFID_Tag = UA_String_fromChars(RFID2);

    UA_Variant_setScalarCopy(&dataValue->value, &RFID_Tag,
                             &UA_TYPES[UA_TYPES_STRING]);

    //ESP_LOGI(MEMORY_TAG, "apos tirar a copia final: %d", xPortGetFreeHeapSize());

    dataValue->hasValue = true;
    UA_String_deleteMembers(&RFID_Tag);
    return UA_STATUSCODE_GOOD;
}

void addRFID2(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "RFID2");
    attr.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "RFID2");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "RFID2");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource RFID_Tag;
    RFID_Tag.read = readRFID2;

    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        RFID_Tag, NULL, NULL);
}

//________________________________________________________________ RFID 2 Handler ______________________________________________________________________

void tag_handler2(uint8_t *sn)
{ // serial number is always 5 bytes long
    ESP_LOGI(TAG, "Tag: %x %x %x %x %x",
             sn[0], sn[1], sn[2], sn[3], sn[4]

    );

    sprintf(RFID2, "%x %x %x %x %x", sn[0], sn[1], sn[2], sn[3], sn[4]);
    stateFlag2 = true;
}

void RC522Init_2()
{
    const rc522_start_args_t_2 start_args2 = {
        .miso_io_2 = 25,
        .mosi_io_2 = 23,
        .sck_io_2 = 19,
        .sda_io_2 = 18,
        .callback_2 = &tag_handler2,

        // Uncomment next line for attaching RC522 to SPI2 bus. Default is VSPI_HOST (SPI3)
        .spi_host_id_2 = HSPI_HOST};

    rc522_start_2(start_args2);
}

//________________________________________________________________ Leitura concentração de gases no ar ______________________________________________________________________

UA_StatusCode
readCurrentVoltage(UA_Server *server,
                   const UA_NodeId *sessionId, void *sessionContext,
                   const UA_NodeId *nodeId, void *nodeContext,
                   UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                   UA_DataValue *dataValue)
{
    UA_Float Voltage = ReadVoltage();
    PPM = Voltage;
    UA_Variant_setScalarCopy(&dataValue->value, &Voltage,
                             &UA_TYPES[UA_TYPES_FLOAT]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

void addCurrentVoltageDataSourceVariable(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Concentração de gases tóxicos");
    attr.dataType = UA_TYPES[UA_TYPES_FLOAT].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "Concentração de gases tóxicos");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Concentração de gases tóxicos");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
    UA_DataSource Voltage;
    configureAnalRead();
    Voltage.read = readCurrentVoltage;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        Voltage, NULL, NULL);
}

//________________________________________________________________ Leitura qualidade do ar ______________________________________________________________________

UA_StatusCode
readAirQuality(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeId, void *nodeContext,
               UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
               UA_DataValue *dataValue)
{

    UA_String Air_Quality;
    if (PPM < 300)
    {
        Air_Quality = UA_String_fromChars("Boa");
    }

    else if (PPM < 600)
    {
        Air_Quality = UA_String_fromChars("Média");
    }

    else if (PPM > 600)
    {
        Air_Quality = UA_String_fromChars("Ruim, PERIGO!!!");
    }

    UA_Variant_setScalarCopy(&dataValue->value, &Air_Quality,
                             &UA_TYPES[UA_TYPES_STRING]);

    dataValue->hasValue = true;
    UA_String_deleteMembers(&Air_Quality);
    return UA_STATUSCODE_GOOD;
}

void addAirQuality(UA_Server *server)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Qualidade do ar");
    attr.dataType = UA_TYPES[UA_TYPES_STRING].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ;

    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "Qualidade do ar");
    UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "Qualidade do ar");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource Air_Quality;
    Air_Quality.read = readAirQuality;

    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
                                        parentReferenceNodeId, currentName,
                                        variableTypeNodeId, attr,
                                        Air_Quality, NULL, NULL);
}
