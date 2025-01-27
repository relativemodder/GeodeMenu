#include "include.h"
#include <Geode/modify/LoadingLayer.hpp>

bool showing = false;
#ifdef GEODE_IS_ANDROID
bool android = true;
#else
bool android = true;
#endif

Client* client;

#ifdef KEYBINDS

class $modify(CCKeyboardDispatcher) {
    static void onModify(auto& self) {
        self.setHookPriority("CCKeyboardDispatcher::dispatchKeyboardMSG", 1024);
    }

    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool idk)
    {     
        if (down && key == KEY_Tab) {
            if (android)
            {
                AndroidUI::addToScene();
            }
            else
            {
                showing = !showing;
                CCDirector::get()->getOpenGLView()->showCursor(true);
            }
            return true;
        }

        if (key == KEY_Escape)
        {
            if (InputModule::selected)
            {
                InputModule::selected = nullptr;
                return true;
            }
        }

        if (InputModule::selected)
        {
            if (down)
            {    
                if (key >= 48)
                {
                    if (key <= 90)
                    {
                        std::stringstream ss;

                        if (CCKeyboardDispatcher::getShiftKeyPressed())
                            ss << CCKeyboardDispatcher::keyToString(key);
                        else
                        {
                            ss << CCKeyboardDispatcher::keyToString(key);
                        }

                        if (InputModule::selected->text.length() < InputModule::selected->maxSize)
                        {
                            for (size_t i = 0; i < InputModule::selected->allowedChars.length(); i++)
                            {
                                if (InputModule::selected->allowedChars[i] == ss.str()[0])
                                {
                                    InputModule::selected->text += ss.str();
                                }
                            }
                        }

                        return true;
                    }
                }

                if (key == KEY_Backspace)
                {
                    InputModule::selected->text = InputModule::selected->text.substr(0, InputModule::selected->text.length() - 1);
                }

                if (key == 190)
                {
                    if (InputModule::selected->text.length() < InputModule::selected->maxSize)
                        {
                            for (size_t i = 0; i < InputModule::selected->allowedChars.length(); i++)
                            {
                                if (InputModule::selected->allowedChars[i] == "."[0])
                                {
                                    InputModule::selected->text += ".";
                                }
                            }
                        }
                }

                return true;
            }
        }

        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, idk);
    }
};

#endif

$on_mod(Loaded)
{
    client = new Client();
    Client::instance = client;

    ClientUtils::Setup(android);
}

#ifndef GEODE_IS_ANDROID

void DrawDescription()
{
    ImVec2 pos = ImVec2(10, ImGui::GetIO().DisplaySize.y - 10);

    if (!AltModuleLocation::instance->enabled)
    {
        pos = ImGui::GetMousePos();

        if (pos.x + ImGui::CalcTextSize(Module::descMod.c_str()).x + 20 > ImGui::GetIO().DisplaySize.x)
        {
            pos.x -= ImGui::CalcTextSize(Module::descMod.c_str()).x + 20;
        }
    }

    DrawUtils::drawRect(ImVec2(pos.x, pos.y - (ImGui::CalcTextSize(Module::descMod.c_str()).y + 20)), ImVec2(ImGui::CalcTextSize(Module::descMod.c_str()).x + 20, ImGui::CalcTextSize(Module::descMod.c_str()).y + 20), ColourUtility::GetColour(ColourUtility::ClientColour::InputField));
    DrawUtils::anchoredText(ImVec2(pos.x + 10, pos.y - 10 - (ImGui::CalcTextSize(Module::descMod.c_str()).y)), ImVec2(ImGui::CalcTextSize(Module::descMod.c_str()).x, ImGui::CalcTextSize(Module::descMod.c_str()).y), Module::descMod.c_str(), ImColor(255, 255, 255, 255), ImVec2(0, 0));
}

#endif

bool v = false;

class $modify (MenuLayer)
{
    virtual bool init()
    {
        if (!MenuLayer::init())
            return false;

        if (!v)
        {
            if (Client::GetModuleEnabled("save-pos"))
            {
                AndroidBall::position = ccp(Mod::get()->getSavedValue("posX", 32), Mod::get()->getSavedValue("posY", CCDirector::get()->getWinSize().height / 2));

                if (AndroidBall::position.x < 0)
                    AndroidBall::position.x = 0;

                if (AndroidBall::position.y < 0)
                    AndroidBall::position.y = 0;

                if (AndroidBall::position.x > CCDirector::get()->getWinSize().width)
                    AndroidBall::position.x = CCDirector::get()->getWinSize().width;

                if (AndroidBall::position.y > CCDirector::get()->getWinSize().height)
                    AndroidBall::position.y = CCDirector::get()->getWinSize().height;
            }
            else
            {
                AndroidBall::position = ccp(32, CCDirector::get()->getWinSize().height / 2);
            }
            
            #ifndef GEODE_IS_ANDROID

            ImGuiCocos::get().setup([] {
                // this runs after imgui has been setup,
                // its a callback as imgui will be re initialized when toggling fullscreen,
                // so use this to setup any themes and or fonts!

                auto* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((Mod::get()->getResourcesDir() / "verdana.ttf").string().c_str(), 32.0f);
                ImGui::GetIO().FontDefault = font;
                ImGui::GetIO().FontGlobalScale = 0.5f;

            }).draw([] {

                if (!android)
                {
                    if (client->animStatus == 0)
                    {
                        InputModule::selected = nullptr;
                    }

                    if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
                        InputModule::selected = nullptr;

                    client->animStatus += ((showing ? 1 : -1) * ImGui::GetIO().DeltaTime) / 0.25f;
                    client->animStatus = clampf(client->animStatus, 0, 1);

                    client->draw();

                    if (!showing)
                        ImGui::GetIO().WantCaptureMouse = false;

                    if (showing)
                    {
                        if (Module::descMod != "")
                            DrawDescription();
                    }

                    ImGui::End();
                }
            });

            #endif

            v = true;
        }

        return true;
    }
};