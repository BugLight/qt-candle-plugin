#include "candlecanbusplugin.h"

QList<QCanBusDeviceInfo> CandleCanBusPlugin::availableDevices(
    QString* errorMessage) const {
  return QList<QCanBusDeviceInfo>();
}

QCanBusDevice* CandleCanBusPlugin::createDevice(const QString& interfaceName,
                                                QString* errorMessage) const {
  return nullptr;
}
