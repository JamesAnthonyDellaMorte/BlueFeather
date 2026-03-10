#ifndef HM64_TITLE_RUNTIME_H
#define HM64_TITLE_RUNTIME_H

#include <memory>

namespace Ship {
class Context;
}

class HM64TitleRuntime {
  public:
    HM64TitleRuntime();

    bool Init(const std::shared_ptr<Ship::Context>& context);
    void Tick();
    bool IsInitialized() const;

  private:
    std::shared_ptr<Ship::Context> m_context;
    bool m_initialized;
};

#endif
