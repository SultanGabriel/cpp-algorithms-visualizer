// dashboard.cpp
#include "../pch.h"
#include "dashboard.h"
#include "../imgui.h"
// #include "debug_console.h"
#include "linked_list_window.h"

namespace UI {
bool showLinkedListWindow = false;

void RenderDashboard() {
  ImGui::Begin("Dashboard");
  ImGui::Text("Welcome to the dashboard!");

  ImGui::Separator();

  // Button to open the linked list window
  if (ImGui::Button("Open Linked List Visualization")) {
    showLinkedListWindow = true;
  }

  if (ImGui::Button("Log Test Message")) {
    // DebugConsole::Instance().Log("Test message from the Dashboard");
  }

  ImGui::End();

  // Render the linked list window if the flag is set
  if (showLinkedListWindow) {
    LinkedListWindow::Show(&showLinkedListWindow);
  }
}
} // namespace UI
