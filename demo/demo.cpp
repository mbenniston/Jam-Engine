#include <jengine.h>

/*
    Demo program to show features of jam engine
*/

using namespace Jam;

int main(int argc, char** argv)
{
    AssetLoader::init(argv[0]);
    {
        Window window;
        BatchRenderer2D br(1000);

        Camera2D cam(window.getWidth(), window.getHeight(), {0,0});

        while (!window.shouldClose())
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0,0,0,1);
            br.clear();
            br.addQuad({ 0,0 }, { 100,100 }, { 1,1,1 });
            br.refreshBuffer();
            br.draw(cam);

            window.update();
        }
    }
    AssetLoader::deinit();

    return 0;
}