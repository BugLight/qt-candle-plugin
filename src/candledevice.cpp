#include "candledevice.h"

#include <candle.h>
#include <string.h>

#include <QVector>

CandleDevice::CandleDevice(candle_handle handle) noexcept : handle_(handle) {}

CandleDevice::~CandleDevice() {
  close();
  if (readThread_.joinable()) readThread_.join();
  candle_dev_free(handle_);
}

bool CandleDevice::open() {
  if (candle_dev_open(handle_)) {
    if (candle_channel_start(handle_, 0, 0)) {
      setState(ConnectedState);
      canRead_ = true;
      readThread_ = std::thread(&CandleDevice::read, this);
      return true;
    }
    candle_dev_close(handle_);
  }
  setState(UnconnectedState);
  return false;
}

void CandleDevice::close() {
  if (state() == UnconnectedState) return;
  canRead_ = false;
  readMutex_.lock();
  candle_channel_stop(handle_, 0);
  candle_dev_close(handle_);
  setState(UnconnectedState);
  readMutex_.unlock();
}

void CandleDevice::read() {
  while (canRead_) {
    candle_frame_t frame;
    std::lock_guard<std::mutex> lock(readMutex_);
    if (canRead_ && candle_frame_read(handle_, &frame, 100)) {
      auto id = candle_frame_id(&frame);
      auto data = QByteArray::fromRawData(
          reinterpret_cast<const char*>(candle_frame_data(&frame)),
          candle_frame_dlc(&frame));
      QCanBusFrame qframe(id, data);
      if (candle_frame_is_rtr(&frame))
        qframe.setFrameType(QCanBusFrame::RemoteRequestFrame);
      auto type = candle_frame_type(&frame);
      if (type == CANDLE_FRAMETYPE_ERROR)
        qframe.setFrameType(QCanBusFrame::ErrorFrame);
      if (type == CANDLE_FRAMETYPE_UNKNOWN)
        qframe.setFrameType(QCanBusFrame::UnknownFrame);
      qframe.setLocalEcho(type == CANDLE_FRAMETYPE_ECHO);
      qframe.setExtendedFrameFormat(candle_frame_is_extended_id(&frame));
      qframe.setTimeStamp(QCanBusFrame::TimeStamp::fromMicroSeconds(
          candle_frame_timestamp_us(&frame)));
      enqueueReceivedFrames(QVector<QCanBusFrame>{qframe});
    }
  }
}

bool CandleDevice::writeFrame(const QCanBusFrame& frame) {
  if (state() != ConnectedState) return false;
  candle_frame_t candleFrame;
  candleFrame.can_id = frame.frameId();
  const auto data = frame.payload();
  candleFrame.can_dlc = data.length();
  memmove(candleFrame.data, data.constData(), data.length());
  return candle_frame_send(handle_, 0, &candleFrame);
}

QString CandleDevice::interpretErrorFrame(const QCanBusFrame& errorFrame) {
  // TODO: add error messages
  return QString();
}

QList<QCanBusDeviceInfo> CandleDevice::interfaces() {
  QList<QCanBusDeviceInfo> devices;
  candle_list_handle list;
  if (candle_list_scan(&list)) {
    uint8_t length;
    if (candle_list_length(list, &length)) {
      for (auto i = 0; i < length; ++i) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 2, 0)
        // https://github.com/qt/qtserialbus/commit/3b2ce7c739ca2bb5b47d26fc1b0ee4294f49f0a4
        auto info = createDeviceInfo(QStringLiteral("candle"), "can" + QString::number(i), QString(),
                                     "Candle CAN device", QString(), 0, false, true);
#else
        auto info = createDeviceInfo("can" + QString::number(i), "",
                                     "Candle CAN device", 0, false, true);
#endif
        devices.append(info);
      }
    }
    candle_list_free(list);
  }
  return devices;
}

QCanBusDevice* CandleDevice::createDevice(const QString& interfaceName) {
  if (!interfaceName.startsWith("can")) return nullptr;
  bool success;
  auto i = interfaceName.mid(3).toInt(&success);
  if (!success) return nullptr;
  QCanBusDevice* device = nullptr;
  candle_list_handle list;
  if (candle_list_scan(&list)) {
    candle_handle handle;
    if (candle_dev_get(list, i, &handle)) device = new CandleDevice(handle);
    candle_list_free(list);
  }
  return device;
}
