#include "prng.h"

static unsigned int nSeed = 5323; // randome seed

void prngSrand(unsigned seed) {
  nSeed = seed;
}

unsigned int prngRand()
{
  nSeed = (8253729 * nSeed + 2396403);
  return nSeed % PRNG_MAX;
}
