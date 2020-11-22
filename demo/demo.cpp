#include <jengine.h>

/*
    Demo program to show features of jam engine
*/

using namespace Jam;

int main(int argc, char** argv)
{
    ArchiveLoader::init(argv[0]);
    {
        Window window;
        BatchRenderer2D br(1000);
        Font8Renderer fr;
        Texture tex;
        tex.loadFromFile(DEFAULT_ASSETS.openFile(DEFAULT_ICON_PATHS[2]), GL_NEAREST);

        fr.init();

        Camera2D cam(window.getWidth(), window.getHeight(), {0,0});

        while (!window.shouldClose())
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0,0,0,1);
            br.clear();
            br.addQuad({ 0,0 }, { 100,100 }, { 1,1,1 });

            br.addQuad({ 100,0 }, { 100,100 }, {0,0}, {1,1}, { 0,0,0 }, tex);
            br.refreshBuffer();
            br.draw(cam);

            fr.start(cam);
            fr.setColor({1,0,1});
            fr.drawText("Hello world", 0,100, 32, 32);
            fr.stop();

            window.update();
        }

        fr.release();
    }
    ArchiveLoader::deinit();

    return 0;
}