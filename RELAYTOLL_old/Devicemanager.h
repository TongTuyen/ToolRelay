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
    uint8        m_u16Address = 0;
    QSerialPort     *pSerialPort;
    QTimer          *pTimer;
    QMutex          *pRxBuffMutex;
    QRingBuffer     *pRxBuffer;
    bool            m_bRunning = false;
    QString Relay;
    ~MainWindow();
private slots:
    void on_Start_clicked();
    void RunSimulation(bool bIsterminated);
    void on_SerialportDataReceived();
    void onTimerTicked();

    void on_btadd_clicked();

    void on_btdelete_clicked();

private:
    Ui::MainWindow *ui;
    QString Comname;
     void on_txtAddress_textChanged();
     static SMODBusFrame_t DecodeFrame(uint8_t* pu8Frame,uint8_t length );
     void ProcessMODBUS();
     uint8_t dataID[50];
     uint8_t datacoil[50];
     //std::shared_ptr<clsRelay> relay1 = std::make_shared<clsRelay>();
     clsRelay ArrayRelay[50];
     //static void 			UpdateDevices();
     //static void 			DeviceInitialize();
     //static void 			RegisterDevice(std::string szDeviceID, std::shared_ptr<imodbusdevice> pDevice);
     //static void 			RemoveDevice(std::string szDeviceID);

};

#endif // DEVICEMANAGER_H
