#include <visualizer/visualizer.h>

#include <cmath>
#include <string>
#include <unordered_map>

namespace vis
{
    Visualizer::Visualizer(core::SteepestAscent& sa, const core::SmallestBoundaryPolygonProblem& sbpp, unsigned int windowWidth, unsigned int windowHeight)
        : m_sa{ sa },
        m_sbpp{ sbpp },
        m_windowWidth{ windowWidth },
        m_windowHeight{ windowHeight }
    {
        m_window.create(sf::VideoMode(windowWidth, windowHeight), "Steepest ascent");

        if (!m_font.loadFromFile("../../../visualizer/res/fonts/arial.ttf")) {}
    }

    Visualizer::~Visualizer()
    {
    }

    void Visualizer::draw()
    {
        while (m_window.isOpen())
        {
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    m_window.close();
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    m_sa.step();
                    updatePolygon();
                }
            }

            m_window.clear(sf::Color::White);

            drawPoints();
            drawPolygon();
            displayStats();

            m_window.display();
        }
    }

    void Visualizer::drawPoints()
    {
        const auto& points = m_sbpp.getPoints();
        for (size_t i = 0; i < points.size(); ++i)
        {
            const auto& point = points[i];

            // Draw vertex
            sf::CircleShape vertex(5.0f);
            vertex.setFillColor(sf::Color::Red);
            vertex.setOrigin(vertex.getRadius(), vertex.getRadius());
            vertex.setPosition(point.x, point.y);

            m_window.draw(vertex);
        }
    }

    void Visualizer::drawPolygon()
    {
        m_polygon.setFillColor(sf::Color::Transparent);
        m_polygon.setOutlineColor(sf::Color::Black);
        m_polygon.setOutlineThickness(1.0f);

        for (size_t i = 0; i < m_polygon.getPointCount(); ++i)
        {
            sf::Text label;
            label.setFont(m_font);
            label.setString(std::to_string(i + 1));
            label.setCharacterSize(13);
            label.setFillColor(sf::Color::Black);

            float x = m_polygon.getPoint(i).x;
            float y = m_polygon.getPoint(i).y - 10.0f;
            label.setPosition(x, y);

            sf::FloatRect textRect = label.getLocalBounds();
            label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

            m_window.draw(label);
        }

        m_window.draw(m_polygon);
    }

    void Visualizer::displayStats()
    {

        std::unordered_map<std::string, std::string> texts{
            {"Iteration: ", std::to_string(m_sa.getIteration())},
            {"Fitness: ", std::to_string(static_cast<int>(m_sa.getBoundaryLength()))},
            {"Constraint: ", std::to_string(static_cast<int>(m_sa.getConstraint()))},
            {"GG: ", (m_sa.isStuck() ? "Yes" : "No")},
        };

        const float paddingRight = 150.0f;
        float offset = 0.0f;
        for (const auto& [annotation, text] : texts)
        {
            sf::Text t;
            t.setFont(m_font);
            t.setString(annotation + text);
            t.setCharacterSize(18);
            t.setFillColor(sf::Color::Black);
            t.setPosition(m_windowWidth - paddingRight, offset);

            offset += 30.0f;
            m_window.draw(t);
        }
    }

    void Visualizer::updatePolygon()
    {
        const auto& boundary = m_sa.getBoundary();

        sf::ConvexShape newPolygon{};
        newPolygon.setPointCount(boundary.size());

        for (size_t i = 0; i < boundary.size(); ++i)
        {
            sf::Vector2f vertex(boundary[i].x, boundary[i].y);
            newPolygon.setPoint(i, vertex);
        }

        m_polygon = newPolygon;
    }
}