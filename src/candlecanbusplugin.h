#ifndef CANDLECANBUSPLUGIN_H_
#define CANDLECANBUSPLUGIN_H_

#include <QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#define CANBUS_FACTORY_CLASS QCanBusFactory
#include <QCanBusFactory>
#else
#define CANBUS_FACTORY_CLASS QCanBusFactoryV2
#include <QCanBusFactoryV2>
#endif

class CandleCanBusPlugin : public QObject, public CANBUS_FACTORY_CLASS {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCanBusFactory" FILE
                        "qt-candle-plugin.json")
  Q_INTERFACES(CANBUS_FACTORY_CLASS)

 public:
  QList<QCanBusDeviceInfo> availableDevices(
      QString* errorMessage) const override;

  QCanBusDevice* createDevice(const QString& interfaceName,
                              QString* errorMessage) const override;
};

#endif  // CANDLECANBUSPLUGIN_H_
