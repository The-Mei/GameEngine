#pragma once

#ifdef HZ_PLATFROM_WINDOWS

extern Hazel::Application *Hazel::createApplication();

int main(int argc, char **argv)
{
    Hazel::Log::init();
    auto app = Hazel::createApplication();
    app->run();
    delete app;
}

#endif