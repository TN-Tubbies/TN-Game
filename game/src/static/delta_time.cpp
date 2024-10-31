#include "delta_time.hpp"

static Uint64 DeltaTime = 0;

void InitDeltaTime(Uint64 delta) { DeltaTime = delta; }
void SetDeltaTime(Uint64 delta) { DeltaTime = delta; }
Uint64 GetDeltaTime() { return DeltaTime; }