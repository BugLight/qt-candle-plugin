#ifndef CANDLECANBUSPLUGIN_H_
#define CANDLECANBUSPLUGIN_H_

#include <QCanBusFactoryV2>

class CandleCanBusPlugin : public QObject, public QCanBusFactoryV2 {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCanBusFactory" FILE
                        "qt-candle-plugin.json")
  Q_INTERFACES(QCanBusFactoryV2)

 public:
  QList<QCanBusDeviceInfo> availableDevices(
      QString* errorMessage) const override;

  QCanBusDevice* createDevice(const QString& interfaceName,
                              QString* errorMessage) const override;
};

#endif  // CANDLECANBUSPLUGIN_H_
