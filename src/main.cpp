#include <iostream>

#include "reactive/Reactive.h"
#include "config/Default.h"


int main()
{
    entt::registry registry;

    registry.on_construct<BoxBreaker::Component::Rect>().connect<BoxBreaker::Reactive::onRectCreated>();
    registry.on_update<BoxBreaker::Component::Rect>().connect<BoxBreaker::Reactive::onRectUpdated>();
    registry.on_destroy<BoxBreaker::Component::Rect>().connect<BoxBreaker::Reactive::onRectDestroyed>();
    registry.on_construct<BoxBreaker::Component::Render>().connect<BoxBreaker::Reactive::onRenderCreated>();
    registry.on_update<BoxBreaker::Component::Render>().connect<BoxBreaker::Reactive::onRenderUpdated>();
    registry.on_destroy<BoxBreaker::Component::Render>().connect<BoxBreaker::Reactive::onRenderDestroyed>();
    registry.on_construct<BoxBreaker::Component::Speed>().connect<BoxBreaker::Reactive::onSpeedCreated>();
    registry.on_update<BoxBreaker::Component::Speed>().connect<BoxBreaker::Reactive::onSpeedUpdated>();
    registry.on_destroy<BoxBreaker::Component::Speed>().connect<BoxBreaker::Reactive::onSpeedDestroyed>();
    BoxBreaker::Config::loadGLConfig(registry.ctx(), std::make_unique<BoxBreaker::Default::GLConfig>());
    BoxBreaker::Config::loadWindowConfig(registry.ctx(),
                                         std::make_unique<BoxBreaker::Default::WindowConfig>());
}
