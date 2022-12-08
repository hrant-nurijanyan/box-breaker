#include "Config.h"

void BoxBreaker::Config::loadWindowConfig(entt::registry::context &ctx,
                                          const std::unique_ptr<IWindowConfig> &windowConfig)
{
    ctx.insert_or_assign<int>(Hash::KEY_WINDOW_WIDTH, windowConfig->getWidth());
    ctx.insert_or_assign<int>(Hash::KEY_WINDOW_HEIGHT, windowConfig->getHeight());
    ctx.insert_or_assign<const char *>(Hash::KEY_WINDOW_TITLE, windowConfig->getTitle());
    ctx.insert_or_assign<Graphics::Color>(Hash::KEY_WINDOW_BACKGROUND_COLOR, windowConfig->getColor());
}
