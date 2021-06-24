#pragma once

#include <opencv2\opencv.hpp>

/// <summary>
/// Nakresli krizek na misto zadane souradnici na dany obraz
/// </summary>
/// <param name="img">Zdrojovy obraz</param>
/// <param name="x">Souradnice X</param>
/// <param name="y">Souradnice Y</param>
/// <param name="size">Velikost krizku</param>
void drawCross(cv::Mat& img, int x, int y, int size);

/// <summary>
/// Nakresli ctverec ma misto zadane souradnici na dany obraz
/// </summary>
/// <param name="img">Zdrojovy obraz</param>
/// <param name="top_left_x">Souradnice X horniho leveho bodu ctverce</param>
/// <param name="top_left_y">Souradnice Y horniho leveho bodu ctverce</param>
/// <param name="size">Velikost ctverce</param>
void drawBox(cv::Mat& img, int top_left_x, int top_left_y, int size);

