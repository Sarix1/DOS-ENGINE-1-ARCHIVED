struct Point2D
{
	int x, y;
};

struct Edge
{
	int top, bottom;
	int* points;
};

enum SIDE
{
	LEFT = 0,
	RIGHT = 1
};

// Direct VGA memory manipulation
void setPixel(int x, int y, int color);
void setPixelsAll(int color);
void setPixelsHorizontally(int x, int y, int len, int color);
void setPixelsVertically(int x, int y, int len, int color);
void setPixelsDiagonally(int x, int y, int len, int dir, int color);
void setPixelsSlope(int ax, int ay, int bx, int by, int color);

// Abstracted basic drawing functions
void drawPixel(int x, int y, int color);
void drawFill(int color);
void drawLine(struct Point2D* p1, struct Point2D* p2, int color);
void drawLines(struct Point2D* points[], int color);
void drawBoxFill(int x, int y, int w, int h, int color);
void drawBoxFillCenter(int x, int y, int w, int h, int color);
void drawBoxFrame(int x, int y, int w, int h, int color);
void drawBoxFrameCenter(int x, int y, int w, int h, int color);
void drawCircleFrame(int x, int y, int diameter, int color);
void drawCircleFill(int x, int y, int diameter, int color);
void drawCircleThick(int x, int y, int diameter, int thickness, int color);

// Triangles and polygons
void sortPair(struct Point2D* p1, struct Point2D* p2);
int orient2D(struct Point2D* p1, struct Point2D* p2, struct Point2D* p3);
void makeSlope(struct Edge* slope, struct Point2D* p1, struct Point2D* p2, int y_offset);
void drawTriangleFill(struct Point2D p1, struct Point2D p2, struct Point2D p3, int color);
void drawPolygonFrame(struct Point2D* points[], int color);
void drawPolygonFill(struct Point2D* points[], int color);