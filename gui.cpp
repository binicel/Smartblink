#include "gui.h"
#include <QDebug>

Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this); // grafische Oberfläche
    m_leds = new Gpio(this);
    m_state = 0;
    m_timer = new QTimer();
     //Verbinde: Quelle(Timer aus klasse Timer) -> Zeil (Toggel-Funktion aus Klasse Gui)
    connect(m_timer, &QTimer::timeout, this, &Gui::toggle); // verbindung Timer -> Gui Label
    m_timer->start(TIMEOUT);
}

void Gui::on_speedSlider_valueChanged(int value)
{
    m_timer->start(1000/value);
}

void Gui::on_blinkButton_clicked()
{
    m_switch = 1;
}
#include <QDebug>
void Gui::on_lauflichtButton_clicked()
{
    m_switch = 0;
    cnt = 1;
}

void Gui::toggle() //Ein Toggl is for switching between these two
{
    //Blinky mit anbleibenden LEDS
     // qDebug() << "toggle";
    m_state = !m_state;// Signal umkehren 1 => 0 / 0 => 1

    if(m_switch == 1)
    {
        label -> setNum(m_state); // So sehen wir auch ohne dem Shield wie sich der Blinky verhält /Also ob High(1) or Low(0)
       // Es entsteht dadurch ein Bug/ Wenn man von Blinker auf Lauflicht switched steht beim Regler entweder 0 oder 1 und nd welche Frequenz man hat also 1-20
        if(m_state == 1)
        {
            cnt = 18; // Irgendeine Hohe Zahl
        }else {
            cnt = 0;
        }
        m_leds->set(cnt);
    }
    if(m_switch == 0)
    {
        m_leds->set(cnt);
            if(cnt < 10) // soll bei *2 höher sein als 12
            {
                cnt = cnt * 2;
            }
            else {
                cnt = 1;
            }
    }
}
