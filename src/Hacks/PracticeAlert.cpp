#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

class $modify (PauseLayer)
{
    bool v = false;

    void onPracticeMode(cocos2d::CCObject* sender)
    {
        if (PlayLayer::get()->m_isPracticeMode || m_fields->v || !Client::GetModuleEnabled("conf-prac"))
        {
            PauseLayer::onPracticeMode(sender);

            return;
        }        

        geode::createQuickPopup(
            "Practice Mode",
            "Are you sure you want to\nenter <cg>practice mode</c>?",
            "Cancel", "Practice",
            [this, sender](FLAlertLayer* tis, bool btn2) {
                log::info("click practice");

                if (btn2) {
                    log::info("right btn");

                    this->m_fields->v = true;

                    this->onPracticeMode(sender);

                    this->m_fields->v = false;
                }
            }
        );
    }

    bool a = false;

    void onRestart(cocos2d::CCObject* sender)
    {
        if (m_fields->a || !Client::GetModuleEnabled("conf-res"))
        {
            PauseLayer::onRestart(sender);

            return;
        }        

        geode::createQuickPopup(
            "Restart Leevl",
            "Are you sure you want to\n<cr>restart this level</c>?",
            "Cancel", "Restart",
            [this, sender](FLAlertLayer* tis, bool btn2) {
                log::info("click restart");

                if (btn2) {
                    log::info("right btn");

                    this->m_fields->a = true;

                    this->onRestart(sender);

                    this->m_fields->a = false;
                }
            }
        );
    }
};