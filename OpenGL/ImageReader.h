#pragma once
#include <string>
#include "ErrorHelper.h"
//hacking my way down town losing sanity very fast, dada dada dada
#define STB_IMAGE_IMPLEMENTATION


//
bool ReadImage(const std::string& filepath, uint32_t& textureID);
