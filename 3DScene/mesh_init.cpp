#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh_init.h"
#include "texture.h"

mesh gen_mesh_circle(const float radius, const unsigned int num_segments)
{
	mesh mesh;
	float theta;
	glm::vec3 vertex;

	mesh.primitive_type = GL_LINE_LOOP;

	for (unsigned int u = 0; u < num_segments; u++)
	{
		theta = 2.0f * 3.1415926f * float(u) / float(num_segments);

		vertex.x = radius * cosf(theta);
		vertex.y = radius * sinf(theta);
		vertex.z = 0.0;

		mesh.vertices.push_back(vertex);
		mesh.indices.push_back(u);
	}

	return mesh;
}

mesh HeightMap(const cv::Mat& hmap, const unsigned int mesh_step_size)
{
	const int seaLevel = 50;
	const int sandLevel = 70;
	const int rockLevel = 130;
	const int snowLevel = 200;
	int level = 0;
	mesh mesh;
	glm::vec3 vertex;
	glm::vec2 textcoord;

	if (hmap.empty())
		return mesh;

	std::cout << "Note: heightmap size:" << hmap.size << ", channels: " << hmap.channels() << std::endl;

	if (hmap.channels() != 1)
	{
		std::cerr << "WARN: requested 1 channel, got: " << hmap.channels() << std::endl;
	}

	// Create heightmap mesh from QUADS in XZ plane, Y is UP (right hand rule) 
	for (unsigned int x_coord = 0; x_coord < (hmap.cols - mesh_step_size); x_coord += mesh_step_size)
	{
		for (unsigned int z_coord = 0; z_coord < (hmap.rows - mesh_step_size); z_coord += mesh_step_size)
		{
			// Get The (X, Y, Z) Value For The Bottom Left Vertex
			vertex.x = x_coord;
			vertex.y = hmap.at<uchar>(cv::Point(x_coord, z_coord));
			vertex.z = z_coord;
			// Set The Color Value Of The Current Vertex (grayscale image returns 0..256, opengl color is 0.0f..1.0f)
			level = 0;

			if (vertex.y > seaLevel)
			{
				level = 1;
			}
			if (vertex.y > sandLevel)
			{
				level = 2;
			}
			if (vertex.y > rockLevel)
			{
				level = 3;
			}
			if (vertex.y > snowLevel)
			{
				level = 4;
			}

			switch (level)
			{
				case 0:
					textcoord = glm::vec2(0.876f, 0.8115f);
					break;
				case 1:
					textcoord = glm::vec2(0.126f, 0.124f);
					break;
				case 2:
					textcoord = glm::vec2(0.001f, 0.0615f);
					break;
				case 3:
					textcoord = glm::vec2(0.251f, 0.249f);
					break;
				case 4:
					textcoord = glm::vec2(0.126f, 0.3115f);
					break;
				default:
					break;
			}

			mesh.vertices.push_back(vertex);
			mesh.texcoords.push_back(textcoord);
			

			// Get The (X, Y, Z) Value For The Top Left Vertex
			vertex.x = x_coord;
			vertex.y = hmap.at<uchar>(cv::Point(x_coord, z_coord + mesh_step_size));
			vertex.z = z_coord + mesh_step_size;
			// Set The Color Value Of The Current Vertex

			switch (level)
			{
			case 0:
				textcoord = glm::vec2(0.876f, 0.751f);
				break;
			case 1:
				textcoord = glm::vec2(0.126f, 0.0635f);
				break;
			case 2:
				textcoord = glm::vec2(0.001f, 0.001f);
				break;
			case 3:
				textcoord = glm::vec2(0.251f, 0.1885f);
				break;
			case 4:
				textcoord = glm::vec2(0.126f, 0.251f);
				break;
			default:
				break;
			}

			mesh.vertices.push_back(vertex);
			mesh.texcoords.push_back(textcoord);

			// Get The (X, Y, Z) Value For The Top Right Vertex
			vertex.x = x_coord + mesh_step_size;
			vertex.y = hmap.at<uchar>(cv::Point(x_coord + mesh_step_size, z_coord + mesh_step_size));
			vertex.z = z_coord + mesh_step_size;
			// Set The Color Value Of The Current Vertex

			switch (level)
			{
			case 0:
				textcoord = glm::vec2(0.9365f, 0.751f);
				break;
			case 1:
				textcoord = glm::vec2(0.1865f, 0.0635f);
				break;
			case 2:
				textcoord = glm::vec2(0.0615f, 0.001f);
				break;
			case 3:
				textcoord = glm::vec2(0.3115f, 0.1885f);
				break;
			case 4:
				textcoord = glm::vec2(0.1865f, 0.249f);
				break;
			default:
				break;
			}

			mesh.vertices.push_back(vertex);
			mesh.texcoords.push_back(textcoord);

			// Get The (X, Y, Z) Value For The Bottom Right Vertex
			vertex.x = x_coord + mesh_step_size;
			vertex.y = hmap.at<uchar>(cv::Point(x_coord + mesh_step_size, z_coord));
			vertex.z = z_coord;
			// Set The Color Value Of The Current Vertex

			switch (level)
			{
			case 0:
				textcoord = glm::vec2(0.9365f, 0.8115f);
				break;
			case 1:
				textcoord = glm::vec2(0.1865f, 0.124f);
				break;
			case 2:
				textcoord = glm::vec2(0.0615f, 0.0615f);
				break;
			case 3:
				textcoord = glm::vec2(0.3115f, 0.249f);
				break;
			case 4:
				textcoord = glm::vec2(0.1865f, 0.3115f);
				break;
			default:
				break;
			}

			mesh.vertices.push_back(vertex);
			mesh.texcoords.push_back(textcoord);
		}
	}

	mesh.primitive_type = GL_QUADS;
	mesh.texture_used = true;
	return mesh;
}


