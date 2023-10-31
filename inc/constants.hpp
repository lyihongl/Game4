#pragma once

#include "resource.hpp"

#include <array>

namespace Constants {
enum class ResourceIndex : string { WOOD = "wood", FOOD = "food" };
const std::array<Resource, 2> ResourcesMetadata = {
    Resource{"wood"},
    Resource{"food"},
};

const Resource &getResource(ResourceIndex i) {
  ResourceIndex::WOOD;
  return ResourcesMetadata[static_cast<int>(i)];
}
}; // namespace Constants