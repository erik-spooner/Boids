//
//

#include "Grid.h"


void Cell::addBoidToBucket(int index, int globalTime)
{
  if (timestamp != globalTime) {
    timestamp = globalTime;
    boidBucket.clear();
  }

  boidBucket.push_back(index);
}

void Cell::getBoids(vector<int> &boids, const int &globalTime)
{
  if (timestamp != globalTime)
    return;

  for (const int &boid : boidBucket)
    boids.push_back(boid);
}


Grid::Grid(int size, float width) : gridSize(size), cellWidth(width)
{
  cells.resize(gridSize * gridSize * gridSize);
  
  float center = (float)(gridSize * cellWidth) / 2.0f;
  gridCenter = vec3(center);
}


bool Grid::checkBounds(const array<int, 3> &cellIndex)
{
  for (const int &index : cellIndex)
    if (index < 0 || index > gridSize - 1)
      return false;

  return true;
}



bool Grid::addBoidToGrid(int boidIndex, const vec3 &position)
{
  array<int, 3> cellIndex;
  vec3 pos = position + gridCenter;
  
  cellIndex[0] = floor(pos.x / (float) cellWidth);
  cellIndex[1] = floor(pos.y / (float) cellWidth);
  cellIndex[2] = floor(pos.z / (float) cellWidth);

  if (!checkBounds(cellIndex))
    return false;

  cellIndex[0] *= gridSize * gridSize;
  cellIndex[1] *= gridSize;

  
  cells[cellIndex[0] + cellIndex[1] + cellIndex[2]].addBoidToBucket(boidIndex, globalTimestamp);
  return true;
}



void Grid::getBoids(const vec3 &position, const float &radius, vector<int> &boids)
{
  // Get the grid cell that the position lies in
  array<int, 3> cellIndex, index;
  vec3 pos = position + gridCenter;
  
  cellIndex[0] = floor(pos.x / (float) cellWidth);
  cellIndex[1] = floor(pos.y / (float) cellWidth);
  cellIndex[2] = floor(pos.z / (float) cellWidth);

  const int indexRadius = ceil(radius / (float) cellWidth);
  
  if (checkBounds(cellIndex))
    cells[cellIndex[0] * gridSize * gridSize + cellIndex[1] * gridSize + cellIndex[2]].getBoids(boids, globalTimestamp);
  
  for (int radius = 1; radius <= indexRadius; ++radius) {
    if (boids.size() > 15)
      return;
    
    for (int x = -radius; (x <= radius) || (x == 0); ++x) {
      int yRange = radius - abs(x);
      for (int y = -yRange; (y <= yRange) || (y == 0); ++y) {
        int z = radius - abs(x) - abs(y);
        
        index[0] = cellIndex[0] + x;
        index[1] = cellIndex[1] + y;
        index[2] = cellIndex[2] + z;
        
        if (checkBounds(index))
          cells[index[0] * gridSize * gridSize + index[1] * gridSize + index[2]].getBoids(boids, globalTimestamp);
        
        index[2] = cellIndex[2] - z;
        
        if (checkBounds(index) && z != 0)
          cells[index[0] * gridSize * gridSize + index[1] * gridSize + index[2]].getBoids(boids, globalTimestamp);
      }
    }
  }
}


void Grid::tick()
{
  globalTimestamp++;
}

