#include "candlecanbusplugin.h"

#include "candledevice.h"

QList<QCanBusDeviceInfo> CandleCanBusPlugin::availableDevices(
    QString* errorMessage) const {
  Q_UNUSED(errorMessage);
  return CandleDevice::interfaces();
}

QCanBusDevice* CandleCanBusPlugin::createDevice(const QString& interfaceName,
                                                QString* errorMessage) const {
  Q_UNUSED(errorMessage);
  return CandleDevice::createDevice(interfaceName);
}
