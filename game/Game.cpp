#include "Game.h"

Game::Game(const Game::WindowConfigPtr &windowConfigPtr)
        : player(registry.create()), ball(registry.create())
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(windowConfigPtr->getWidth(), windowConfigPtr->getHeight(),
                                   windowConfigPtr->getName(),
                                   nullptr,
                                   nullptr);
    if (window == nullptr)
    {
        throw std::runtime_error("Cannot create glfw window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        throw std::runtime_error("Cannot initialize glad");
    }

    glViewport(0, 0, windowConfigPtr->getWidth(), windowConfigPtr->getHeight());

    glfwSetFramebufferSizeCallback(window, resizeCallback);

    registry.ctx().insert_or_assign(ShaderProgram());
    registry.ctx().insert_or_assign(KEY_BACKGROUND_COLOR, windowConfigPtr->getBackgroundColor());
}

void Game::setInputProcessor(Game::InputProcessorPtr inputProcessorPtr)
{
    registry.ctx().insert_or_assign(std::move(inputProcessorPtr));
}

void Game::loadGameConfig(const Game::GameConfigPtr &gameConfig)
{
    registry.clear<>();

    // Creating player entity
    player = registry.create();
    registry.emplace<Color>(player, gameConfig->getPlayerColor());
    registry.emplace<Rect>(player, gameConfig->getPlayerRect());
    registry.emplace<Speed>(player);
    registry.emplace<Render>(player);

    // Creating ball entity
    ball = registry.create();
    registry.emplace<Color>(ball, gameConfig->getBallColor());
    registry.emplace<Rect>(ball, gameConfig->getBallRect());
    registry.emplace<Speed>(ball, gameConfig->getBallInitialSpeed());
    registry.emplace<Render>(ball);

    // Creating walls
    auto leftWall = registry.create();
    registry.emplace<Color>(leftWall, Color{1, 0, 0, 1});
    registry.emplace<Rect>(leftWall, -1, -1, 0.01, 2);
    registry.emplace<Render>(leftWall);

    auto upWall = registry.create();
    registry.emplace<Color>(upWall, Color{1, 0, 0, 1});
    registry.emplace<Rect>(upWall, -1, 0.99, 2, 0.01);
    registry.emplace<Render>(upWall);

    auto rightWall = registry.create();
    registry.emplace<Color>(rightWall, Color{1, 0, 0, 1});
    registry.emplace<Rect>(rightWall, 0.99, -1, 0.01, 2);
    registry.emplace<Render>(rightWall);

    auto downWall = registry.create();
    registry.emplace<Color>(downWall, Color{1, 0, 0, 1});
    registry.emplace<Rect>(downWall, -1, -1, 2, 0.01);
    registry.emplace<Render>(downWall);

    auto obstacleRects = gameConfig->getObstacleRects();
    auto obstacleColors = gameConfig->getObstacleColors();

    if (obstacleColors.size() < obstacleRects.size())
    {
        Color defaultObstacleColor = {1.0f, 0.0f, 0.0f, 1.0f};
        std::vector<Color> diffVec(obstacleRects.size() - obstacleColors.size(), defaultObstacleColor);
        obstacleColors.insert(obstacleColors.end(), diffVec.begin(), diffVec.end());
    }

    for (int i = 0; i < obstacleRects.size(); ++i)
    {
        const auto &obstacleRect = obstacleRects[i];
        const auto &obstacleColor = obstacleColors[i];
        auto obstacle = registry.create();
        registry.emplace<Rect>(obstacle, obstacleRect);
        registry.emplace<Color>(obstacle, obstacleColor);
        registry.emplace<Render>(obstacle);
    }
    const auto &renderView = registry.view<Render>();
    std::vector<GLuint> VAOs(renderView.size());
    std::vector<GLuint> VBOs(renderView.size());
    std::vector<GLuint> EBOs(renderView.size());

    glGenVertexArrays(VAOs.size(), VAOs.data());
    glGenBuffers(VBOs.size(), VBOs.data());
    glGenBuffers(EBOs.size(), EBOs.data());

    std::vector<GLuint> deleteVAOs;
    std::vector<GLuint> deleteVBOs;
    std::vector<GLuint> deleteEBOs;

    for (int i = 0; i < renderView.size(); ++i)
    {
        const auto &entity = renderView[i];
        const auto &VAO = VAOs[i];
        const auto &VBO = VBOs[i];
        const auto &EBO = EBOs[i];
        bool isDynamic = registry.all_of<Speed>(entity);
        auto rect = registry.try_get<Rect>(entity);
        if (rect == nullptr)
        {
            deleteVAOs.emplace_back(VAO);
            deleteVBOs.emplace_back(VBO);
            deleteEBOs.emplace_back(EBO);
            registry.erase<Render>(entity);
            continue;
        }
        auto color = registry.try_get<Color>(entity);

        auto vertices = color == nullptr
                        ? getRectVertices(*rect, Color{0, 0, 0, 1})
                        : getRectVertices(*rect, *color);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(getRectIndices()), getRectIndices().data(),
                     isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Updating render component
        registry.patch<Render>(entity, [&](auto &render)
        {
            render.VAO = VAO;
            render.VBO = VBO;
        });

    }


    glDeleteVertexArrays(deleteVAOs.size(), deleteVAOs.data());
    glDeleteBuffers(deleteVBOs.size(), deleteVBOs.data());
    glDeleteBuffers(deleteEBOs.size(), deleteEBOs.data());

    registry.on_update<Speed>().connect<&Game::onSpeedUpdated>();
    registry.on_update<Rect>().connect<&Game::onRectUpdated>();
}

void Game::end()
{
    auto window = glfwGetCurrentContext();
    if (window == nullptr)
    {
        return;
    }
    glfwSetWindowShouldClose(window, true);
}

bool Game::isKeyPressed(Key key)
{
    auto window = glfwGetCurrentContext();
    if (window == nullptr)
    {
        return false;
    }
    auto glfwKey = getGlfwKeyFromKey(key);
    return glfwGetKey(window, glfwKey) == GLFW_PRESS;
}

void Game::loop()
{
    auto window = glfwGetCurrentContext();
    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;

    auto backgroundColor = registry.ctx().get<Color>(KEY_BACKGROUND_COLOR);
    while (!glfwWindowShouldClose(window))
    {
        auto processorPtr = registry.ctx().find<InputProcessorPtr>();

        if (processorPtr)
        {
            processorPtr->get()->processInput(*this);
        }

        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT);


        currentFrame = glfwGetTime();
        registry.ctx().insert_or_assign<double>(KEY_DELTA_TIME, currentFrame - lastFrame);
        lastFrame = currentFrame;

        if (gameHasStarted())
        {
            doCollision();
            updateBallPosition();
        }

        auto renderEntities = registry.view<Render>();

        for (const auto &entity: renderEntities)
        {
            auto render = registry.get<Render>(entity);
            registry.ctx().get<ShaderProgram>().use();

            auto colorPtr = registry.try_get<Color>(entity);
            if (colorPtr)
            {
                registry.ctx().get<ShaderProgram>().setUniform("color",
                                                               {colorPtr->r, colorPtr->g, colorPtr->b, colorPtr->a});
            }

            glBindVertexArray(render.VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::resizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Game::movePlayerRight()
{
    if (!gameHasStarted())
    {
        return;
    }
    registry.patch<Speed>(player, [&](auto &speed)
    {
        speed.x = 1.0f;
    });
}

void Game::movePlayerLeft()
{
    if (!gameHasStarted())
    {
        return;
    }
    registry.patch<Speed>(player, [&](auto &speed)
    {
        speed.x = -1.0f;
    });
}

void Game::onRectUpdated(entt::registry &registry, entt::entity entity)
{
    if (!registry.all_of<Render>(entity))
    {
        return;
    }
    auto [rect, render] = registry.get<Rect, Render>(entity);

    auto color = registry.try_get<Color>(entity);


    auto vertices = color == nullptr ? getRectVertices(rect, Color{0, 0, 0, 1}) : getRectVertices(rect, *color);

    glBindBuffer(GL_ARRAY_BUFFER, render.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);
}

void Game::onSpeedUpdated(entt::registry &registry, entt::entity entity)
{
    const auto &speed = registry.get<Speed>(entity);
    registry.patch<Rect>(entity, [&](auto &rect)
    {
        rect.x += speed.x * registry.ctx().get<double>(KEY_DELTA_TIME);
        rect.y += speed.y * registry.ctx().get<double>(KEY_DELTA_TIME);
    });
}

void Game::updateBallPosition()
{
    registry.patch<Speed>(ball);
}

void Game::start()
{
    registry.ctx().insert_or_assign<>(KEY_GAME_STARTED, true);
}

bool Game::gameHasStarted() const
{
    return registry.ctx().contains<bool>(KEY_GAME_STARTED) && registry.ctx().get<bool>(KEY_GAME_STARTED);
}

Game::~Game()
{
    glfwTerminate();
}

void Game::doCollision()
{
    const auto &rectView = registry.view<Rect>();
    const auto &ballRect = registry.get<Rect>(ball);
    for (const auto &entity: rectView)
    {
        if (entity == ball)
        {
            continue;
        }

        const auto &otherRect = registry.get<Rect>(entity);


        if (rectCollide(ballRect, otherRect))
        {
            auto otherSpeed = registry.try_get<Speed>(entity);

            registry.patch<Speed>(ball, [&](auto &speed)
            {

                speed.x = -speed.x;
                speed.y = -speed.y;

            });
        }
    }
}
