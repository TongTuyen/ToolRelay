#include "clscoil.h"
#include <QRadioButton>
#include <QBoxLayout>

clsCoil::clsCoil(int coilid)
{
    m_coilId = coilid;
}

clsCoil::clsCoil(QWidget *parent) :
    QWidget(parent)
{
}
QGroupBox *clsCoil::createCoil()
{
      // m_groupBox = new QGroupBox();
       m_pCoilOn->setChecked(true);
       m_vbox->addWidget(m_pCoilOn);
       m_vbox->addWidget(m_pCoilOff);
       m_vbox->addStretch(1);
       m_groupBox->setLayout(m_vbox);
       m_groupBox->setFixedSize(55,70);
       return m_groupBox;
}

QGroupBox *clsCoil::Namerelay(uint8_t *relayID)
{
    m_namerelay1->setText("Relay");
    m_namerelay2->setText((QString)*relayID);
    m_vbox->addWidget(m_namerelay1);
    m_vbox->addWidget(m_namerelay2);
    m_vbox->addStretch(1);
    m_groupBox->setLayout(m_vbox);
    m_groupBox->setFixedSize(50,70);
    return m_groupBox;
}

void clsCoil::getCoilValues(uint8_t *coilvalues)
{
    *coilvalues=m_pCoilOn->isChecked()?1:0;
}

void clsCoil::setCoilValues(int *coilvalues)
{
    if(*coilvalues ==1)
    {
        m_pCoilOff->setChecked(true);
    }
    else
        m_pCoilOn->setChecked(true);

}

void clsCoil::setCoilID(int coilid)
{
    m_coilId = coilid;
}






