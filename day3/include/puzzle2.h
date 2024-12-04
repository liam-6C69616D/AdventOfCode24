#ifndef PUZZLE2
#define PUZZLE2
#include <stdbool.h>
#include "puzzle1.h"
#include <stddef.h>

bool enabled(Match* doMatches, size_t doMatchesCount, Match* dontMatches, size_t dontMatchesCount, int position);
#endif