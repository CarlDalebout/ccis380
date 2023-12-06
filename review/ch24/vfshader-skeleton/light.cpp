#include "myglm.h"
#include "light.h"

glm::vec3 light_color(1, 1, 1);
glm::vec3 light_amb(0.1, 0.1, 0.1);
glm::vec3 light_diff(0.5, 0.5, 0.5);
glm::vec3 light_spec(5, 5, 5);
glm::vec3 light_pos(1, 1, 1);
float spot_cutoff = 45.0f * 3.14f / 180.0f;
