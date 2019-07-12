#include "App.h"
#include "Renderer.h"
#include "FFDGui.h"


FFDGui::FFDGui(QWidget *parent) : QMainWindow(parent) {
    setCentralWidget(&ffdApp().getRenderer());
}
