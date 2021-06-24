#pragma once

#include "mesh.h"
#include <opencv2\opencv.hpp>

mesh gen_mesh_circle(const float radius, const unsigned int num_segments);

mesh HeightMap(const cv::Mat& hmap, const unsigned int mesh_step_size);
