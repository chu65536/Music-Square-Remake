#include "imgui.h"
#include "imgui-SFML.h"
#include "States/Play.hpp"


Play::Play(GameData& gameData, const SettingsData& settingsData) :
    m_gameData(gameData),
    m_conductor(gameData.songData.music),
    m_camera(*gameData.windowPt, gameData.square, sf::Vector2f(0.f, 0.f), settingsData.windowSize) {
}

void Play::HandleEvents(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Keyboard::Key key = event.key.code;
        switch(key) {
        case sf::Keyboard::Space:
            if (m_conductor.GetStatus() != sf::SoundSource::Playing) {
                m_conductor.Play();
            }
            else {
                m_conductor.Pause();
            }
            break;
        case sf::Keyboard::S:
            m_conductor.Stop();
            break;
        case:: sf::Keyboard::Escape:
            m_exit = true;
            break;
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        float delta = event.mouseWheelScroll.delta * 0.1f;
        if (0.2f < m_camera.zoom + delta && m_camera.zoom + delta < 5.f) {
            m_camera.zoom += delta;
        }
    }
}

State::Type Play::Update(const sf::Time& dt) {
    if (m_exit) {
        m_gameData.Clear();
        return State::Type::Menu;
    }

    if (!m_gameData.map.isEnd() && m_conductor.GetStatus() == sf::SoundSource::Playing) {
        m_timer += dt.asSeconds();
        m_conductor.Normalize(m_timer);
    }
    if (m_gameData.map.isEnd()) {
        m_timer = m_gameData.map.GetNextPlatform(m_timer).GetTime();
    }
    Platform& curPlatform = m_gameData.map.GetNextPlatform(m_timer);
    m_gameData.square.Update(m_timer, curPlatform);
    m_camera.Update(dt);

    return State::Type::None;
}

void Play::Render(sf::RenderWindow& window) {
    m_gameData.map.Render(window, m_camera);
    m_gameData.square.Render(window);
}

