#pragma once

#include <SFML/Graphics.hpp>


class UserData {
public:
    void Update();

    sf::Vector2u windowSize{1920u, 1080u};
    sf::Vector2f position{0.f, 0.f};

    sf::Vector2f squareSize{20.f, 20.f};
    sf::Vector2f speed{250.f, 250.f};
    std::vector<float> squareColorVector {1.f, 0.f, 0.f};
    sf::Color squareColor{sf::Color::Red};
    sf::Color squareOutlineColor{sf::Color::Black};
    float squareOutlineThickness = -2.f;

    sf::Vector2f platformSize{20.f, 10.f};
    sf::Color platformColor{sf::Color::Blue};

    std::vector<float> backgroundColorVector {1.f, 1.f, 1.f};
    sf::Color backgroundColor{sf::Color::White};

    std::vector<float> wallsColorVector {0.f, 0.f, 0.f};
    sf::Color wallsColor{sf::Color::Black};


    bool debugWindow = true;

private:
    void updateColor(sf::Color& color, const std::vector<float>& vector);
};