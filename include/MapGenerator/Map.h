#pragma once

#include "dDelaunay.h"
#include "Structures.h"
#include "Quadtree.h"
#include <vector>
#include <map>

typedef QuadTree<center *> CenterPointerQT;

// Forward Declarations
class Vec2;
namespace noise
{
	namespace module
	{
		class Perlin;
	}
}

class Map
{
public:
	Map(int width, int height, double point_spread, std::string seed);

	void Generate();

	void GeneratePolygons();
	void GenerateLand();

	bool LoadFile(std::string& file_name);
	bool WriteFile(std::string& file_name);

	std::vector<edge *> GetEdges();
	std::vector<corner *> GetCorners();
	std::vector<center *> GetCenters();

	center * GetCenterAt(Vec2 p_pos);

private:
	int map_width;
	int map_height;
	double m_point_spread;
	double z_coord;
	noise::module::Perlin * noiseMap;
	std::string m_seed;
	CenterPointerQT m_centers_quadtree;

	std::vector<del::vertex> points;

	std::map<double, std::map<double, center *> > pos_cen_map;
	std::vector<edge *> edges;
	std::vector<corner *> corners;
	std::vector<center *> centers;

	static const std::vector<std::vector<Biome::Type> > elevation_moisture_matrix;
	static std::vector<std::vector<Biome::Type> > MakeBiomeMatrix();

	bool IsIsland(Vec2 position);
	void AssignOceanCoastLand();
	void AssignCornerElevation();
	void RedistributeElevations();
	void AssignPolygonElevations();
	void CalculateDownslopes();
	void GenerateRivers();
	void AssignCornerMoisture();
	void RedistributeMoisture();
	void AssignPolygonMoisture();
	void AssignBiomes();

	void GeneratePoints();
	void Triangulate(std::vector<del::vertex> puntos);
	void FinishInfo();
	void AddCenter(center * c);
	center * GetCenter(Vec2 position);
	void OrderPoints(std::vector<corner *> &corners);

	std::vector<corner *> GetLandCorners();
	std::vector<corner *> GetLakeCorners();
	void LloydRelaxation();
	static unsigned int HashString(std::string seed);
	std::string CreateSeed(int length);
};

