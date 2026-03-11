#ifndef MOONWRIGHT_BUFFERS_WRAPPER_H
#define MOONWRIGHT_BUFFERS_WRAPPER_H

/*
 * Moonwright should use the imported HM64 buffer layout as the source of truth.
 * Keeping a parallel host-only buffer map caused the real gameplay modules to
 * diverge from the imported source and blocked the full intro/game path.
 */
#include "../../../src/buffers/buffers.h"

#endif
