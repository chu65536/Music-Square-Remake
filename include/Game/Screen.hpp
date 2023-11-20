#pragma once

#include "Game/Square.hpp"
#include "Game/Map.hpp"
#include "Game/Camera.hpp"


class Screen
{   
public:
    Screen(int id, Square&& square, Map&& map, Camera&& camera);
    void Update(const sf::Time& dt, float time);
    void Render(sf::RenderWindow& window);
    void SetViewport(const sf::FloatRect& viewport);
    void SetName(const std::string& name);
    void SetFont(const std::string& path);
    void CalcActiveTime(const std::vector<float>& delays);
    bool Activate(float time);
    bool Idle(float time);
    int GetID() const;
    std::string GetName() const;
private:
    void drawName(sf::RenderWindow& window);

    const int m_id;
    std::string m_name;
    Square m_square;
    Map m_map;
    Camera m_camera;
    sf::FloatRect m_viewport;
    std::vector<std::pair<float, float>> m_activeTime;
    bool m_active = false;
    sf::Font m_font;
};