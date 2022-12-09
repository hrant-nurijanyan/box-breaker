#ifndef BOX_BREAKER_GAME_H
#define BOX_BREAKER_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>

#include <fstream>
#include <sstream>


#include "../component/Component.hpp"
#include "../config/Config.h"

namespace BoxBreaker {
    struct ShaderProgram {
        ShaderProgram(const char *vertexPath, const char *fragmentPath);

        ShaderProgram();

        void use() const;

        void setUniform(const char *name, const std::array<float, 4> &value) const;


    private:
        static constexpr const char *defaultVertexPath = "glsl/vertex.vert";
        static constexpr const char *defaultFragmentPath = "glsl/fragment.frag";

        GLuint id;
    };

    struct Reactive {

        static void onRectCreated(entt::registry &registry, entt::entity entity);

        static void onRectUpdated(entt::registry &registry, entt::entity entity);

        static void onRectDestroyed(entt::registry &registry, entt::entity entity);

        static void onRenderCreated(entt::registry &registry, entt::entity entity);

        static void onRenderUpdated(entt::registry &registry, entt::entity entity);

        static void onRenderDestroyed(entt::registry &registry, entt::entity entity);

        static void onSpeedCreated(entt::registry &registry, entt::entity entity);

        static void onSpeedUpdated(entt::registry &registry, entt::entity entity);

        static void onSpeedDestroyed(entt::registry &registry, entt::entity entity);

    private:
        static void createRenderComponentData(entt::registry &registry, entt::entity entity);

    };

    struct Game {
        Game();

        void loadWindowConfig(const std::unique_ptr<Config::IWindowConfig> &windowConfig);

        void loadGameConfig(const std::unique_ptr<Config::IGameConfig> &gameConfig);

        void run();

        ~Game();

    private:
        bool isPaused() const;

        void reload();

        void movePlayer(float dist);

        void pause();

        void resume();

        void moveBall();

        void doCollision();

        void doRender();

        static void quit();

        static void resizeCallback(GLFWwindow *window, int width, int height);

        void processInput(GLFWwindow *window);

    private:
        entt::registry registry;
        entt::entity player;
        entt::entity ball;
    };
}


#endif //BOX_BREAKER_GAME_H
