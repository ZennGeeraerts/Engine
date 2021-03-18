#pragma once

#ifdef SMILEENGINE_EXPORT
// dll library uses this
#define SMILEENGINE_ENTRY __declspec(dllexport)
#else
#ifdef SMILEENGINE_IMPORT
// dll user uses this
#define SMILEENGINE_ENTRY __declspec(dllimport)
#else
// static linked uses this
#define SMILEENGINE_ENTRY
#endif
#endif
