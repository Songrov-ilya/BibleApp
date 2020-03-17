#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSize sizeScreen = QGuiApplication::primaryScreen()->availableSize() * 3 / 5;
    resize(sizeScreen);

    labelImageBook = new QLabel;
    labelImageBook->setBackgroundRole(QPalette::Base);
    labelImageBook->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    labelImageBook->setScaledContents(true);

    scrollArea = new ScrollAreaMy;
    scrollArea->setParent(ui->frame);
    scrollArea->resize(sizeScreen / 3);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(labelImageBook);
    scrollArea->setVisible(true);

    connect(scrollArea, &ScrollAreaMy::doubleClick, this, &MainWindow::slotDoubleClickScrollArea);

//    skeleton.generateContent("../BibleApp/Photos/Old_Testament");
//    skeleton.generateContent("../BibleApp/Photos/New_Testament");

    ui->comboBoxBooks->insertItems(0, bible.getListAllBooks());
    on_comboBoxBooks_activated("Genesis");
    scaleImage(0.18);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBoxBooks_activated(const QString &arg1)
{
    bible.setCurrentBook(arg1);
    ui->comboBoxChapter->clear();
    ui->comboBoxChapter->insertItems(0, bible.getListNumberOfChapters());
    switchScreen();
}

void MainWindow::on_comboBoxChapter_activated(int index)
{
    if(bible.setCurrentChapter(index + 1)){
        switchScreen();
    }
}

void MainWindow::on_pushButtonPrevious_clicked()
{
    if(--bible){
        switchScreen();
        ui->comboBoxBooks->setCurrentText(bible.getCurrentBook());
        ui->comboBoxChapter->clear();
        ui->comboBoxChapter->insertItems(0, bible.getListNumberOfChapters());
    }
    ui->comboBoxChapter->setCurrentIndex(bible.getCurrentChapter() - 1);
}

void MainWindow::on_pushButtonNext_clicked()
{
    if(++bible){
        switchScreen();
        ui->comboBoxBooks->setCurrentText(bible.getCurrentBook());
        ui->comboBoxChapter->clear();
        ui->comboBoxChapter->insertItems(0, bible.getListNumberOfChapters());
    }
    ui->comboBoxChapter->setCurrentIndex(bible.getCurrentChapter() - 1);
}

void MainWindow::on_pushButtonRotate_clicked()
{
    rotateImage();
}

void MainWindow::slotDoubleClickScrollArea()
{
    static bool zoomIn = false;
    if(zoomIn){
        scaleImage(1.5);
    }
    else{
        scaleImage(0.5);
    }
    zoomIn = !zoomIn;
}

void MainWindow::scaleImage(double factor)
{
    if(!labelImageBook->pixmap()){
        return;
    }
//    Q_ASSERT(labelImageBook->pixmap());
    scaleFactor *= factor;
    labelImageBook->resize(scaleFactor * labelImageBook->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

//    zoomInAct->setEnabled(scaleFactor < 3.0);
    //    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void MainWindow::rotateImage()
{
    if(!labelImageBook->pixmap()){
        return;
    }
    labelImageBook->setPixmap(labelImageBook->pixmap()->transformed(QTransform().rotate(90)));
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::switchScreen()
{
    QPixmap pixTransform = QPixmap(bible.getCurrentPathPhoto()).transformed(QTransform().rotate(270));
    labelImageBook->setPixmap(pixTransform);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDragging = true;
        lastMouseDragLocation = event->pos();
        setCursor(Qt::CursorShape::OpenHandCursor);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDragging = false;
        lastMouseDragLocation = event->pos();
        setCursor(Qt::CursorShape::ArrowCursor);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging)
    {
        QPoint delta = event->pos() - lastMouseDragLocation;
        scrollArea->horizontalScrollBar()->setValue(scrollArea->horizontalScrollBar()->value() - delta.x());
        scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->value() - delta.y());
        lastMouseDragLocation = event->pos();
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0){
        scaleImage(1.25);
    }
    else{
        scaleImage(0.8);
    }
    qDebug() << "wheelEvent " << event->angleDelta() << endl;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    scrollArea->resize(ui->frame->size());
}

void MainWindow::showEvent(QShowEvent *)
{
    scrollArea->resize(ui->frame->size());
}


