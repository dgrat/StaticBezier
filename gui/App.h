#pragma once

class App;
class Renderer;
class FFDGui;

//! Accessor to the App singleton
App &ffdApp();

class App {
public:
    App();
    ~App();
    
    bool init();
    
    FFDGui &getGui();
    Renderer &getRenderer();
    
private:
    struct Impl;
    Impl * const d;
};
