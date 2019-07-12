#include <QApplication>

#include "App.h"

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    App s_app;
    ffdApp().init();
    return app.exec();
}
