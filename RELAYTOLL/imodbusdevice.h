#ifndef IMODBUSDEVICE_H
#define IMODBUSDEVICE_H
#include <iostream>
#include <stdint.h>

typedef enum _E_DEV_TYPE
{
    DEV_TYPE_BEGIN = 0,
    DEV_TYPE_SENSOR_NODE,
    DEV_TYPE_SENSOR_AIR_TEMPERATURE,
    DEV_TYPE_SENSOR_AIR_HUMIDITY,
    DEV_TYPE_SENSOR_SOIL_TEMPERATURE,
    DEV_TYPE_SENSOR_SOIL_MOISTURE,
    DEV_TYPE_ACTUATOR_VALVE,
    DEV_TYPE_ACTUATOR_PUMP,
    DEV_TYPE_INPUT_DIGITAL,
    DEV_TYPE_INPUT_ANALOG,
    DEV_TYPE_COUNTER,
    DEV_TYPE_TANK,
    DEV_TYPE_END,
    DEV_TYPE_RELAY,
    DEV_TYPE_DI,
    DEV_TYPE_AI
} DevType_t;
class imodbusdevice
{
public:
    imodbusdevice();
    virtual void 					SetDeviceID(uint8_t szDeviceID) = 0;
    virtual uint8_t                 GetDeviceID() = 0;

    virtual void					SetDevType(DevType_t type) = 0;
    virtual DevType_t				GetDevType() = 0;



};

#endif // IMODBUSDEVICE_H
