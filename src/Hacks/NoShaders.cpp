#include <Geode/Geode.hpp>
#include <Geode/modify/ShaderLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

class $modify (ShaderLayer)
{
    TodoReturn performCalculations()
    {
        //log::info("ShaderLayer::performCalculations");

        if (!Client::GetModuleEnabled("no-shaders"))
            ShaderLayer::performCalculations();
    }
};