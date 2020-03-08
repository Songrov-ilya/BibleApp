#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTransform>
#include <QLabel>
#include <QImageReader>
#include <QMouseEvent>
#include <QScrollBar>
#include <QResizeEvent>
#include <QScreen>

#include "Bible.h"
#include "ScrollAreaMy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel *labelImageBook;
    ScrollAreaMy *scrollArea;
    QPoint lastMouseDragLocation;
    bool isDragging {false};
    double scaleFactor {1};
    Bible bible;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBoxBooks_activated(const QString &arg1);
    void on_comboBoxChapter_activated(int index);
    void on_pushButtonPrevious_clicked();
    void on_pushButtonNext_clicked();

private:
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void switchScreen();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void resizeEvent(QResizeEvent *);
    virtual void showEvent(QShowEvent *);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
