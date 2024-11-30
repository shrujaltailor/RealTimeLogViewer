#include "LogViewer.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LogViewer viewer;
    viewer.show();
    return app.exec();
}
