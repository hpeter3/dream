#ifndef CTRX_H
#define CTRX_H

#include <QThread>
#include "../DrmTransceiver.h"
#include <vector>
#include <QString>

class CTRx : public QThread, public CDRMTransceiver
{
    Q_OBJECT
public:
    explicit CTRx(QThread *parent = nullptr);
    virtual int GetFrequency()=0;

signals:
    void InputDeviceChanged(const QString &device);
    void OutputDeviceChanged(const QString &device);
    void soundUpscaleRatioChanged(int);

public slots:
    virtual void SetFrequency(int)=0;
    virtual void SetSoundSignalUpscale(int) {}
};

#endif // CTRX_H
