#ifndef PICTUR_H
#define PICTUR_H
#include <QPainter>
#include <QMainWindow>
#include <QPaintEvent>

class pictur : public QMainWindow
{
    Q_OBJECT
public:
    explicit pictur(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // PICTUR_H
