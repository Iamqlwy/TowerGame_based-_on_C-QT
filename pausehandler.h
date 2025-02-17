#ifndef PAUSEHANDLER_H
#define PAUSEHANDLER_H

#include <QObject>
#include<QEvent>
class PauseHandler : public QObject
{
    Q_OBJECT
public:
    PauseHandler(QObject *parent = nullptr) : QObject(parent), isPaused(false) {}

    void setPaused(bool paused)
    {
        isPaused = paused;
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (isPaused && event->type() == QEvent::Timer) {
                return true; // 阻止定时器事件
            }
            return QObject::eventFilter(obj, event);
    }

private:
    bool isPaused;
};

#endif // PAUSEHANDLER_H
