// dashboard.cpp
#include "dashboard.h"
#include "imgui.h"
#include "linked_list_window.h"
#include "signal_visualization_window.h"
#include <stdio.h>

namespace UI {
bool showLinkedListWindow = false;
bool showSignalVisualizationWindow = false;

void RenderDashboard() {
  ImGui::Begin("Dashboard");
  ImGui::Text("Welcome to the dashboard!");

  ImGui::Separator();

  // Button to open the linked list window
  if (ImGui::Button("Open Linked List Visualization")) {
    showLinkedListWindow = true;
  }
  //
  // Button to open the signal visualization window
  if (ImGui::Button("Open Signal Visualization")) {
    showSignalVisualizationWindow = true;
  }

  if (ImGui::Button("Log Test Message")) {
    printf("Test Message\n");
  }

  ImGui::End();

  // Render the linked list window if the flag is set
  if (showLinkedListWindow) {
    LinkedListWindow::Show(&showLinkedListWindow);
  }

  // Render the signal visualization window if the flag is set
  if (showSignalVisualizationWindow) {
    SignalVisualizationWindow::Show(&showSignalVisualizationWindow);
  }
}
} // namespace UI
