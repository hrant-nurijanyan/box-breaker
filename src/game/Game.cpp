#include "Game.h"

BoxBreaker::ShaderProgram::ShaderProgram(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    vShaderFile.close();
    fShaderFile.close();
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;

    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void BoxBreaker::ShaderProgram::use() const {
    glUseProgram(id);
}

BoxBreaker::ShaderProgram::ShaderProgram() : ShaderProgram(defaultVertexPath, defaultFragmentPath) {

}

void BoxBreaker::ShaderProgram::setUniform(const char *name, const std::array<float, 4> &value) const {
    glUniform4f(glGetUniformLocation(id, name), value[0], value[1], value[2], value[3]);
}


void BoxBreaker::Reactive::onRectCreated(entt::registry &registry, entt::entity entity) {
    auto render = registry.try_get<Component::Render>(entity);

    // If no render component is attached or attached render is already valid, do nothing
    if (render == nullptr || render->isValid()) {
        return;
    }

    createRenderComponentData(registry, entity);
}

void BoxBreaker::Reactive::onRectUpdated(entt::registry &registry, entt::entity entity) {
    if (registry.all_of<Component::Render>(entity)) {
        registry.patch<Component::Render>(entity); // Trigger patch
    }
}

void BoxBreaker::Reactive::onRectDestroyed(entt::registry &registry, entt::entity entity) {
    registry.erase<Component::Render>(entity);
}

void BoxBreaker::Reactive::onRenderCreated(entt::registry &registry, entt::entity entity) {
    auto &render = registry.get<Component::Render>(entity);

    // If already valid render component is created, do nothing
    if (render.isValid()) {
        return;
    }

    auto rect = registry.try_get<Component::Rect>(entity);
    if (rect == nullptr) {
        return;
    }

    createRenderComponentData(registry, entity);
}

void BoxBreaker::Reactive::onRenderUpdated(entt::registry &registry, entt::entity entity) {
    if (!registry.all_of<Component::Rect>(entity)) {
        return;
    }

    auto [render, rect] = registry.get<Component::Render, Component::Rect>(entity);


    auto vertices = Math::getVertices(rect);
    auto indices = Math::getIndices(rect);

    glBindBuffer(GL_ARRAY_BUFFER, render.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                 render.isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                 render.isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void BoxBreaker::Reactive::onRenderDestroyed(entt::registry &registry, entt::entity entity) {
    auto &render = registry.get<Component::Render>(entity);

    glDeleteVertexArrays(1, &render.VAO);
    glDeleteBuffers(1, &render.VBO);
    glDeleteBuffers(1, &render.EBO);

}

void BoxBreaker::Reactive::onSpeedCreated(entt::registry &registry, entt::entity entity) {
    if (registry.all_of<Component::Rect, Component::Render>(entity)) {
        registry.patch<Component::Render>(entity, [](auto &render) {
            render.isDynamic = true;
        });
    }
}

void BoxBreaker::Reactive::onSpeedUpdated(entt::registry &registry, entt::entity entity) {
    const auto &speed = registry.get<Component::Speed>(entity);
    if (registry.all_of<Component::Rect>(entity)) {

        registry.patch<Component::Rect>(entity, [&](auto &rect) {
            auto deltaTime = registry.ctx().get<double>(Hash::KEY_DELTA_TIME);
            rect.x += speed.x * deltaTime;
            rect.y += speed.y * deltaTime;
        });
    }
}

void BoxBreaker::Reactive::onSpeedDestroyed(entt::registry &registry, entt::entity entity) {
    if (registry.all_of<Component::Rect, Component::Render>(entity)) {
        registry.patch<Component::Render>(entity, [](auto &render) {
            render.isDynamic = false;
        });
    }
}

void BoxBreaker::Reactive::createRenderComponentData(entt::registry &registry, entt::entity entity) {
    if (!registry.all_of<Component::Render, Component::Rect>(entity)) {
        return;
    }

    auto [render, rect] = registry.get<Component::Render, Component::Rect>(entity);

    render.isDynamic = registry.all_of<Component::Speed>(entity);

    glGenVertexArrays(1, &render.VAO);
    glGenBuffers(1, &render.VBO);
    glGenBuffers(1, &render.EBO);

    auto vertices = Math::getVertices(rect);
    auto indices = Math::getIndices(rect);

    glBindVertexArray(render.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, render.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(),
                 render.isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                 render.isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


BoxBreaker::Game::Game() : player(entt::null), ball(entt::null) {
    registry.on_construct<BoxBreaker::Component::Rect>().connect<BoxBreaker::Reactive::onRectCreated>();
    registry.on_update<BoxBreaker::Component::Rect>().connect<BoxBreaker::Reactive::onRectUpdated>();
    registry.on_destroy<BoxBreaker::Component::Rect>().connect<BoxBreaker::Reactive::onRectDestroyed>();
    registry.on_construct<BoxBreaker::Component::Render>().connect<BoxBreaker::Reactive::onRenderCreated>();
    registry.on_update<BoxBreaker::Component::Render>().connect<BoxBreaker::Reactive::onRenderUpdated>();
    registry.on_destroy<BoxBreaker::Component::Render>().connect<BoxBreaker::Reactive::onRenderDestroyed>();
    registry.on_construct<BoxBreaker::Component::Speed>().connect<BoxBreaker::Reactive::onSpeedCreated>();
    registry.on_update<BoxBreaker::Component::Speed>().connect<BoxBreaker::Reactive::onSpeedUpdated>();
    registry.on_destroy<BoxBreaker::Component::Speed>().connect<BoxBreaker::Reactive::onSpeedDestroyed>();

}

void BoxBreaker::Game::run() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    const auto &ctx = registry.ctx();

    const auto &windowWidth = ctx.get<int>(Hash::KEY_WINDOW_WIDTH);
    const auto &windowHeight = ctx.get<int>(Hash::KEY_WINDOW_HEIGHT);

    auto window = glfwCreateWindow(windowWidth,
                                   windowHeight,
                                   ctx.get<const char *>(Hash::KEY_WINDOW_TITLE),
                                   nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Cannot create window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Cannot load glad");
    }

    glViewport(0, 0, windowWidth, windowHeight);

    glfwSetFramebufferSizeCallback(window, resizeCallback);

    registry.ctx().emplace<ShaderProgram>();

    reload();

    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);


        const auto &color = ctx.get<Graphics::Color>(Hash::KEY_WINDOW_BACKGROUND_COLOR);
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);

        currentFrame = glfwGetTime();
        registry.ctx().insert_or_assign<double>(Hash::KEY_DELTA_TIME, currentFrame - lastFrame);
        lastFrame = currentFrame;

        moveBall();
        doCollision();
        doRender();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}

void BoxBreaker::Game::movePlayer(float dist) {
    if (!registry.valid(player)) {
        return;
    }

    if (registry.all_of<Component::Speed>(player)) {
        registry.patch<Component::Speed>(player, [dist](auto &speed) {
            speed.x = dist;
        });
    }
}


void BoxBreaker::Game::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        movePlayer(-1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        movePlayer(1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        quit();
    }
}

void BoxBreaker::Game::loadWindowConfig(const std::unique_ptr<Config::IWindowConfig> &windowConfig) {
    auto &ctx = registry.ctx();
    ctx.insert_or_assign<int>(Hash::KEY_WINDOW_WIDTH, windowConfig->getWidth());
    ctx.insert_or_assign<int>(Hash::KEY_WINDOW_HEIGHT, windowConfig->getHeight());
    ctx.insert_or_assign<const char *>(Hash::KEY_WINDOW_TITLE, windowConfig->getTitle());
    ctx.insert_or_assign<Graphics::Color>(Hash::KEY_WINDOW_BACKGROUND_COLOR, windowConfig->getColor());
}

void BoxBreaker::Game::loadGameConfig(const std::unique_ptr<Config::IGameConfig> &gameConfig) {
    auto &ctx = registry.ctx();
    ctx.insert_or_assign<Math::Rect>(Hash::KEY_PLAYER_RECT, gameConfig->getPlayerRect());
    ctx.insert_or_assign<Graphics::Color>(Hash::KEY_PLAYER_COLOR, gameConfig->getPlayerColor());
    ctx.insert_or_assign<Math::Rect>(Hash::KEY_BALL_RECT, gameConfig->getBallRect());
    ctx.insert_or_assign<Graphics::Color>(Hash::KEY_BALL_COLOR, gameConfig->getBallColor());
    ctx.insert_or_assign<Math::Vector2f>(Hash::KEY_BALL_INITIAL_SPEED, gameConfig->getBallInitialSpeed());
    ctx.insert_or_assign<std::vector<Math::Rect>>(Hash::KEY_OBSTACLE_RECTS, gameConfig->getObstacleRects());
    ctx.insert_or_assign<std::vector<Graphics::Color>>(Hash::KEY_OBSTACLE_COLORS, gameConfig->getObstacleColors());
}

void BoxBreaker::Game::pause() {

}

void BoxBreaker::Game::resume() {

}

void BoxBreaker::Game::quit() {
    auto window = glfwGetCurrentContext();
    if (window == nullptr) {
        return;
    }
    glfwSetWindowShouldClose(window, true);
}

void BoxBreaker::Game::resizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool BoxBreaker::Game::isPaused() const {
    auto paused = registry.ctx().find<bool>(Hash::KEY_GAME_IS_PAUSED);
    return paused == nullptr || *paused;
}

BoxBreaker::Game::~Game() {
    glfwTerminate();
}

void BoxBreaker::Game::reload() {
    registry.clear<>();

    const auto &ctx = registry.ctx();

    player = registry.create();
    registry.emplace<Component::Rect>(player, ctx.get<Math::Rect>(Hash::KEY_PLAYER_RECT));
    registry.emplace<Component::Color>(player, ctx.get<Graphics::Color>(Hash::KEY_PLAYER_COLOR));
    registry.emplace<Component::Speed>(player);
    registry.emplace<Component::Render>(player);

    ball = registry.create();
    registry.emplace<Component::Rect>(ball, ctx.get<Math::Rect>(Hash::KEY_BALL_RECT));
    registry.emplace<Component::Color>(ball, ctx.get<Graphics::Color>(Hash::KEY_BALL_COLOR));
    registry.emplace<Component::Speed>(ball, ctx.get<Math::Vector2f>(Hash::KEY_BALL_INITIAL_SPEED));
    registry.emplace<Component::Render>(ball);



    // Creating walls
    auto leftWall = registry.create();
    registry.emplace<Component::Color>(leftWall, Component::Color{1, 0, 0, 1});
    registry.emplace<Component::Rect>(leftWall, -1, -1, 0.01, 2);
    registry.emplace<Component::Wall>(leftWall);

    auto upWall = registry.create();
    registry.emplace<Component::Color>(upWall, Component::Color{1, 0, 0, 1});
    registry.emplace<Component::Rect>(upWall, -1, 0.99, 2, 0.01);
    registry.emplace<Component::Wall>(upWall);

    auto rightWall = registry.create();
    registry.emplace<Component::Color>(rightWall, Component::Color{1, 0, 0, 1});
    registry.emplace<Component::Rect>(rightWall, 0.99, -1, 0.01, 2);
    registry.emplace<Component::Wall>(rightWall);

    auto downWall = registry.create();
    registry.emplace<Component::Color>(downWall, Component::Color{1, 0, 0, 1});
    registry.emplace<Component::Rect>(downWall, -1, -1, 2, 0.01);
    registry.emplace<Component::Wall>(downWall);

}

void BoxBreaker::Game::doRender() {
    auto renderEntities = registry.view<Component::Render>();

    for (const auto &entity: renderEntities) {
        auto render = registry.get<Component::Render>(entity);
        registry.ctx().get<ShaderProgram>().use();

        auto colorPtr = registry.try_get<Component::Color>(entity);
        if (colorPtr) {
            registry.ctx().get<ShaderProgram>().setUniform("color",
                                                           {colorPtr->r, colorPtr->g, colorPtr->b, colorPtr->a});
        }

        glBindVertexArray(render.VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void BoxBreaker::Game::doCollision() {
    if (!registry.valid(player) || !registry.valid(ball)) {
        return;
    }

    if (!registry.all_of<Component::Rect>(player) || !registry.all_of<Component::Rect>(ball)) {
        return;
    }

    auto playerRect = registry.get<Component::Rect>(player);
    auto ballRect = registry.get<Component::Rect>(ball);


    auto walls = registry.view<Component::Wall, Component::Rect>();

    for (const auto &wall: walls) {
        const auto &wallRect = registry.get<Component::Rect>(wall);
        if (Math::rectCollide(playerRect, wallRect)) {
            registry.patch<Component::Speed>(player, [](auto &speed) {
                speed.x = -speed.x;
                speed.y = -speed.y;
            });
        }
        if (Math::rectCollide(ballRect, wallRect)) {
            registry.patch<Component::Speed>(ball, [](auto &speed) {
               speed.x *= -1;
               speed.y *= -1;
            });
        }
    }


}

void BoxBreaker::Game::moveBall() {
    if (registry.valid(ball) && registry.all_of<Component::Speed>(ball)) {
        registry.patch<Component::Speed>(ball);
    }

}

