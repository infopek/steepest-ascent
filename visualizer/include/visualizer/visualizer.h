#pragma once

#include <steepest-ascent/steepest_ascent.h>

#include <SFML/Graphics.hpp>

namespace vis
{
    class Visualizer
    {
    public:
        Visualizer(core::SteepestAscent& sa, const core::SmallestBoundaryPolygonProblem& sbpp, unsigned int windowWidth, unsigned int windowHeight);
        ~Visualizer();

        void draw();

    private:
        void drawPoints();
        void drawPolygon();

        void displayStats();

        void updatePolygon();

    private:
        core::SteepestAscent& m_sa;
        core::SmallestBoundaryPolygonProblem m_sbpp;

        unsigned int m_windowWidth{};
        unsigned int m_windowHeight{};

        sf::RenderWindow m_window;
        sf::ConvexShape m_polygon;

        sf::Font m_font;
    };
}
