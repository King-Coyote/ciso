#pragma once

namespace ci {

enum GuiStateType {
    GUISTATE_DISABLED = 0,
    GUISTATE_ENABLED,
    GUISTATE_HOVER,
    GUISTATE_CLICKED,
    GUISTATE_UNCLICKED, // for like eg if they click but then move mouse outside
    NUM_GUI_STATES // DO NOT DELETE OR ADD ANYTHING AFTER THIS
};

class GuiState {
public:
    GuiStateType transitionMouseMove(bool mouseIsInside);
    GuiStateType transitionMousePressed(bool mouseIsInside);
    GuiStateType transitionMouseReleased(bool mouseIsInside);
    GuiStateType getState();

    GuiStateType state = GUISTATE_ENABLED;
private:
};

}