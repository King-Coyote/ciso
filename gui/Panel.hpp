#pragma once

#include "GuiObject.hpp"
#include "ResourceManager.hpp"

namespace ci {

class Panel : public GuiObject {
public:
    Panel(
        mun::Table&,
        StyleMap&
    );

    sf::Vector2f getGlobalPos() override;
    sf::Vector2f getLocalPos() override;
private:
    void renderDrawables(float dt, sf::RenderTarget& window) override;
    void updateDrawables(float dt) override;
    void setDrawablesPosition(const sf::Vector2f& position) override;
    void applyStyle(const GuiStyle& style) override;
};

}
