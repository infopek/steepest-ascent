#pragma once

#include <common/point.h>
#include <common/search_space.h>

#include <string>
#include <vector>

namespace core
{
	class SmallestBoundaryPolygonProblem
	{
	public:
		SmallestBoundaryPolygonProblem();
		SmallestBoundaryPolygonProblem(const SearchSpace& searchSpace);
		~SmallestBoundaryPolygonProblem();

		float objective(const std::vector<Point>& solution) const;
		float constraint(const std::vector<Point>& solution) const;

		void loadPointsFromFile(const std::string& fileName);
		void savePointsToFile(const std::string& fileName, const std::vector<Point>& pointVector);

		inline const std::vector<Point>& getPoints() const { return m_points; }

	private:
		float distanceFromLine(Point lp1, Point lp2, Point p) const;
		float outerDistanceToBoundary(const std::vector<Point>& solution) const;
		float lengthOfBoundary(const std::vector<Point>& solution) const;

	private:
		SearchSpace m_searchSpace;
		std::vector<Point> m_points{};
	};
}
