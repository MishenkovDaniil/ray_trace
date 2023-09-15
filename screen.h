#ifndef SCREEN_H
#define SCREEN_H

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 800;

static const double X_START = -50;
static const double Z_START = 50;

static const double X_END = 50;
static const double Z_END = -50;

static const double DX = (X_END - X_START) / (double)WINDOW_WIDTH;
static const double DZ = (Z_END - Z_START) / (double)WINDOW_HEIGHT;

static const double SCREEN_Y = 50;

static const char *WINDOW_NAME = "ray_cast";

#endif /* SCREEN_H */