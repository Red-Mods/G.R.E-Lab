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

            ImGui::Text("DeadEye Points: %f", localPlayer->m_DeadEyePoints);
            ImGui::Text("Max DeadEye Points: %f", localPlayer->m_MaxDeadEyePoints);
            ImGui::Text("Added DeadEye Points Limit: %f", localPlayer->m_AddedDeadEyePointsLimit);

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
                    /*
                    if (playerActor->m_ActorComponent->m_UnkStruct1)
                    {
                        if (playerActor->m_ActorComponent->m_UnkStruct1->m_AnimatorComponent)
                        {

                        }
                    }
                    */

                    if (playerActor->m_ActorComponent->m_UnkStruct2)
                    {
                        Vector3 position = playerActor->m_ActorComponent->m_UnkStruct2->m_Position;

                        ImGui::Separator();
                        ImGui::Text("X: %.3f | Y: %.3f | Z: %.3f", position.X, position.Y, position.Z);
                    }
                }

                if (playerActor->m_HealthComponent)
                {
                    ImGui::Separator();
                    ImGui::Checkbox("Is Drunk", &playerActor->m_HealthComponent->m_IsDrunk);
                }
            }
        }

        ImGui::PopStyleColor();

        ImGui::End();
    }
}