#include <catch.hpp>

#include "core_entity.hpp"
#include "core_scene.hpp"

using aff::core::Entity;
using aff::core::Scene;

TEST_CASE("Scene stores entities") {
  SECTION("Adding and removing entities") {
    auto dummy_entity_1 = new Entity();
    auto dummy_entity_2 = new Entity();

    Scene simple_scene;
    REQUIRE(simple_scene.entities().size() == 0);
    simple_scene.InsertEntity(dummy_entity_1);
    simple_scene.InsertEntity(dummy_entity_2);
    REQUIRE(simple_scene.entities().size() == 2);
    simple_scene.DeleteEntity(dummy_entity_2);
    simple_scene.DeleteEntity(dummy_entity_1);
    REQUIRE(simple_scene.entities().size() == 0);
    REQUIRE(dummy_entity_1 == NULL);
    REQUIRE(dummy_entity_2 == NULL);
  }
}