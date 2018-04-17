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
    uint8_t      						    m_szDeviceID;
   // std::string 						m_szDescription;
   // std::string						m_szGatewayID;
    QGridLayout                        *m_pRelaygrid;// = new QGridLayout;
    //QList<clsCoil*>                      ListCoil ;
    std::shared_ptr<clsCoil> Coil1 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil2 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil3 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil4 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil5 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil6 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil7 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil8 = std::make_shared<clsCoil>();
    std::shared_ptr<clsCoil> Coil9 = std::make_shared<clsCoil>();
public:
    clsRelay();
    virtual ~clsRelay();
     void 					SetDeviceID(uint8_t szDeviceID);
     uint8_t 			GetDeviceID() ;
//     void 				SetDeviceDescription(std::string szDescription) override {m_szDescription = szDescription;}
//     std::string 			GetDeviceDescription() override { return m_szDescription;}
     void					SetDevType(DevType_t type) override;
     DevType_t				GetDevType() override;

//  int16_t		 		ExecuteCommand(uint16_t u16Cmd, uint16_t u16SubCmd) override;
//     char*		 			GetCurrentStatus();
//     bool					IsVisible();
//     void					SetVisible(bool visible);
//     uint8_t				UpdateValues(void* pvArgs);
  //   uint16_t 				ReadValue();


    void createCoilGroupBox();
    QGridLayout* getRelayLayout();
    QGridLayout* RemoveRelayLayout();
  //  QGroupBox *createCoil(QRadioButton *m_pCoilOn,QRadioButton *m_pCoilOff);
    void getCoilData(uint8_t *data);
    void setCoilData(uint8_t *mod_data, uint8_t *data);

};

#endif // CLSRELAY_H

