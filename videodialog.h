#ifndef VIDEODIALOG_H
#define VIDEODIALOG_H

#include <QDialog>
#include <cv.h>
#include <highgui.h>
#include <jpeglib.h>
#include <queue>
#include <dc1394/dc1394.h>
#include "cycdatabuffer.h"
#include "videofilewriter.h"
#include "camerathread.h"
#include "videocompressorthread.h"
#include "event.h"
#include "eventcontainer.h"
#include "eventreader.h"

class MainWindow;

namespace Ui {
class VideoDialog;
}

class VideoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit VideoDialog(int _cameraId, MainWindow *window, QWidget *parent = 0);
    ~VideoDialog();
    volatile bool color;

    bool start(const QString eventStr);
    void stop();

public slots:
    void onDrawFrame(unsigned char* _jpegBuf);

    void onShutterChanged(int _newVal);
    void onGainChanged(int _newVal);
    void onUVChanged(int _newVal);
    void onVRChanged(int _newVal);

    void stopThreads();
    void recordVideo();

private slots:
    void getNextEvent();

private:
    bool initVideo();

    Ui::VideoDialog *ui;
    MainWindow*     window;

    cv::VideoCapture*       capCam;

    dc1394camera_t*         camera;
    dc1394_t*           dc1394Context;

    CameraThread*       	cameraThread;
    CycDataBuffer*			cycVideoBufRaw;
    CycDataBuffer*			cycVideoBufJpeg;
    VideoFileWriter*		videoFileWriter;
    VideoCompressorThread*	videoCompressorThread;

    bool        isRec, videoAvailable;

    char*		imBuf;

    // JPEG-related stuff
    struct		jpeg_decompress_struct cinfo;
    struct		jpeg_error_mgr jerr;
    JSAMPROW 	row_pointer[1];

    EventContainer* events;
    std::vector<std::string> images;

    QTimer *brightnessTmr;
    QTimer *eventTmr;
};

#endif // VIDEODIALOG_H
