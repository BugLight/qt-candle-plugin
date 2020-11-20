#ifndef CANDLEDEVICE_H_
#define CANDLEDEVICE_H_

#include <mutex>
#include <thread>

#include <QCanBusDevice>

#include <candle.h>

class CandleDevice : public QCanBusDevice {
  Q_OBJECT

 public:
  explicit CandleDevice(candle_handle handle) noexcept;

  ~CandleDevice();

  // No copy
  CandleDevice(const CandleDevice&) = delete;
  CandleDevice& operator=(const CandleDevice&) = delete;

  // No move
  CandleDevice(CandleDevice&&) = delete;
  CandleDevice& operator=(CandleDevice&&) = delete;

  bool writeFrame(const QCanBusFrame& frame) override;

  QString interpretErrorFrame(const QCanBusFrame& errorFrame) override;

  static QList<QCanBusDeviceInfo> interfaces();

  static QCanBusDevice* createDevice(const QString& interfaceName);

 protected:
  bool open() override;

  void close() override;

 private:
  void read();

  candle_handle handle_;
  std::atomic_bool canRead_;
  std::thread readThread_;
  std::mutex readMutex_;
};

#endif  // CANDLEDEVICE_H_
