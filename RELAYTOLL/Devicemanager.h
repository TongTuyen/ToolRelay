#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QMainWindow>
#include <QString>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMutex>
#include <QTimer>
#include "QRingBuffer.h"
#include "imodbusdevice.h"
#include <memory>
#include <clsrelay.h>
#include <clsdiscreteinput.h>
#include <stdio.h>
class QRadioButton;
class QLabel;
class QGroupBox;

typedef struct __attribute__((packed)) _S_MODBUS_FRAME
{
    uint8_t		Slaveaddress;
    uint8_t		function;
    uint8_t		StartAddressHi;
    uint8_t	    StartAddressLo;
    uint8_t	    QuantityHi;
    uint8_t		QuantityLo;
    uint8_t		CRCLo;
    uint8_t  	CRCHi;

} SMODBusFrame_t;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int btadd_id=0;
    uint8           m_u16Address = 0;
    QSerialPort     *pSerialPort;
    QTimer          *pTimer;
    QMutex          *pRxBuffMutex;
    QRingBuffer     *pRxBuffer;
    bool            m_bRunning = false;
   // QString         Relay;
    ~MainWindow();
private slots:
    void on_Start_clicked();
    void RunSimulation(bool bIsterminated);
    void on_SerialportDataReceived();
    void onTimerTicked();

    void on_btadd_clicked();

private:
    Ui::MainWindow *ui;
    QString Comname;
     void on_txtAddress_textChanged();
     static SMODBusFrame_t DecodeFrame(uint8_t* pu8Frame,uint8_t length );
     void ProcessMODBUS();
     void ProcessMODBUS_DI();
     // Relay
     uint8_t dataID[50];
     uint8_t datacoil[50];
     uint8_t m_di_datacoil[50];
     clsRelay ArrayRelay[50];
     // DI
     uint8_t m_di_dataID[50];
     uint8_t mu16_di_datacoil[50];

     clsdiscreteinput ArrayDI[50];


};

#endif // DEVICEMANAGER_H
