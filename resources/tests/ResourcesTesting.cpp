#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ResourceManager.hpp"
#include "SFML/Graphics.hpp"
#include <memory>

using namespace std;
using namespace ci;

#define TEST_TEXTURE "tileatlas.png"
#define TEST_FONT "DejaVuSans.ttf"

SCENARIO("Resources are loaded correctly", "[resources]") {

    GIVEN("A resource manager object") {

        auto resourceManager = make_unique<ResourceManager>();

        WHEN("An invalid filename is given") {
            THEN("The manager throws an exception") {
                CHECK_THROWS(resourceManager->getResource<sf::Texture>("nothing_here_adsbvcjewbvjwbvk"));
            }
        }
            
        WHEN("A resource is requested of the wrong type") {

            THEN("The manager throws an exception") {
                CHECK_THROWS(resourceManager->getResource<sf::Font>(TEST_TEXTURE));
            }

        }

        WHEN("A correctly typed and filenamed texture resource is requested") {
            auto resource = resourceManager->getResource<sf::Texture>(TEST_TEXTURE);

            THEN("The resource pointer is valid") {
                CHECK(resource != nullptr);
            }
        }

        WHEN("A font resource is requested correctly") {
            auto resource = resourceManager->getResource<sf::Font>(TEST_FONT);

            THEN("The font resource pointer is valid") {
                CHECK(resource != nullptr);
            }
        }

    }

}