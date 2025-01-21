// menu.cpp
#include "menu.h"
#include "imgui.h"

namespace UI {
    void RenderMenu() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ImGui::MenuItem("Open", "Ctrl+O");
                ImGui::MenuItem("Save", "Ctrl+S");
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }
}

