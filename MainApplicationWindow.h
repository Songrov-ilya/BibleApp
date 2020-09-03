#pragma once

#include <QMainWindow>
#include <QQuickStyle>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QImageReader>
#include <QScreen>

#include "Manager.h"

class MainApplicationWindow : public QQmlApplicationEngine
{
    Q_OBJECT

    Manager *manager;
public:
    MainApplicationWindow(QObject *parent = nullptr);
    ~MainApplicationWindow();

    void setElapsed(const int elapsed);
private:
    void setGeneralSettings();
};
