#include <Bee/Bee.hpp>

void init()
{
    
}

int main(int argc, char* argv[])
{
    Bee::onInit(init);
    Bee::run();
    Bee::cleanUp();
    return 0;
}
