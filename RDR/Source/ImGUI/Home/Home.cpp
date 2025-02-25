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
                        ImGui::Text("[Position (MoverCmp Method)] X: %.3f | Y: %.3f | Z: %.3f", position.X, position.Y, position.Z);
                        
                        playerActor->GetGohObject()->GetPosition(&position);

                        ImGui::Text("[Position (GohObj Method)] X: %.3f | Y: %.3f | Z: %.3f", position.X, position.Y, position.Z);

                        ImGui::Separator();
                        ImGui::Text("[Heading (ActorCmp Method)] X: %.3f", playerActor->m_ActorComponent->GetHeading());

                        ImGui::Text("[Rotation (MoverCmp Method)] X: %.3f | Y: %.3f | Z: %.3f", rotation.X, rotation.Y, rotation.Z);

                        playerActor->GetGohObject()->GetRotation(&rotation);

                        rotation *= Math<float>::RadToDeg;

                        ImGui::Text("[Rotation (GohObj Method)] X: %.3f | Y: %.3f | Z: %.3f", rotation.X, rotation.Y, rotation.Z);

                        rage::Invoke<0x27B7D6D6, bool>(rage::Invoke<0xE8CFDD53, int>(-1), &rotation);

                        ImGui::Text("[Rotation (NativeInvoker Method)] X: %.3f | Y: %.3f | Z: %.3f", rotation.X, rotation.Y, rotation.Z);

                        ImGui::Separator();
                        if (ImGui::Button("Set Heading 0°"))
                        {
                            Vector3 newRotation(0.0f, 0.0f, 0.0f);

                            newRotation *= Math<float>::DegToRad;

                            playerActor->GetGohObject()->SetRotation(&newRotation);
                        }
                        if (ImGui::Button("Set Heading 90°"))
                        {
                            Vector3 newRotation(0.0f, 90.0f, 0.0f);

                            newRotation *= Math<float>::DegToRad;

                            playerActor->GetGohObject()->SetRotation(&newRotation);
                        }
                        if (ImGui::Button("Set Heading 180°"))
                        {
                            Vector3 newRotation(0.0f, 180.0f, 0.0f);

                            newRotation *= Math<float>::DegToRad;

                            playerActor->GetGohObject()->SetRotation(&newRotation);
                        }
                        if (ImGui::Button("Set Heading -90°"))
                        {
                            Vector3 newRotation(0.0f, -90.0f, 0.0f);

                            newRotation *= Math<float>::DegToRad;

                            playerActor->GetGohObject()->SetRotation(&newRotation);
                        }

                        ImGui::Separator();
                        if (ImGui::Button("Teleport To Armadillo"))
                        {
                            Vector3 newPosition(-2145.7f, 16.1f, 2611.8f);

                            playerActor->GetGohObject()->SetPosition(&newPosition, true);
                        }
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