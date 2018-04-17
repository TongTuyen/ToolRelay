#ifndef CLSCOIL_H
#define CLSCOIL_H

#include <QWidget>
#include <QRadioButton>
#include <QGroupBox>
#include <QBoxLayout>
#include <QList>
#include <QLabel>
#include <QString>
class clsCoil : public QWidget
{
    Q_OBJECT
public:
    clsCoil(int coilid);
    explicit clsCoil(QWidget *parent = 0);
    QGroupBox *createCoil();
    QGroupBox *Namerelay(uint8_t *relayID);
    void getCoilValues(uint8_t *coilvalues);
    void setCoilValues(int *coilvalues);
    void setCoilID(int coilid);


private:
    int                                 m_coilId;
    QRadioButton                       *m_pCoilOn  = new QRadioButton(tr("On"));
    QRadioButton                       *m_pCoilOff = new QRadioButton(tr("Off"));

    QGroupBox                          *m_groupBox = new QGroupBox(tr(""));
    QVBoxLayout                        *m_vbox     = new QVBoxLayout;
    QLabel                              *m_namerelay1 = new QLabel;
    QLabel                              *m_namerelay2 = new QLabel;
signals:
public slots:

};

#endif // CLSCOIL_H
