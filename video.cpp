/*==================================================================
  !
  !  mardrone application AR-Drone for MeeGo

  ! Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
  ! All rights reserved.
  !
  !  Author:Kate Alhola  kate.alhola@nokia.com
  !
  ! GNU Lesser General Public License Usage
  ! This file may be used under the terms of the GNU Lesser
  ! General Public License version 2.1 as published by the Free Software
  ! Foundation and appearing in the file LICENSE.LGPL included in the
  ! packaging of this file.  Please review the following information to
  ! ensure the GNU Lesser General Public License version 2.1 requirements
  ! will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
  !
  !
  !
  *===================================================================*/
#include "video.h"
#include <QGraphicsView>

DroneVideo::DroneVideo() : videoThread(0), image(0), videoWidth(FRONT_VIDEO_WIDTH), videoHeight(FRONT_VIDEO_HEIGHT)
{
    droneHost.setAddress("192.168.1.1");
    setPreferredSize(videoWidth,videoHeight);
    padDetection = new PadDetection(this, videoWidth, videoHeight);
    connect(padDetection, SIGNAL(padDetected(int,float,float, float)), this, SLOT(padDetected(int,float,float,float)));
    padFont = font();
    padFont.setPixelSize(PAD_LABEL_SIZE);
    videoThread = 0;
    videoEnabled = true;
    pad[0] = QPixmap(":/data/data/dt_pad1.png");
    pad[1] = QPixmap(":/data/data/dt_pad2.png");
    pad[2] = QPixmap(":/data/data/dt_pad3.png");
    pad[3] = QPixmap(":/data/data/dt_pad4.png");
    pad[4] = QPixmap(":/data/data/dt_pad5.png");
    Q_ASSERT(!pad[0].isNull());
    reset();
}

void DroneVideo::reset() {
    videoHasBeenReceived = false;
    initialized=false;
    viewBottomCamera(false);
    if (image) {
        delete image;
        image = 0;
    }
    if(videoThread) {
        delete videoThread;
        videoThread = 0;
    }
}

void DroneVideo::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!initialized) { // We need initialize QImage here because we don't know display depth before
        int depth=0;

        depth=painter->device()->depth();
        //        qDebug() << "depth=" << depth;
        /*
        if(depth==124) {
            image=new QImage(320,240, QImage::Format_RGB32);
            image->fill(0x555555);
        } else {*/
        image=new QImage(videoWidth,videoHeight, QImage::Format_RGB16);
        image->fill(0x5555);
        //}
        QPainter p(image);
        p.drawLine(0,0,image->width(),image->height());
        p.drawLine(image->width(),0,0,image->height());
        p.drawText(boundingRect(), "Waiting for video..");
        videoThread=new VideoProcessor(this);
        connect(videoThread, SIGNAL(newImageProcessed(QImage)), this, SLOT(frameUpdated(QImage)), Qt::QueuedConnection);
        viewBottomCamera(false);
        initialized=true;
        update(boundingRect());
    } else {
        if(videoEnabled) {
            QRect sourceRect;
            if(bottomCamera) {
                sourceRect.setRect(0,0,BOTTOM_VIDEO_WIDTH, BOTTOM_VIDEO_HEIGHT);
            } else {
                sourceRect.setRect(0,0,FRONT_VIDEO_WIDTH, FRONT_VIDEO_HEIGHT);
            }
            painter->drawImage(boundingRect(),*image,sourceRect);
            painter->setPen(Qt::white);
            painter->setBrush(Qt::darkGray);
            painter->setFont(padFont);
            if(padNum) {
                if(padNum > 0 && padNum < MAX_NUM_PADS+1) { // Draw the fancy pad
                    painter->drawPixmap(padX - pad[0].width()/2, padY - pad[0].height()/2, pad[padNum-1]);
                } else { // Fallback pad
                    painter->drawRect(padX-PAD_LABEL_SIZE/2, padY+PAD_LABEL_SIZE/2, PAD_LABEL_SIZE*3,-PAD_LABEL_SIZE);
                    painter->drawText(padX-PAD_LABEL_SIZE/2, padY+PAD_LABEL_SIZE/2-5, "Pad " + QString::number(padNum));
                }
            }
        }
    }
};

QRectF DroneVideo::boundingRect() const
{
    return QRectF(0.0,0.0,FRONT_VIDEO_WIDTH, FRONT_VIDEO_HEIGHT);
}

void DroneVideo::viewBottomCamera(bool bottom) {
    bottomCamera = bottom;
    videoWidth = FRONT_VIDEO_WIDTH;
    videoHeight = FRONT_VIDEO_HEIGHT;
    emit padDetected(0,0,0,0);
    if(videoThread) {
//        if(bottom) {
//            videoThread->setFrameSkip(DETECT_ON_NTH_FRAME);
//        } else {
//            videoThread->setFrameSkip(0);
//        }
    }
    /*
    if(bottom) {
        videoWidth = BOTTOM_VIDEO_WIDTH;
        videoHeight = BOTTOM_VIDEO_HEIGHT;
//        setScale((float)FRONT_VIDEO_WIDTH/(float)BOTTOM_VIDEO_WIDTH);
    } else {
        videoWidth = FRONT_VIDEO_WIDTH;
        videoHeight = FRONT_VIDEO_HEIGHT;
//        setScale(1);
        emit padDetected(0,0,0,0);
    }
    */
    if(scene() && !scene()->views().isEmpty()) {
        //        scene()->views().at(0)->fitInView(this);
        scene()->setSceneRect(0,0,videoWidth, videoHeight);
        qDebug() << Q_FUNC_INFO << videoWidth << videoHeight;
        //        scene()->views().at(0)->
        scene()->views().at(0)->fitInView(0,0,videoWidth, videoHeight);
    }
}

void DroneVideo::frameUpdated(const QImage &newimage) {
    //    static QImage convertedImage;
    if(bottomCamera) {
        //        convertedImage = videoThread->imageData()->convertToFormat(QImage::Format_RGB888);
        //        padDetection->detectPads(convertedImage.bits());

        padDetection->detectPads(newimage.bits());
    }
    *image = newimage;
    update();
    if(!videoHasBeenReceived) {
        emit videoReceived();
        videoHasBeenReceived = true;
    }
}

void DroneVideo::padDetected(int num, float x, float y, float rot) {
    padNum = num;
    padX = (FRONT_VIDEO_WIDTH/2 + x*FRONT_VIDEO_WIDTH*2.5f);
    padY = (FRONT_VIDEO_HEIGHT/2 + y*FRONT_VIDEO_HEIGHT*3.0f);
    padX *=(FRONT_VIDEO_WIDTH/BOTTOM_VIDEO_WIDTH);
    padY *= (FRONT_VIDEO_HEIGHT/BOTTOM_VIDEO_HEIGHT);
    emit padVisible(num);
}

void DroneVideo::enableVideo(bool enabled) {
    videoEnabled = enabled;
    if(!enabled && image)
        image->fill(0);
}
