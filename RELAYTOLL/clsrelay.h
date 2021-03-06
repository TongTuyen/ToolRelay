#ifndef CLSRELAY_H
#define CLSRELAY_H
#include "imodbusdevice.h"
#include<crcmodbus.h>
#include <QMutex>
#include <QTimer>
#include "QRingBuffer.h"
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QGridLayout>
#include <QRadioButton>
#include <QList>
#include <clscoil.h>
#include <memory>


class QGroupBox;

class clsRelay :public imodbusdevice
{
private:
    DevType_t 							m_u8DeviceType;
    uint8_t      						m_szDeviceID;
    QGridLayout                        *m_pRelaygrid;
    std::shared_ptr<clsCoil> Coil1 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil2 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil3 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil4 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil5 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil6 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil7 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil8 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil9 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coildi1 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coildi2 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coildi3 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coildi4 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coildi5 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coildi6 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coildi7 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coildi8 = std::make_shared<clsCoil>();

public:
    clsRelay();
    virtual ~clsRelay();
    void 					SetDeviceID(uint8_t szDeviceID);
    uint8_t                 GetDeviceID();
    void					SetDevType(DevType_t type) override;
    DevType_t				GetDevType() override;
    void                    createCoilGroupBox();
    QGridLayout*            getRelayLayout();
    QGridLayout*            RemoveRelayLayout();

    void getCoilData(uint8_t *data);
    void setCoilData(uint8_t *mod_data, uint8_t *data);
    void getCoilData_DI(uint8_t *data);

};

#endif // CLSRELAY_H

