struct Edge
{
	int x_at_y[SCREEN_HEIGHT];
};

struct Coverage
{
	int top, bottom;
	struct Edge edges[2];
};

struct DecoratedEdge
{
	struct Edge edge;
	byte color[SCREEN_HEIGHT];
};

struct DecoratedCoverage
{
	int top, bottom;
	struct DecoratedEdge edges[2];
};

// Direct VGA memory manipulation
void setPixel				(int x, int y, byte color);
void setPixelsAll			(byte color);
void setPixelsHorizontally	(int x,	 int y,  int len, byte color);
void setPixelsVertically	(int x,	 int y,  int len, byte color);
void setPixelsDiagonally	(int x,	 int y,  int len, int dir, byte color);
void setPixelsSlope			(int ax, int ay, int bx,  int by,  byte color);

// Abstracted basic drawing functions
void drawPixel			(int x, int y, byte color);
void drawFill			(byte color);
void drawLine			(struct Point2D* p1, struct Point2D* p2, byte color);
void drawLines			(struct Point2D* points[], byte color);
void drawBoxFill		(int x, int y, int w, int h, byte color);
void drawBoxFillCenter  (int x, int y, int w, int h, byte color);
void drawBoxFrame		(int x, int y, int w, int h, byte color);
void drawBoxFrameCenter	(int x, int y, int w, int h, byte color);
void drawCircleFrame	(int x, int y, int diameter, byte color);
void drawCircleFill		(int x, int y, int diameter, byte color);
void drawCircleThick	(int x, int y, int diameter, int thickness, byte color);

// Triangle and polygon drawing functions
void plotLine			(struct Edge* edge, int align, const struct Point2D* p1, const struct Point2D* p2);
void drawTriangleFrame_P(const struct Point2D* p1, const struct Point2D* p2, const struct Point2D* p3, byte color);
void drawTriangleFill_P	(const struct Point2D* p1, const struct Point2D* p2, const struct Point2D* p3, byte color);
void drawTriangleFrame	(const struct Triangle2D* triangle);
void drawTriangleFill	(const struct Triangle2D* triangle);
void drawPolyFrame		(const struct Polygon2D* polygon);
void drawPolyFrame_P	(const struct Point2D* points[], byte color);
void drawPolyFill		(const struct Polygon2D* polygon);
void drawPolyFill_P		(const struct Point2D* points[], byte color);