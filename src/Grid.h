//
//

#ifndef Grid_h
#define Grid_h

#define GRIDSIZE 200
#define CELLWIDTH 10

#include <stdio.h>
#include <array>
#include <vector>

#include "givr.h"

using namespace glm;
using namespace std;

class Cell {
  int timestamp = -1;
  vector<int> boidBucket;
  
public:
  // Addes a boid to the cell (clears the bucket if the globalTime is different to the timestamp)
  void addBoidToBucket(int index, int globalTime);
  
  // Returns all the boids within the given radius around the position in the vector boids
  void getBoids(vector<int> &boids, const int &globalTime);
};


class Grid {
  int globalTimestamp = 0;
  vector<Cell> cells;

  // checks if an index into the cells array is within bounds
  bool checkBounds(const array<int, 3> &cellIndex);
  
  vec3 gridCenter;

public:
  Grid();
  
  // adds a boid to the grid (returns false if the boid cannot be added to the grid)
  bool addBoidToGrid(int boidIndex, const vec3 &position);

  // Returns all the boids within the given radius around the position in the vector boids
  void getBoids(const vec3 &position, const float &radius, vector<int> &boids);

  // increments the global timestep
  void tick();
};

#endif /* Grid_h */
