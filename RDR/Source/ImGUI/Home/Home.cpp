#include "pch.h"



Home::Home()
{
    m_Position = ImVec2(100.0f, 100.0f);
    m_Size = ImVec2(600.0f, 300.0f);

	m_OpenHotkey = ImGuiKey_F8;
}



void Home::OnRender()
{
    if (ImGui::Begin(APPLICATION_NAME " | Home##HomeWindow", &m_IsOpen, ImGuiWindowFlags_MenuBar))
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Debug"))
            {
                const auto& console = ImGUI::Get()->GetWindow("Console");

                if (console)
                {
                    bool isOpen = console->IsOpen();

                    if (ImGui::MenuItem("Console", nullptr, isOpen))
                    {
                        if (isOpen)
                            console->Close();
                        else
                            console->Open();
                    }
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::PushStyleColor(ImGuiCol_Text, IMGUI_COLOR_FWHITE);

        rage::sagPlayer* localPlayer = rage::sagPlayerMgr::GetLocalPlayer();

        if (localPlayer)
        {
            ImGui::Text("Player Infos");
            ImGui::Separator();

            ImGui::Text("DeadEye Points: %.2f", localPlayer->m_DeadEyePoints);
            ImGui::Text("Max DeadEye Points: %.2f", localPlayer->m_MaxDeadEyePoints);
            ImGui::Text("Added DeadEye Points Limit: %.2f", localPlayer->m_AddedDeadEyePointsLimit);

            ImGui::SliderFloat("DeadEye Timescale", &localPlayer->m_DeadEyeTimescale, 0.0f, 10.0f, "%.1f");

            if (ImGui::Button("Fill DeadEye"))
            {
                localPlayer->m_DeadEyePoints = 100.0f;
            }

            rage::sagActor* playerActor = localPlayer->GetPlayerActor();

            if (playerActor)
            {
                if (playerActor->m_ActorComponent)
                {
                    ImGui::Text("Player Actor: 0x%p", playerActor);

                    if (playerActor->m_MoverComponent)
                    {
                        Vector3 position = playerActor->m_MoverComponent->GetPosition();
                        Vector3 rotation = playerActor->m_MoverComponent->GetRotation();

                        ImGui::Separator();
                        ImGui::Text("[Position] X: %.3f | Y: %.3f | Z: %.3f", position.X, position.Y, position.Z);
                        ImGui::Text("[Rotation (Using reversed structs)] X: %.3f | Y: %.3f | Z: %.3f", rotation.X, rotation.Y, rotation.Z);

                        Vector3 rotation2;
                        rage::Invoke<0x27B7D6D6, bool>(rage::Invoke<0xE8CFDD53, int>(-1), &rotation2);

                        ImGui::Text("[Rotation (Using natives invoker)] X: %.3f | Y: %.3f | Z: %.3f", rotation2.X, rotation2.Y, rotation2.Z);
                    }
                }

                if (playerActor->m_HealthComponent)
                {
                    ImGui::Separator();
                    ImGui::Text("Current Health: %.2f", playerActor->m_HealthComponent->m_CurrentHealth);
                    ImGui::Text("Max Health: %.2f", playerActor->m_HealthComponent->m_MaxHitPoints);
                    ImGui::Checkbox("Is Drunk", &playerActor->m_HealthComponent->m_IsDrunk);
                }
            }
        }

        ImGui::PopStyleColor();

        ImGui::End();
    }
}