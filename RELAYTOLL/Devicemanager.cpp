#include "Devicemanager.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <crcmodbus.h>
#include <QRadioButton>
#include <QGridLayout>
#include <QGroupBox>
#include <qcolor.h>
#include <memory>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
      Comname = info.portName();
    ui->cbbCom->addItem(Comname);
    }
    //address
    this->ui->txtAddress->setMaxLength(5);
    this->ui->txtAddress->setInputMask("HH;_");
    ui->cbbProtocol->setEnabled(true);
    ui->cbbDevice->setEnabled(true);
    ui->cbbCom->setEnabled(true);
    ui->txtAddress->setEnabled(true);
    ui->Start->setText("START");
    //test
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_txtAddress_textChanged()
{
    bool b;
    this->m_u16Address = this->ui->txtAddress->text().remove(QChar(' ')).toUInt(&b, 10);
    qDebug("Slave address =%.2X",m_u16Address);
}
void MainWindow::RunSimulation(bool bIsterminated)
{
    if(bIsterminated == true)
    {
        this->pSerialPort = new QSerialPort(NULL);
        pSerialPort->setBaudRate(QSerialPort::Baud9600);
        pSerialPort->setParity(QSerialPort::EvenParity);
        pSerialPort->setDataBits(QSerialPort::Data8);
        pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
        pSerialPort->setPortName(this->ui->cbbCom->currentText());

        connect(pSerialPort, SIGNAL(readyRead()), this, SLOT(on_SerialportDataReceived()));
        qDebug() << "Openning COM port " << pSerialPort->portName() << " baud: " << pSerialPort->baudRate();


        if(!pSerialPort->open(QIODevice::ReadWrite))
        {
            return;
        }

        // Initialize Rx Ringbuffer
        pRxBuffMutex = new QMutex();
        pRxBuffer = new QRingBuffer();
        pRxBuffer->BufferInit(1024, pRxBuffMutex);


        pTimer = new QTimer(this);
        pTimer->setInterval(10);
        connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimerTicked()));
        qDebug() << "Starting RxProcess Thread";
        pTimer->start();


    }
    else
    {
        pSerialPort->close();
        pTimer->stop();
        delete pSerialPort;
        delete pRxBuffer;
        delete pRxBuffMutex;
        delete pTimer;
        qDebug() << "Stop RxProcess Thread";
    }

}
void MainWindow::on_SerialportDataReceived()
{

    QByteArray arr =  this->pSerialPort->readAll();
    qDebug() << "[DBG-L1]Rcv data: " << arr.toHex();
     pRxBuffer->BufferPushStream((void*)arr.data(), arr.size());
}
void MainWindow::onTimerTicked()
{

    if(pRxBuffer->BufferGetCount()==0)
    {
        return;
    }
    else if(ui->cbbProtocol->currentIndex()==0&&ui->cbbDevice->currentIndex()==0)
    {
       qDebug() << "RELAY MODBUS PROTOCOL";
       ProcessMODBUS();
    }
    else if(ui->cbbProtocol->currentIndex()==0&&ui->cbbDevice->currentIndex()==1)
    {
       qDebug() << "DI MODBUS PROTOCOL";
       ProcessMODBUS_DI();
    }


}
void MainWindow::on_Start_clicked()
{

    for(int i=0;i<btadd_id;i++)
    {
//       m_di_dataID[i]= ArrayDI[i].GetDeviceID();
//        qDebug("\n--------------dia chi cua DI% d  ",m_di_dataID[i]);
//        ArrayDI[i].getCoilData(&m_di_datacoil[i]);
//        qDebug("----------------DATACOIL%.2x",m_di_datacoil[i]);
       // DI
        qDebug("\n-----Start  ");
        m_di_dataID[i]=ArrayDI[i].GetDeviceID();
        qDebug("\n-----dia chi cua DI% d  ",m_di_dataID[i]);
        ArrayDI[i].getCoilData(&mu16_di_datacoil[i]);
        qDebug("-----DATACOIL%.2x",mu16_di_datacoil[i]);
    }
    if(this->m_bRunning== false)
    {
    RunSimulation(true);
    ui->Start->setText("STOP");
    ui->cbbProtocol->setEnabled(false);
    ui->cbbDevice->setEnabled(false);
    ui->cbbCom->setEnabled(false);
    ui->txtAddress->setEnabled(false);
    this->m_bRunning = true;
    }
    else {
        this->m_bRunning = false;
        ui->Start->setText("START");
        ui->cbbProtocol->setEnabled(true);
        ui->cbbDevice->setEnabled(true);
        ui->cbbCom->setEnabled(true);
        ui->txtAddress->setEnabled(true);
        RunSimulation(false);
        this->m_bRunning = false;

    }

}


void MainWindow::on_btadd_clicked()
{
     on_txtAddress_textChanged();
     qDebug() << "btadd_id "<<btadd_id;
     if(ui->cbbProtocol->currentIndex()==0&&ui->cbbDevice->currentIndex()==0)
     {
       // qDebug() << "RELAY MODBUS PROTOCOL";
       std::shared_ptr<clsRelay> relay = std::make_shared<clsRelay>();
       relay->SetDeviceID(m_u16Address);
       relay->createCoilGroupBox();
       this->ui->main_gridLayout->addLayout(relay->getRelayLayout(), btadd_id, 0);

     //  relay->getCoilData(&datacoil);
       ArrayRelay[btadd_id]=*relay;

     }
     if(ui->cbbProtocol->currentIndex()==0&&ui->cbbDevice->currentIndex()==1)
     {
       // qDebug() << "DI MODBUS PROTOCOL";
         std::shared_ptr<clsdiscreteinput> DigitalInput = std::make_shared<clsdiscreteinput>();
         DigitalInput->SetDeviceID(m_u16Address);
         //DigitalInput->SetDevType();
         DigitalInput->createCoilGroupBox();
         this->ui->DI_gridLayout->addLayout(DigitalInput->getDILayout(), btadd_id, 0);
       //  relay->getCoilData(&datacoil);
         ArrayDI[btadd_id]=*DigitalInput;
     }
     btadd_id ++;
}

SMODBusFrame_t MainWindow::DecodeFrame(uint8_t* pu8Frame,uint8_t length) {
    qDebug("DECODEFRAM");
   SMODBusFrame_t sResult = {0};
   uint8_t datacrc[2];
   if(length<8)
   {
       return sResult;
   }

   uint16_t crc = ModRTU_CRC(pu8Frame,length-2);
   qDebug("datacrc %.4X " ,crc);
           datacrc[0]=crc>>8;
           datacrc[1]=crc;
 //                   qDebug("datacrchi %.2X " ,datacrc[0]);
 //                   qDebug("datacrclo %.2X " ,datacrc[1]);
   if(datacrc[1]!=pu8Frame[length-2]||datacrc[0]!=pu8Frame[length-1])
       qDebug("ERROR ");
       return sResult;
   sResult.Slaveaddress = pu8Frame[0];
   sResult.function = pu8Frame[1];
   sResult.StartAddressLo = pu8Frame[2];
   sResult.StartAddressHi = pu8Frame[3];
   sResult.QuantityLo = pu8Frame[4];
   sResult.QuantityHi = pu8Frame[5];
   sResult.CRCLo = pu8Frame[6];
   sResult.CRCHi = pu8Frame[7];
   return sResult;

}

void MainWindow::ProcessMODBUS()
{//0

    static uint8_t  ucLen =0;
    static uint8_t	pucRecvFrame[258]={0};
    uint8_t lenght =0;
    qDebug("\nPROCESS MODBUS");
    ucLen = pRxBuffer->BufferGetCount();
    for(int i=0;i<btadd_id;i++)
    {
       dataID[i]= ArrayRelay[i].GetDeviceID();
        qDebug("\ndia chi cua relay%d ",dataID[i]);
       ArrayRelay[i].getCoilData(&datacoil[i]);
        qDebug("DATACOIL%.2x",datacoil[i]);
       ArrayRelay[i].getCoilData_DI(&m_di_datacoil[i]);
//       m_di_dataID[i]=ArrayDI[i].GetDeviceID();
      // ArrayDI[i].get(&m_di_datacoil[i]);
    }
    int indexid=0;
    while(ucLen>0)
    {//1
        pRxBuffer->BufferPop(&pucRecvFrame[0]);
        for(int i=0;i<btadd_id;i++)
        {//2
            if(pucRecvFrame[0]==dataID[i])
                indexid =i;

        }//2
        if(pucRecvFrame[0]==dataID[indexid])
         {//3
                    pRxBuffer->BufferPop(&pucRecvFrame[1]);
                    if(pucRecvFrame[1] == 0x01)
                    {//5
                        //function true , pop 6 byte and crc
                        pRxBuffer->BufferPopStream(&pucRecvFrame[2],6);
                        DecodeFrame(pucRecvFrame,ucLen);
                        // check value relay
                        // build frame

                        uint8_t RelayFrame[258];
                        //Slave address
                        RelayFrame[0]=pucRecvFrame[0];lenght++;
                        //fuction
                        RelayFrame[1]=pucRecvFrame[1];lenght++;
                        //byte count
                        RelayFrame[2] =sizeof(datacoil[indexid]);lenght++;
                        //data
                        RelayFrame[3]=datacoil[indexid];lenght++;
                        qDebug("lenght %.2x " ,datacoil[indexid]);
                        qDebug("lenght %i " ,lenght);
                        //crc
                        uint16_t crc = ModRTU_CRC(RelayFrame,lenght);
                        qDebug("datacrc %.4X " ,crc);
                        RelayFrame[5]=crc>>8;   lenght++;
                        RelayFrame[4]=crc;  lenght++;
                        qDebug("lenghtFrame %i " ,lenght);
                        // write reponse
                        this->pSerialPort->write((const char*)RelayFrame,lenght);

                    }//5
                    else if(pucRecvFrame[1] == 0x0f){
                        pRxBuffer->BufferPopStream(&pucRecvFrame[2],8);
                        DecodeFrame(pucRecvFrame,ucLen);
                        qDebug("RUN MULTIPLE\n  ");
                        uint8_t mod_command;
                        if(pucRecvFrame[7]==0xff)
                        {
                            qDebug("ON\n  ");
                            mod_command=pucRecvFrame[7];
                            uint8_t coilID =0;
                            //on multiple coil
                            for(uint8_t i=0;i<8;i++)
                            {
                                ArrayRelay[indexid].setCoilData(&mod_command,&i);
                            }
                        }
                        if(pucRecvFrame[7]==0x00)
                        {
                            qDebug("OFF\n  ");
                            mod_command=pucRecvFrame[7];
                            //off multiple coil
                            for(uint8_t i=0;i<8;i++)
                            {
                                ArrayRelay[indexid].setCoilData(&mod_command,&i);
                            }

                        }
                    }
                    else if(pucRecvFrame[1] == 0x02)
                    {
                        //function true , pop 6 byte and crc
                        pRxBuffer->BufferPopStream(&pucRecvFrame[2],6);
                        DecodeFrame(pucRecvFrame,ucLen);
                        // check value relay
                        // build frame
                        //qDebug("RUN DI\n  ");
                        uint8_t RelayFrame[258];
                        //Slave address
                        RelayFrame[0]=pucRecvFrame[0];lenght++;
                        //fuction
                        RelayFrame[1]=pucRecvFrame[1];lenght++;
                        //byte count
                        RelayFrame[2] =sizeof(m_di_datacoil[indexid]);lenght++;
                        //data
                        RelayFrame[3]=m_di_datacoil[indexid];lenght++;
                        qDebug("lenght %.2x " ,m_di_datacoil[indexid]);
                        qDebug("lenght %i " ,lenght);
                        //crc
                        uint16_t crc = ModRTU_CRC(RelayFrame,lenght);
                        qDebug("datacrc %.4X " ,crc);
                        RelayFrame[5]=crc>>8;   lenght++;
                        RelayFrame[4]=crc;  lenght++;
                        qDebug("lenghtFrame %i " ,lenght);
                        // write reponse
                        this->pSerialPort->write((const char*)RelayFrame,lenght);
                    }
                     else if(pucRecvFrame[1] == 0x05)
                           {
                              uint8_t coilID =0;
                            qDebug("FUNC WRITE SINGLE COIL");
                               //get data
                             pRxBuffer->BufferPopStream(&pucRecvFrame[2],6);
                               //check crc
                             DecodeFrame(pucRecvFrame,ucLen);
                             qDebug("FUNC WRITE SINGLE COIL%.2x",pucRecvFrame[3]);
                             uint8_t mod_command;
                                //chay lenh cm
                                if(pucRecvFrame[4]==0xff&&pucRecvFrame[5]==0x01)
                                    {
                                     mod_command=pucRecvFrame[4];
                                          if(pucRecvFrame[3]==0){
                                                coilID=0;
                                                ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==1){
                                                coilID=1;
                                               ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==2){
                                                coilID=2;
                                               ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==3){
                                                coilID=3;
                                               ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==4){
                                                coilID=4;
                                               ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==5){
                                                coilID=5;
                                              ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==6){
                                                coilID=6;
                                              ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==7){
                                                coilID=7;
                                               ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }

                                        }
                                 else if(pucRecvFrame[4]==0x00&&pucRecvFrame[5]==0x01)
                                        {
                                            mod_command=pucRecvFrame[4];
                                            if(pucRecvFrame[3]==0){
                                                coilID=0;
                                               ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==1){
                                                coilID=1;
                                              ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==2){
                                                coilID=2;
                                               ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==3){
                                                coilID=3;
                                              ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==4){
                                                coilID=4;
                                             ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==5){
                                                coilID=5;
                                              ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==6){
                                                coilID=6;
                                             ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                            if(pucRecvFrame[3]==7){
                                                coilID=7;
                                              ArrayRelay[indexid].setCoilData(&mod_command,&coilID);
                                            }
                                        }


                                        // kiem tra lai ket qua va bao cao lai cho bbb
                                        // build frame
                                        ArrayRelay[indexid].getCoilData(&datacoil[indexid]);
                                        qDebug("DATACOIL IN REPONSE%.2x",datacoil[indexid]);
                                        uint8_t lenght =0;
                                        uint8_t RelayFrame[258];
                                        //Slave address
                                        RelayFrame[0]=pucRecvFrame[0];lenght++;
                                        //fuction
                                        RelayFrame[1]=pucRecvFrame[1];lenght++;
                                        //byte count
                                        RelayFrame[2] =sizeof(datacoil[indexid]);lenght++;
                                        //data
                                        RelayFrame[3]=datacoil[indexid];lenght++;
                                        qDebug("lenght %i " ,lenght);
                                        //crc
                                        uint16_t crc = ModRTU_CRC(RelayFrame,lenght);
                                        qDebug("datacrc %.4X " ,crc);
                                        RelayFrame[5]=crc>>8;   lenght++;
                                        RelayFrame[4]=crc;  lenght++;
                                        qDebug("lenghtFrame %i " ,lenght);
                                        // write reponse
                                        this->pSerialPort->write((const char*)RelayFrame,lenght);

                                    }
                    else
                        break;

          }//3
            else
                qDebug("\nDia chia cua tao khac dia chi may muon hoi  ");
                break;

        if(lenght>=6)
        {

            ucLen=0;
            break;
        }

     }//1


}
//0
void MainWindow::ProcessMODBUS_DI()
{
    static uint8_t  ucLen =0;
    static uint8_t	pucRecvFrame[258]={0};
    uint8_t lenght =0;
    qDebug("\n DI PROCESS MODBUS");
    ucLen = pRxBuffer->BufferGetCount();
    for(int i=0;i<btadd_id;i++)
    {
       m_di_dataID[i]=ArrayDI[i].GetDeviceID();
       ArrayDI[i].getCoilData(&mu16_di_datacoil[i]);
       qDebug("-----DATACOIL%.2x",mu16_di_datacoil[i]);
    }
    int indexid=0;
    while(ucLen>0){

        pRxBuffer->BufferPop(&pucRecvFrame[0]);
        for(int i=0;i<btadd_id;i++)
        {//2
            if(pucRecvFrame[0]==m_di_dataID[i])
                indexid =i;

        }//2
        if(pucRecvFrame[0]==m_di_dataID[indexid])
        {//3
            pRxBuffer->BufferPop(&pucRecvFrame[1]);
            if(pucRecvFrame[1] == 0x02)
            {//4
                //function true , pop 6 byte and crc
                pRxBuffer->BufferPopStream(&pucRecvFrame[2],6);
                DecodeFrame(pucRecvFrame,ucLen);
                // check value relay
                // build frame

                uint8_t RelayFrame[258];
                //Slave address
                RelayFrame[0]=pucRecvFrame[0];lenght++;
                //fuction
                RelayFrame[1]=pucRecvFrame[1];lenght++;
                //byte count
                RelayFrame[2] =sizeof(mu16_di_datacoil[indexid]);lenght++;
                //data
                RelayFrame[3]=mu16_di_datacoil[indexid];lenght++;
                qDebug("\n-----mu16_di_datacoil %.4x " ,mu16_di_datacoil[indexid]);
                qDebug("\n-----RelayFrame[3] %.4x " ,RelayFrame[3]);
                //qDebug("lenght %i " ,lenght);
                //crc
                uint16_t crc = ModRTU_CRC(RelayFrame,lenght);
                qDebug("datacrc %.4X " ,crc);
                RelayFrame[5]=crc>>8;   lenght++;
                RelayFrame[4]=crc;  lenght++;
               // qDebug("lenghtFrame %i " ,lenght);
                // write reponse
                this->pSerialPort->write((const char*)RelayFrame,lenght);

            }//4
        }//3

        if(lenght>=6)
        {

            ucLen=0;
            break;
        }
    }
}




