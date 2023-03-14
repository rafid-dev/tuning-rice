#ifndef CONFIG_H
#define CONFIG_H 1

#include<cstdint>
#include"./engines/rice.h"

#define TAPERED 1
using TuneEval = Rice::RiceEval;
constexpr int32_t thread_count = 6;
constexpr double preferred_k = 3;
constexpr bool retune_from_zero = true;


#endif // !CONFIG_H
