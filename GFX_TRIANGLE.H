struct Point2D
{
	int x, y;
};

int orient2D(struct Point2D* a, struct Point2D* b, struct Point2D* c);
void drawTriangle(struct Point2D* v0, struct Point2D* v1, struct Point2D* v2, int color);