enum direction
{
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
};

enum align
{
	TOP = 0,
	BOTTOM = 1
};

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
	int x_at_y[SCREEN_HEIGHT];
	int color[SCREEN_HEIGHT];
};

struct DecoratedCoverage
{
	int top, bottom;
	struct DecoratedEdge edges[2];
};

// Direct VGA memory manipulation
static void setPixel(int x, int y, int color);
static void setPixelsAll(int color);
static void setPixelsHorizontally(int x, int y, int len, int color);
static void setPixelsVertically(int x, int y, int len, int color);
static void setPixelsDiagonally(int x, int y, int len, int dir, int color);
static void setPixelsSlope(int ax, int ay, int bx, int by, int color);

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
static void plotLine(struct Edge* edge, int side, struct Point2D* p1, struct Point2D* p2);

void drawTriangleFill(struct Point2D p1, struct Point2D p2, struct Point2D p3, int color);
void drawPolyFlatFrame(struct Point2D* points[], int color);
void drawPolyFlatFill(struct Point2D* points[], int color);