#ifndef CTX_H
#define CTX_H

#include "ctrx.h"
#include <QObject>
#include <QString>

class CDRMTransmitter;

class CTx : public CTRx
{
    Q_OBJECT
public:
    explicit CTx(CDRMTransmitter& nRx, CTRx *parent = nullptr);
    virtual ~CTx() override;
    void run() override;

    virtual void GetInputDevice(std::string&);
    virtual void GetOutputDevice(std::string&);
    void EnumerateInputs(std::vector<std::string>& names, std::vector<std::string>& descriptions, std::string& defaultInput) override;
    void EnumerateOutputs(std::vector<std::string>& names, std::vector<std::string>& descriptions, std::string& defaultOutput) override;
    virtual CSettings*				GetSettings() override;
    virtual CParameter*				GetParameters() override;
    virtual bool				IsReceiver() const override { return false;}
    virtual bool				IsTransmitter() const override { return true;}
    virtual int GetIQOutput();
    virtual bool isHighQualityIQ();
    virtual bool isOutputAmplified();
    virtual bool CanEncode(int);
    virtual _REAL GetCarrierOffset();
    virtual int GetLevelMeter();
    virtual bool GetTransmissionStatus(std::string, _REAL);
    virtual int GetFrequency() override;

public slots:
    virtual void LoadSettings() override;
    virtual void SaveSettings() override;
    virtual void SetInputDevice(std::string) override;
    virtual void SetOutputDevice(std::string) override;
    void SetInputDevice(const QString &device); //new Qt slot
    void SetOutputDevice(const QString &device); //new Qt slot
    virtual void Restart();
    virtual void Stop();
    virtual void SetSettings(CSettings* pNewSettings) override;
    virtual void SetTextMessage(std::string);
    void SetTextMessage(const QString &msg);
    virtual void ClearTextMessage();
    virtual void SetPicFileName(std::string, std::string);
    void SetPicFileName(const QString &name, const QString &desc);
    virtual void SetPathRemoval(bool);
    virtual void ClearPicFileNames();
    virtual void SetHighQualityIQ(bool);
    virtual void SetOutputAmplified(bool);
    virtual void SetCarrierOffset(_REAL);
    virtual void SetIQOutput(int);
    virtual void SetFrequency(int) override;
    
signals:
	void OutputDeviceChanged(const QString &device);
	void InputDeviceChanged(const QString &device);

private:
    CDRMTransmitter& tx;
    ERunState eRunState;

};


#endif // CTX_H
