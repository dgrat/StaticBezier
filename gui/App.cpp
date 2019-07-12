#include "App.h"
#include "FFDGui.h"
#include "Renderer.h"

#include <memory>
#include <functional>

namespace {
	App *s_app = nullptr;
}

App& ffdApp() {
	// using this functions while pointer is NULL
	// probably indicates a mistake
	assert(s_app != nullptr);
	return *s_app;
}

struct App::Impl {
    std::unique_ptr<FFDGui> mainWindow;
    std::unique_ptr<Renderer> renderWidget;
};

FFDGui& App::getGui() {
	if (!d->mainWindow) {
		d->mainWindow = std::unique_ptr<FFDGui>(new FFDGui);
	}
	return *d->mainWindow;
}

Renderer& App::getRenderer() {
	if (!d->renderWidget) {
		d->renderWidget = std::unique_ptr<Renderer>(new Renderer);
	}
	return *d->renderWidget;
}


App::App() : d(new Impl()) {
    s_app = this;    
}

App::~App() {
	delete d;
	s_app = nullptr;
}

bool App::init() {
    getGui().show();
    return true;
}
