#include "clsrelay.h"
#include <QDebug>
#include<QRadioButton>
#include <QGridLayout>
#include <QGroupBox>
#include <iostream>
#include <QBoxLayout>
#include <clscoil.h>
#include <QList>
#include <QString>

clsRelay::clsRelay()
{
    m_u8DeviceType 	= DEV_TYPE_RELAY;
    //ListCoil.clear();
}
clsRelay::~clsRelay()
{

}

void clsRelay::SetDeviceID(uint8_t szDeviceID) {
       m_szDeviceID = szDeviceID;
}

uint8_t clsRelay::GetDeviceID() {
    return m_szDeviceID;
}

void clsRelay::SetDevType(DevType_t type) {
    m_u8DeviceType = type;
}

DevType_t clsRelay::GetDevType() {
    return m_u8DeviceType;
}


void clsRelay::createCoilGroupBox(){

        uint8_t relayId = GetDeviceID();
        QString m_nameDevice = "Relay";
        QString Str = QString::number(relayId);
    if (m_pRelaygrid == nullptr) {
        m_pRelaygrid = new QGridLayout;
        m_pRelaygrid->addWidget(Coil1->createCoil(),0,1);
        m_pRelaygrid->addWidget(Coil2->createCoil(),0,2);
        m_pRelaygrid->addWidget(Coil3->createCoil(),0,3);
        m_pRelaygrid->addWidget(Coil4->createCoil(),0,4);
        m_pRelaygrid->addWidget(Coil5->createCoil(),0,5);
        m_pRelaygrid->addWidget(Coil6->createCoil(),0,6);
        m_pRelaygrid->addWidget(Coil7->createCoil(),0,7);
        m_pRelaygrid->addWidget(Coil8->createCoil(),0,8);
        m_pRelaygrid->addWidget(Coil9->Namerelay(&m_nameDevice,&Str),0,0);
        m_pRelaygrid->addWidget(Coildi1->createCoil(),1,1);
        m_pRelaygrid->addWidget(Coildi2->createCoil(),1,2);
        m_pRelaygrid->addWidget(Coildi3->createCoil(),1,3);
        m_pRelaygrid->addWidget(Coildi4->createCoil(),1,4);
        m_pRelaygrid->addWidget(Coildi5->createCoil(),1,5);
        m_pRelaygrid->addWidget(Coildi6->createCoil(),1,6);
        m_pRelaygrid->addWidget(Coildi7->createCoil(),1,7);
        m_pRelaygrid->addWidget(Coildi8->createCoil(),1,8);
    }
}

QGridLayout *clsRelay::getRelayLayout()
{
    return m_pRelaygrid;
}

QGridLayout *clsRelay::RemoveRelayLayout()
{


}



void clsRelay::getCoilData(uint8_t *data)
{
//qDebug("\ngetcoildata\n" );
 //check value relay
   uint8_t Coildata[8];
   Coil1->getCoilValues(&Coildata[0]);
   Coil2->getCoilValues(&Coildata[1]);
   Coil3->getCoilValues(&Coildata[2]);
   Coil4->getCoilValues(&Coildata[3]);
   Coil5->getCoilValues(&Coildata[4]);
   Coil6->getCoilValues(&Coildata[5]);
   Coil7->getCoilValues(&Coildata[6]);
   Coil8->getCoilValues(&Coildata[7]);
    uint8_t u8RelayData = 0;
    for (int i  = 0; i < 8; i ++)
    {
        u8RelayData |= Coildata[i] ? (1<<i) : 0;
    }
    qDebug("\ngetcoildata %.2x " ,u8RelayData);
    *data=u8RelayData;
    return ;
}

void clsRelay::setCoilData(uint8_t *mod_data,uint8_t *data)
{
    uint8_t updatedata=*data;
    uint8_t updatemod_data=*mod_data;
    int values;
    if(updatemod_data ==0xff)
    {
        values=0;
        //cm on coil

        if(updatedata==0)
        {
            qDebug("cm on coil 0");
            //m_pCoil1On->setChecked(true);
            Coil1->setCoilValues(&values);
        }
        if(updatedata==1)
        {

            Coil2->setCoilValues(&values);
        }
        if(updatedata==2)
        {
            Coil3->setCoilValues(&values);
        }
        if(updatedata==3)
        {
            Coil4->setCoilValues(&values);
        }
        if(updatedata==4)
        {
            Coil5->setCoilValues(&values);
        }
        if(updatedata==5)
        {
            Coil6->setCoilValues(&values);
        }
        if(updatedata==6)
        {
            Coil7->setCoilValues(&values);
        }
        if(updatedata==7)
        {
            Coil8->setCoilValues(&values);
        }
    }
    else if(updatemod_data ==0x00)
    {
        //cm off coil
        qDebug("cm off coil");
        values =1;
        if(updatedata==0)
        {
            Coil1->setCoilValues(&values);
        }
        if(updatedata==1)
        {
            Coil2->setCoilValues(&values);
        }
        if(updatedata==2)
        {
            Coil3->setCoilValues(&values);
        }
        if(updatedata==3)
        {
            Coil4->setCoilValues(&values);
        }
        if(updatedata==4)
        {
            Coil5->setCoilValues(&values);
        }
        if(updatedata==5)
        {
            Coil6->setCoilValues(&values);
        }
        if(updatedata==6)
        {
            Coil7->setCoilValues(&values);
        }
        if(updatedata==7)
        {
            Coil8->setCoilValues(&values);
        }
    }


}

void clsRelay::getCoilData_DI(uint8_t *data)
{
    uint8_t Coildata[8];
    Coildi1->getCoilValues(&Coildata[0]);
    Coildi2->getCoilValues(&Coildata[1]);
    Coildi3->getCoilValues(&Coildata[2]);
    Coildi4->getCoilValues(&Coildata[3]);
    Coildi5->getCoilValues(&Coildata[4]);
    Coildi6->getCoilValues(&Coildata[5]);
    Coildi7->getCoilValues(&Coildata[6]);
    Coildi8->getCoilValues(&Coildata[7]);
     uint8_t u8RelayData = 0;
     for (int i  = 0; i < 8; i ++)
     {
         u8RelayData |= Coildata[i] ? (1<<i) : 0;
     }
     qDebug("\ngetcoildata %.2x " ,u8RelayData);
     *data=u8RelayData;
     return ;
}


