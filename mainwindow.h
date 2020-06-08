#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QImageReader>
#include <QScreen>

#include "Provider/ProviderQml.h"
#include "Bible.h"

class MainWindow : public QQuickView
{
    Q_OBJECT

    ProviderQml providerQml;
    Bible bible;
public:
    MainWindow(QWindow *parent = nullptr);
    ~MainWindow();

private:
    void setQmlSettings();
};
#endif // MAINWINDOW_H
