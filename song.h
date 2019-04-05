#pragma once
#include "stdint.h"
using namespace std;

  namespace music{

    enum music_genre{
      fail_case,
      Blues,
      Country,
      Electronic,
      Folk,
      HipHop,
      Jazz,
      Latin,
      Pop,
      Rock
    };

    struct Song{
      char title [64];
      char artist [32];
      char album [64];
      uint16_t track; //Used an unsigned 8-bit integer because it's unlikely that track # will exceed 255
      uint16_t year; //Used an unsigned 16-bit integer because year will obviously not exceed 65535
      music_genre genre;
    };
  };
