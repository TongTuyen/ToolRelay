#ifndef CLSDISCRETEINPUT_H
#define CLSDISCRETEINPUT_H
#include "imodbusdevice.h"
#include<crcmodbus.h>
#include <QGridLayout>
#include <clscoil.h>
#include <memory>
class clsdiscreteinput:public imodbusdevice
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
//    std::shared_ptr<clsCoil> Coil9 = std::make_shared<clsCoil>();
//    std::shared_ptr<clsCoil> Coil10 = std::make_shared<clsCoil>();
//    std::shared_ptr<clsCoil> Coil11 = std::make_shared<clsCoil>();
//    std::shared_ptr<clsCoil> Coil12 = std::make_shared<clsCoil>();
//    std::shared_ptr<clsCoil> Coil13 = std::make_shared<clsCoil>();
//    std::shared_ptr<clsCoil> Coil14 = std::make_shared<clsCoil>();
//    std::shared_ptr<clsCoil> Coil15 = std::make_shared<clsCoil>();
//    std::shared_ptr<clsCoil> Coil16 = std::make_shared<clsCoil>();

    std::shared_ptr<clsCoil> Coil17 = std::make_shared<clsCoil>();

public:
    clsdiscreteinput();
    virtual ~clsdiscreteinput();
    void 					SetDeviceID(uint8_t szDeviceID);
    uint8_t                 GetDeviceID();
    void					SetDevType(DevType_t type) override;
    DevType_t				GetDevType() override;
    void                    createCoilGroupBox();
    QGridLayout*            getDILayout();
    void getCoilData(uint8_t *data);
};

#endif // CLSDISCRETEINPUT_H
