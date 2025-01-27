#pragma once

#include <imgui-cocos.hpp>

class DrawUtils
{
    public:
        static ImVec2 addImVec2(ImVec2 arg1, ImVec2 arg2)
        {
            float x = 0, y = 0;

            x = arg1.x;
            x += arg2.x;

            y = arg1.y;
            y += arg2.y;

            return ImVec2(x, y);
        }

        static void drawRect(ImVec2 pos, ImVec2 size, ImColor colour)
        {
            #ifndef GEODE_IS_ANDROID
            ImGui::GetWindowDrawList()->AddRectFilled(pos, addImVec2(pos, size), colour);
            #endif
        }

        static void anchoredText(ImVec2 pos, ImVec2 size, std::string text, ImColor colour = ImColor(ImVec4(255, 255, 255, 255)), ImVec2 anchor = ImVec2(0.5f, 0.5f))
        {
            #ifndef GEODE_IS_ANDROID
            float s = size.x / ImGui::CalcTextSize(text.c_str()).x;
            if (s > 1)
                s = 1;
            
            ImGui::SetCursorPos(ImVec2(pos.x + ((size.x) * anchor.x) - ImGui::CalcTextSize(text.c_str()).x * anchor.x, pos.y + ((size.y) * anchor.y) - ImGui::CalcTextSize(text.c_str()).y * anchor.y));
            
            
            ImGui::TextColored(colour, text.c_str());
            #endif
        }

        /// <summary>
        /// z = width, w = height
        /// </summary>
        static bool mouseWithinRect(ImVec4 rect)
        {
            ImVec2 point = ImGui::GetIO().MousePos;

            if (point.x > rect.x && point.y > rect.y)
            {
                if (point.x < rect.x + rect.z && point.y < rect.y + rect.w)
                {
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// z = width, w = height
        /// </summary>
        static bool pointWithinRect(ImVec2 point, ImVec4 rect)
        {
            if (point.x > rect.x && point.y > rect.y)
            {
                if (point.x < rect.x + rect.z && point.y < rect.y + rect.w)
                {
                    return true;
                }
            }

            return false;
        }

        enum animType
        {
            SlideLeft,
            SlideRight,
            SlideUp,
            SlideDown,
            v6,
        };

        static inline animType animationIn = animType::v6;
        static inline animType animationOut = animType::SlideUp;
};