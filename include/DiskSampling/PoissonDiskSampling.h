#pragma once

#include <vector>
#include <cmath>

class PoissonDiskSampling 
{
public:
	PoissonDiskSampling(int p_width, int p_height, double p_min_dist, int p_point_count);

	std::vector<std::pair<double,double>> Generate();

	struct point
	{
		point(double x_, double y_) : x(x_), y(y_) {};
		point(const point &p) : x(p.x), y(p.y) {};

		int gridIndex(double cell_size, int map_width)
		{
			int x_index = x / cell_size;
			int y_index = y / cell_size;

			return x_index + y_index * map_width;
		};

		double distance(point p)
		{
			return std::sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y));
		}

		double x, y;
	};


private:
	
	std::vector<std::vector<point*>> m_grid;
	std::vector<point> m_process;
	std::vector<std::pair<double,double>> m_sample;

	int m_width;
	int m_height;
	double m_min_dist;
	int m_point_count;
	double m_cell_size;
	int m_grid_width;
	int m_grid_height;

	point generatePointAround(point p_point);
	bool inRectangle(point p_point);
	bool inNeighbourhood(point p_point);
	std::vector<point *> getCellsAround(point p_point);
};
