#include "Config.h"

void BoxBreaker::Config::loadWindowConfig(entt::registry::context &ctx,
                                          const std::unique_ptr<IWindowConfig> &windowConfig)
{
    ctx.insert_or_assign<int>(Hash::KEY_WINDOW_WIDTH, windowConfig->getWidth());
    ctx.insert_or_assign<int>(Hash::KEY_WINDOW_HEIGHT, windowConfig->getHeight());
    ctx.insert_or_assign<const char *>(Hash::KEY_WINDOW_TITLE, windowConfig->getTitle());
    ctx.insert_or_assign<Graphics::Color>(Hash::KEY_WINDOW_BACKGROUND_COLOR, windowConfig->getColor());
}

void BoxBreaker::Config::loadGLConfig(entt::registry::context &ctx, const std::unique_ptr<IGLConfig> &glConfig)
{
    ctx.insert_or_assign<int>(Hash::KEY_GL_VERSION_MAJOR, glConfig->getVersionMajor());
    ctx.insert_or_assign<int>(Hash::KEY_GL_VERSION_MINOR, glConfig->getVersionMinor());
    ctx.insert_or_assign<int>(Hash::KEY_GL_PROFILE, glConfig->getProfile());
}
