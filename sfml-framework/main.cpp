#include <SFML/Graphics.hpp>
#include "Framework/Framework.h"


int main()
{
    Framework framework(1280, 720);
    framework.Init(1280,720);
    framework.Do();

    return 0;
}