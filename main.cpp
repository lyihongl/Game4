#include "inc/empire.hpp"
#include "inc/render.hpp"

#include <cstdio>
#include <cstdlib>
#include <shaders.hpp>
#include <vector>
#include <queue>
#include <windows.h>

#define GLM_FORCE_RADIANS 1
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

const int SCREEN_FULLSCREEN = 0;
const uint32_t SCREEN_WIDTH = 1280;
const uint32_t SCREEN_HEIGHT = 720;
const float VP_RATIO = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
SDL_Window *window = NULL;
SDL_GLContext maincontext;

// uint32_t frame_count = 0;

static void sdl_die(const char *message) {
    fprintf(stderr, "%s: %s\n", message, SDL_GetError());
    exit(2);
}

void init_screen(const char *caption) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) sdl_die("Couldn't initialize SDL");
    atexit(SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    // Create the window
    if (SCREEN_FULLSCREEN) {
        window = SDL_CreateWindow(
            caption, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0,
            SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        window = SDL_CreateWindow(caption, SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    }
    if (window == NULL) sdl_die("Couldn't set video mode");

    maincontext = SDL_GL_CreateContext(window);
    if (maincontext == NULL) sdl_die("Failed to create OpenGL context");

    // Check OpenGL properties
    printf("OpenGL loaded\n");
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    // Use v-sync
    // SDL_GL_SetSwapInterval(1);

    // Disable depth test and face culling.
    // glShadeModel(GL_FLAT)
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_GL_SetSwapInterval(0);
    glViewport(0, 0, w, h);
    glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
}

void bfs(std::vector<std::vector<unsigned int>> &dist,
         const std::vector<std::vector<unsigned int>> &blocked, int startX,
         int startY) {

    std::vector<std::vector<unsigned int>> visited(
        dist.size(), std::vector<unsigned int>(dist[0].size(), 0));

    std::queue<std::pair<int, int>> work;
    work.push({startX, startY});
    // dist[startY][startX] = 0;
    // visited[startY][startX] = 1;

    std::vector<std::pair<int, int>> dirs = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0},
    };

    unsigned int path_length = 0;
    while (!work.empty()) {
        int n = work.size();
        for (int i = 0; i < n; i++) {
            auto [x, y] = work.front();
            work.pop();
            visited[y][x] = 1;
            dist[y][x] = path_length;
            // std::cout<<"bfs "<<x<<" : "<<y<<" : "<<path_length<<std::endl;
            for (const auto &[dx, dy] : dirs) {
                if (x + dx >= 0 && x + dx < dist[0].size() && y + dy >= 0 &&
                    y + dy < dist.size() && visited[y + dy][x + dx] == 0 &&
                    blocked[y + dy][x + dx] == 0) {
                    work.push({x + dx, y + dy});
                    // dist[y + dy][x + dx] = dist[y][x] + 1;
                    visited[y + dy][x + dx] = 1;
                }
            }
        }
        path_length++;
    }
}

int main(int argc, char **argv) {
    // std::cout<<Constants::getResource(Constants::ResourceIndex::WOOD).getName()<<std::endl;

    init_screen("OpenGL 4.3");

    SDL_Event event;
    bool quit = false;
    bool be_nice_and_dont_burn_the_cpu = true;
    Uint32 minimum_fps_delta_time = (1000 / 60);
    Uint32 last_game_step = SDL_GetTicks(); // initial value
    Uint32 wait_time = 0;

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f,
        100.0f);

    float angle = 0.0f;
    float rotationSpeed = 0.1f;

    glm::vec2 start = glm::vec2(10, 10);
    glm::vec2 end = glm::vec2(10, 40);
    unsigned long long ticks = 0;

    Empire rome{};
    Render render{SCREEN_WIDTH, SCREEN_HEIGHT};
    std::vector<Quad> quads;
    quads.push_back(Quad{50, 80, 16, 16, 0});
    quads.push_back(Quad{30, 30, 100, 30, 0});
    quads.push_back(Quad{30, 30, 30, 100, 0});
    Shader s{"./shaders/triagShader.vert", "./shaders/triagShader.frag"};

    std::vector<std::vector<unsigned int>> grid1(
        36, std::vector<unsigned int>(64, 0));

    std::vector<std::vector<unsigned int>> blocked(
        36, std::vector<unsigned int>(64, 0));

    std::vector<std::vector<std::pair<float, float>>> grid2(
        36, std::vector<std::pair<float, float>>(64, {0.0f, 0.0f}));

    int mX = 0, mY = 0;

    while (!quit) {
        Uint32 now = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                // if (rng_gen) delete rng_gen;
                quit = true;
                break;
            }
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_q) {
                    quit = true;
                    break;
                }
            }
            }
        }

        if (last_game_step + minimum_fps_delta_time < now) {
            SDL_GL_SwapWindow(window);

            Uint32 delta_time = now - last_game_step;
            // wait_time = std::min(0, minimum_fps_delta_time - delta_time);

            if (delta_time > minimum_fps_delta_time) {
                delta_time = minimum_fps_delta_time; // slow down if the
                                                     // computer is too slow
            }
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            std::cout << "fps: " << (1000.f / delta_time) << "\n";
            ticks++;
            SDL_GetMouseState(&mX, &mY);
            unsigned int gridX = mX / 20;
            unsigned int gridY = mY / 20;
            if (ticks % 20 == 0) {
                // std::cout<<gridX<<": "<<gridY<<std::endl;
                bfs(grid1, blocked, gridX, gridY);
                // for (const auto &row : grid1) {
                //     for (const unsigned int &i : row) {
                //         std::cout << i << " ";
                //         // i = 0;
                //     }
                //     std::cout << "\n";
                // }
                // std::cout << std::endl;
            }
            // rome.simulate(ticks);
            // for (Quad &q : quads) {
            //     q.rad += 0.005;
            // }
            // render.renderQuad(quads, s);

            // RenderGame();

            last_game_step = now;
        } else {
            // we're too fast, wait a bit.
            if (be_nice_and_dont_burn_the_cpu) {
                SDL_Delay(1);
            }
        }
    }
    return 0;
}