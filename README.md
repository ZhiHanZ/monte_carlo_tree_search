# monte_carlo_tree_search
A simple implementation on monte_carlo_tree_search based agent
## Objective
Building an AI agent which is responsible to planning a farm.
**time interval**: from 0 to 91
## goal
maximize total outcome produced by farm in 91 days
## simulator requirements(farm environment)
**size:**  n * n( n is the num of cells)
each cell can make three legal states:
1. have a corn plant
2. have a bean plant
3. empty
-----
corn and bean both needs **90** days to grom from time of planting to harvesting.
At the 90 day mark, plant can produce **10** units of basic output and cell become empty again.
**synergic effect of corn and bean:**
1. for every bean that is in one of the adjacent 8 cells to a corn plant, corn produces **1** extra unit of food.
2. a bean plant that is adjacennt to one or more corn produce 15 units of food upon harvest.
## Agent (harvest robot)
**live in black box and do not know the rule of plant interaction**
**available actions in one cell(x, y):**
1. plant a bean
2. plant a corn
3. harvest item

this agent can **only** get information from simulator.

# installation requirement
## cpp version
1. C++ 17
2. gtest



