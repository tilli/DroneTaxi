#ifndef VIDEO_H
#define VIDEO_H

#include <QGraphicsWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QThread>
#include <QTimer>
#include "dronecontrol.h"
#include "paddetection.h"
#include "videoprocessor.h"

// #define TARGET_CPU_ARM 1
#include <navdata.h>
#include "vlib.h"

#define FRONT_VIDEO_WIDTH 320.0f
#define FRONT_VIDEO_HEIGHT 240.0f
#define BOTTOM_VIDEO_WIDTH 176.0f
#define BOTTOM_VIDEO_HEIGHT 144.0f

#define DETECT_ON_NTH_FRAME 3

#define PAD_LABEL_SIZE 32

#define MAX_NUM_PADS 5

class VideoThread;

class DroneVideo : public QGraphicsWidget
{
    Q_OBJECT
public:
    DroneVideo();
    void reset();
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
public slots:
    void frameUpdated(const QImage &image);
    void padDetected(int num, float x, float y, float rot);
    void viewBottomCamera(bool);
    void enableVideo(bool enabled);
signals:
    void padVisible(int num);
    void videoReceived();
private:
    QHostAddress droneHost;  // Ip address of the drone
    VideoProcessor *videoThread;
    QImage *image;
    PadDetection *padDetection;
    int padX, padY, padNum;
    int videoWidth, videoHeight;
    QFont padFont;
    QPixmap pad[MAX_NUM_PADS];
public: // for testing
    bool initialized, bottomCamera, videoHasBeenReceived;
    bool videoEnabled;
};

#endif // VIDEO_H
