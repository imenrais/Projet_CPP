#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>

namespace Ui
{
class camera;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;





class camera : public QWidget
{
    Q_OBJECT
public:
    explicit camera(QWidget *parent = nullptr);
   // ~camera();
private:
    Ui::camera *ui;
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;



};

#endif // CAMERA_H
