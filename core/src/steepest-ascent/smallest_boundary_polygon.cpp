#include "../stdafx.h"
#include <steepest-ascent/smallest_boundary_polygon.h>
#include <fstream>
#include <math.h>

namespace core
{
	SmallestBoundaryPolygonProblem::SmallestBoundaryPolygonProblem()
	{
	}

	SmallestBoundaryPolygonProblem::SmallestBoundaryPolygonProblem(const SearchSpace& searchSpace)
		: m_searchSpace{ searchSpace }
	{
	}

	SmallestBoundaryPolygonProblem::~SmallestBoundaryPolygonProblem()
	{
	}

	//
	// Basic IO
	//
	void SmallestBoundaryPolygonProblem::loadPointsFromFile(const std::string& fileName)
	{
		std::ifstream ftowns(fileName);
		Point point{};
		while (ftowns >> point.x >> point.y)
		{
			m_points.push_back(point);
		}
		ftowns.close();
	}

	void SmallestBoundaryPolygonProblem::savePointsToFile(const std::string& fileName, const std::vector<Point>& pointVector)
	{
		std::ofstream fpoints(fileName);
		for (Point pnt : pointVector)
		{
			fpoints << pnt.x << "\t" << pnt.y << std::endl;
		};
		fpoints.close();
	}

	//
	// Helper functions
	//
	float SmallestBoundaryPolygonProblem::distanceFromLine(Point lp1, Point lp2, Point p) const
	{
		// https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
		return ((lp2.y - lp1.y) * p.x - (lp2.x - lp1.x) * p.y + lp2.x * lp1.y - lp2.y * lp1.x) / sqrt(pow(lp2.y - lp1.y, 2) + pow(lp2.x - lp1.x, 2));
	}


	float SmallestBoundaryPolygonProblem::outerDistanceToBoundary(const std::vector<Point>& solution) const
	{
		float sum_min_distances = 0;
		for (const auto& point : m_points)
		{
			float min_dist = std::numeric_limits<float>::infinity();

			Point adjustedPoint{ .x = point.x, .y = m_searchSpace.y.max - point.y };

			for (size_t i = 0; i < solution.size(); ++i)
			{
				Point p1 = solution[i];
				Point p2 = solution[(i + 1) % solution.size()];

				p1.y = m_searchSpace.y.max - p1.y;
				p2.y = m_searchSpace.y.max - p2.y;

				float act_dist = distanceFromLine(p1, p2, adjustedPoint);
				if (act_dist < min_dist)
					min_dist = act_dist;
			}

			if (min_dist < 0)
				sum_min_distances -= min_dist;
		}

		return sum_min_distances;
	}

	float SmallestBoundaryPolygonProblem::lengthOfBoundary(const std::vector<Point>& solution) const
	{
		float sum_length = 0;

		for (unsigned int li = 0; li < solution.size() - 1; li++)
		{
			Point p1 = solution[li];
			Point p2 = solution[(li + 1) % solution.size()];
			sum_length += sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
		}
		return sum_length;
	}

	//
	// Objective functions
	//
	float SmallestBoundaryPolygonProblem::objective(const std::vector<Point>& solution) const
	{
		return lengthOfBoundary(solution);
	}

	float SmallestBoundaryPolygonProblem::constraint(const std::vector<Point>& solution) const
	{
		return -outerDistanceToBoundary(solution);
	}
}


