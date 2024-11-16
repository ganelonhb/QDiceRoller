#ifndef QDMSWIDGET_H
#define QDMSWIDGET_H

#include <QWidget>
#include <QObject>
#include <QMenuBar>

#ifdef _WIN32
#include <windows.h>

class Mutex {
public:
    Mutex() { InitializeCriticalSection(&cs); }
    ~Mutex() { DeleteCriticalSection(&cs); }

    void lock() { EnterCriticalSection(&cs); }
    void unlock() { LeaveCriticalSection(&cs); }

private:
    CRITICAL_SECTION cs;

    Mutex(const Mutex &) = delete;
    Mutex &operator=(const Mutex &) = delete;
};

template <typename M>
class LockGuard {
public:
    explicit LockGuard(M &mutex) : m_mutex(mutex) {
        m_mutex.lock();
    }

    ~LockGuard() {
        m_mutex.unlock();
    }

private:
    M &m_mutex;

    LockGuard(const LockGuard&) = delete;
    LockGuard &operator=(const LockGuard&) = delete;

};

#endif

enum class WidgetType {
    WINDOW,
    TAB,
    FLOATING_DOCK,
};

class QDMSWidget : public QWidget
{
    Q_OBJECT
public:
    QDMSWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
        :QWidget(parent, f) {}

    bool isCloseBlocked()
    {
#ifdef _WIN32
        LockGuard<Mutex> lock(mutex);
#else
        std::lock_guard<std::mutex> lock(mutex);
#endif

        return m_blockClose;
    }

    void blockClose()
    {
#ifdef _WIN32
        LockGuard<Mutex> lock(mutex);
#else
        std::lock_guard<std::mutex> lock(mutex);
#endif
        m_blockClose = true;
    }

    void unblockClose()
    {
#ifdef _WIN32
        LockGuard<Mutex> lock(mutex);
#else
        std::lock_guard<std::mutex> lock(mutex);
#endif
        m_blockClose = false;
    }

    WidgetType type() const { return m_type; }
    void setType(const WidgetType &t)
    {
        m_type = t;
    }

private:
    std::atomic<bool> m_blockClose;

#ifdef _WIN32
    Mutex mutex;
#else
    std::mutex mutex;
#endif

    WidgetType m_type;

    QMenuBar *menuBar{nullptr};
};

#endif // QDMSWIDGET_H
