#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "appContext.hpp"

class Application {
  private:
    AppContext m_context;

  public:
    bool running = true;

    Application(const char *name);
    ~Application();

    void Tick();
    void Input();
    void Update();
    void Render();
};

#endif
