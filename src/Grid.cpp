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


Grid::Grid()
{
  cells.resize(GRIDSIZE * GRIDSIZE * GRIDSIZE);
  
  float center = (float)(GRIDSIZE * CELLWIDTH) / 2.0f;
  gridCenter = vec3(center);
}


bool Grid::checkBounds(const array<int, 3> &cellIndex)
{
  for (const int &index : cellIndex)
    if (index < 0 || index > GRIDSIZE - 1)
      return false;

  return true;
}



bool Grid::addBoidToGrid(int boidIndex, const vec3 &position)
{
  array<int, 3> cellIndex;
  vec3 pos = position + gridCenter;
  
  cellIndex[0] = floor(pos.x / (float) CELLWIDTH);
  cellIndex[1] = floor(pos.y / (float) CELLWIDTH);
  cellIndex[2] = floor(pos.z / (float) CELLWIDTH);

  if (!checkBounds(cellIndex))
    return false;

  cellIndex[0] *= GRIDSIZE * GRIDSIZE;
  cellIndex[1] *= GRIDSIZE;

  
  cells[cellIndex[0] + cellIndex[1] + cellIndex[2]].addBoidToBucket(boidIndex, globalTimestamp);
  return true;
}



void Grid::getBoids(const vec3 &position, const float &radius, vector<int> &boids)
{
  // Get the grid cell that the position lies in
  array<int, 3> cellIndex, index;
  vec3 pos = position + gridCenter;
  
  cellIndex[0] = floor(pos.x / (float) CELLWIDTH);
  cellIndex[1] = floor(pos.y / (float) CELLWIDTH);
  cellIndex[2] = floor(pos.z / (float) CELLWIDTH);

  const int indexRadius = ceil(radius / (float) CELLWIDTH);
  
  for (int radius = 0; radius < indexRadius; ++radius) {
    for (int x = -radius; x < radius; ++x) {
      int yRange = radius - abs(x);
      for (int y = -yRange; y < yRange; ++y) {
        int z = radius - abs(x) - abs(y);
        
        index[0] = cellIndex[0] + x;
        index[1] = cellIndex[1] + y;
        index[2] = cellIndex[2] + z;
        
        if (checkBounds(index))
          cells[index[0] * GRIDSIZE * GRIDSIZE + index[1] * GRIDSIZE + index[2]].getBoids(boids, globalTimestamp);
        
        index[2] = cellIndex[2] - z;
        
        if (checkBounds(index))
          cells[index[0] * GRIDSIZE * GRIDSIZE + index[1] * GRIDSIZE + index[2]].getBoids(boids, globalTimestamp);

        if (boids.size() > 10)
          return;
      }
    }
    
    
  }
  

//  maxIndex[0] = cellIndex[0] + indexRadius;
//  maxIndex[1] = cellIndex[1] + indexRadius;
//  maxIndex[2] = cellIndex[2] + indexRadius;
//
//  // iterate through all the valid indices and grab the boids that lie within the cell
//  for (cellIndex[0] = minIndex[0]; cellIndex[0] < maxIndex[0]; ++cellIndex[0])
//    for (cellIndex[1] = minIndex[1]; cellIndex[1] < maxIndex[1]; ++cellIndex[1])
//      for (cellIndex[2] = minIndex[2]; cellIndex[2] < maxIndex[2]; ++cellIndex[2])
//        if (checkBounds(cellIndex))
//          cells[cellIndex[0] * GRIDSIZE * GRIDSIZE + cellIndex[1] * GRIDSIZE + cellIndex[2]].getBoids(boids, globalTimestamp);
}


void Grid::tick()
{
  globalTimestamp++;
}

