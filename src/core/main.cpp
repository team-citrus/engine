#include <thread>
#include <mutex>
#include <ctime>
#include <csetjmp>
#include "core/mem.hpp"
#include "core/mem_int.hpp"
#include "core/Main.hpp"
#include "core/scene.hpp"
#include "core/scene_int.hpp"
#include "core/workQueue.hpp"
#include "graphics/vkInit.hpp"
#include "graphics/initGL.hpp"

using namespace engine;
using namespace internals;

bool internals::usingVulkan;
int internals::frameRate;
jmp_buf internals::buf

std::thread internals::render;
std::thread internals::phys;
std::thread internals::mix;
std::thread internals::gameplay;

int main(int argc, char const **argv)
{
    // TODO: Add crash handling stuff

    // Initalize everything
    
    pool = Pool();

    // TODO: Implement settings
    // TODO: Estimate framerate

    if(usingVulkan)
        Vulkan::vkLoad();
    else
        OpenGL::loadGL();

    // TODO: Add GUI init, and splash screen stuff

    // Load default scene
    loadScene(0);

    // TODO: Write the actual loops, which will only stop if the scene reloads

    return 0;
}
