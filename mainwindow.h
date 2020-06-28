#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QImageReader>
#include <QScreen>

#include "Manager.h"

class MainWindow : public QQuickView
{
    Q_OBJECT

    Manager *manager;
public:
    MainWindow(QWindow *parent = nullptr);
    ~MainWindow();

    void setElapsed(const int elapsed);
private:
    void setGeneralSettings();
};
#endif // MAINWINDOW_H
