#include "clsdiscreteinput.h"

clsdiscreteinput::clsdiscreteinput()
{
    m_u8DeviceType = DEV_TYPE_DI;
}

clsdiscreteinput::~clsdiscreteinput()
{

}
void clsdiscreteinput::SetDeviceID(uint8_t szDeviceID)
{
    m_szDeviceID = szDeviceID;
}

uint8_t clsdiscreteinput::GetDeviceID()
{
    return m_szDeviceID;
}

void clsdiscreteinput::SetDevType(DevType_t type)
{
    m_u8DeviceType = type;
}

DevType_t clsdiscreteinput::GetDevType()
{
    return m_u8DeviceType;
}

void clsdiscreteinput::createCoilGroupBox()
{
    uint8_t NameId = GetDeviceID();
    QString m_nameDevice = "DI";
    QString Str = QString::number(NameId);
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
//        m_pRelaygrid->addWidget(Coil9->createCoil(),1,1);
//        m_pRelaygrid->addWidget(Coil10->createCoil(),1,2);
//        m_pRelaygrid->addWidget(Coil11->createCoil(),1,3);
//        m_pRelaygrid->addWidget(Coil12->createCoil(),1,4);
//        m_pRelaygrid->addWidget(Coil13->createCoil(),1,5);
//        m_pRelaygrid->addWidget(Coil14->createCoil(),1,6);
//        m_pRelaygrid->addWidget(Coil15->createCoil(),1,7);
//        m_pRelaygrid->addWidget(Coil16->createCoil(),1,8);
        m_pRelaygrid->addWidget(Coil17->Namerelay(&m_nameDevice,&Str),0,0);

    }

}

QGridLayout *clsdiscreteinput::getDILayout()
{
    return m_pRelaygrid;
}

void clsdiscreteinput::getCoilData(uint8_t *data)
{
       // qDebug("\ngetcoildata\n" );
     //check value relay
       uint8_t Coildata[16];
       Coil1->getCoilValues(&Coildata[0]);
       Coil2->getCoilValues(&Coildata[1]);
       Coil3->getCoilValues(&Coildata[2]);
       Coil4->getCoilValues(&Coildata[3]);
       Coil5->getCoilValues(&Coildata[4]);
       Coil6->getCoilValues(&Coildata[5]);
       Coil7->getCoilValues(&Coildata[6]);
       Coil8->getCoilValues(&Coildata[7]);
//       Coil9->getCoilValues(&Coildata[8]);
//       Coil10->getCoilValues(&Coildata[9]);
//       Coil11->getCoilValues(&Coildata[10]);
//       Coil12->getCoilValues(&Coildata[11]);
//       Coil13->getCoilValues(&Coildata[12]);
//       Coil14->getCoilValues(&Coildata[13]);
//       Coil15->getCoilValues(&Coildata[14]);
//       Coil16->getCoilValues(&Coildata[15]);
       uint8_t u8RelayData = 0;
        for (int i  = 0; i < 16; i ++)
        {
            u8RelayData |= Coildata[i] ? (1<<i) : 0;
        }
        qDebug("getcoildata %.2x " ,u8RelayData);
        *data=u8RelayData;
        return ;
}
