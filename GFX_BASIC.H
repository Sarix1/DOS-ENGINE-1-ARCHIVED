struct Point2D
{
	int x, y;
};

// Direct memory manipulation
void setPixel(int x, int y, int color);
void setPixelsAll(int color);
void setPixelsHorizontally(int x, int y, int len, int color);
void setPixelsVertically(int x, int y, int len, int color);
void setPixelsDiagonally(int x, int y, int len, int dir, int color);
void setPixelsSlope(int ax, int ay, int bx, int by, int color);

// Abstracted functions
void drawPixel(int x, int y, int color);
void drawFill(int color);
void drawLine(struct Point2D* p1, struct Point2D* p2, int color);
void drawLines(struct Point2D* points[], int color);
void drawPolygon(struct Point2D* points[], int color);
void drawBoxFill(int x, int y, int w, int h, int color);
void drawBoxFillCenter(int x, int y, int w, int h, int color);
void drawBoxFrame(int x, int y, int w, int h, int color);
void drawBoxFrameCenter(int x, int y, int w, int h, int color);
void drawCircleFrame(int x, int y, int diameter, int color);
void drawCircleFill(int x, int y, int diameter, int color);
void drawCircleThick(int x, int y, int diameter, int thickness, int color);

// Triangles
int orient2D(struct Point2D* a, struct Point2D* b, struct Point2D* c);
void drawTriangleFill(struct Point2D* v0, struct Point2D* v1, struct Point2D* v2, int color);