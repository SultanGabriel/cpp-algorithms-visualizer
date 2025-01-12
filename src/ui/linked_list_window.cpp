#include "linked_list_window.h"
#include "../imgui.h"
#include "../linked_list.h"
#include "imgui_internal.h"
#include "linked_list_window.h"

namespace UI {

LinkedList linkedList;

void LinkedListWindow::Show(bool *open) {
  if (*open) {
    ImGui::Begin("Linked Lists", open);

    // Input to add a node
    static int valueToAdd = 0;
    // ImGui::InputInt("Value", &valueToAdd);
    ImGui::DragInt("Value", &valueToAdd);

    if (ImGui::Button("Add Node at Beginning")) {
      linkedList.InsertAtBeginning(valueToAdd);
    }

    if (ImGui::Button("Add Node at End")) {
      linkedList.InsertAtEnd(valueToAdd);
    }
    // Input to delete a node
    static int valueToDelete = 0;
    ImGui::DragInt("Delete Value", &valueToDelete);
    if (ImGui::Button("Delete Node")) {
      linkedList.DeleteValue(valueToDelete);
    }

    // Visualize the linked list
    ImDrawList *drawList = ImGui::GetWindowDrawList();
    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    ImVec2 nodePos = cursorPos;
    float nodeWidth = 50.0f;
    float nodeHeight = 30.0f;
    float spacing = 35.0f;
    float margin = 5.0f;

    auto values = linkedList.GetValues();
    for (size_t i = 0; i < values.size(); ++i) {
      // Draw node rectangle
      ImVec2 rectMin(nodePos.x, nodePos.y);
      ImVec2 rectMax(nodePos.x + nodeWidth, nodePos.y + nodeHeight);

      if (rectMin.x >
          ImGui::GetWindowPos().x + ImGui::GetWindowWidth() - nodeWidth) {
        nodePos.x = cursorPos.x;
        nodePos.y += nodeHeight + spacing;
        rectMin.x = nodePos.x;
        rectMin.y = nodePos.y;
        rectMax.x = nodePos.x + nodeWidth;
        rectMax.y = nodePos.y + nodeHeight;
      }

      drawList->AddRectFilled(rectMin, rectMax, IM_COL32(0, 128, 255, 255));
      drawList->AddRect(rectMin, rectMax, IM_COL32(255, 255, 255, 255));

      // Draw value
      ImVec2 textPos(rectMin.x + nodeWidth / 4, rectMin.y + nodeHeight / 4);
      drawList->AddText(textPos, IM_COL32(255, 255, 255, 255),
                        std::to_string(values[i]).c_str());

      // Draw connection arrow
      if (i < values.size() - 1) {
        ImVec2 arrowStart(rectMax.x + margin, rectMin.y + nodeHeight / 2);
        ImVec2 arrowEnd(rectMax.x + spacing, rectMin.y + nodeHeight / 2);
        drawList->AddLine(arrowStart, arrowEnd, IM_COL32(255, 255, 255, 255),
                          2.0f);
        drawList->AddTriangleFilled(ImVec2(arrowEnd.x - 5, arrowEnd.y - 5),
                                ImVec2(arrowEnd.x - 5, arrowEnd.y + 5),
                                ImVec2(arrowEnd.x + 5, arrowEnd.y),
                                IM_COL32(255, 255, 255, 255));
        nodePos.x += nodeWidth + spacing + margin;
      }
    }

    ImGui::End();
  }
}
} // namespace UI
