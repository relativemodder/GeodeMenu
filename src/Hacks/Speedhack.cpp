#include <Geode/Geode.hpp>
#include <Geode/modify/CCScheduler.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

FMOD::ChannelGroup* masterGroup;

class $modify (CCScheduler)
{
    void update(float dt)
    {
        if (!masterGroup)
        {
            FMODAudioEngine::sharedEngine()->m_system->getMasterChannelGroup(&masterGroup);
        }

        // icon effects value
        ColourUtility::update(dt);

        if (SpeedhackTop::instance)
        {
            if (SpeedhackEnabled::instance->enabled)
            {
                float v = 1.0f;

                if (SpeedhackTop::instance->text.size() != 0 && !SpeedhackTop::instance->text.ends_with("."))
                {
                    v = std::stof(SpeedhackTop::instance->text);
                }

                if (v < 0.01f)
                    v = 0.01f;

                if (v > 99999)
                    v = 99999;

                bool m = SpeedhackMus::instance->enabled;

                if (m)
                    if (!(PlayLayer::get() || GameManager::sharedState()->getEditorLayer())) { v = 1.0f; }

                //FMOD::ChannelGroup* masterGroup;
                //0FMODAudioEngine::sharedEngine()->m_system->getMasterChannelGroup(&masterGroup);
                masterGroup->setPitch(m ? v : 1);
                
                CCScheduler::update(dt * v);
                return;
            }
        }

        masterGroup->setPitch(1);
        
        CCScheduler::update(dt);
    }
};