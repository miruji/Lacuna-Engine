#include "Object.h"

LE::Object::Object(const std::string name, const float x, const float y, const float w, const float h)
	: name(name), x(x), y(y), w(w), h(h)
{
}
LE::Object::~Object()
{
}
// to opengl texture coords glTexCoord2f func
std::pair<float, float> xy_to_float2(const float x, const float y, const float w, const float h)
{
	return std::pair<float, float>(
		(x == w) ? 1.0f : ((x > 0) ? (x / w) : 0.0f),
		(y == h) ? 1.0f : ((y > 0) ? (y / h) : 0.0f)
	);
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void drawBatchedRectangles(std::vector<LE::vertex>& vertices, GLenum mode)
{
	if (vertices.empty() || vertices.size() % 4 != 0) {
		return;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, sizeof(LE::vertex), &vertices[0].x);
	glTexCoordPointer(2, GL_FLOAT, sizeof(LE::vertex), &vertices[0].u);

	glDrawArrays(mode, 0, vertices.size());

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void LE::Object::drawRect(Camera& c, Texture& t, mi tilemap)
{
	float x = this->x + c.x;
	float y = this->y + c.y;

	if (!t.name.empty())
		glColor4f(t.color[0], t.color[1], t.color[2], t.color[3]);

	glBindTexture(GL_TEXTURE_2D, t.num);

	std::vector<vertex> vertices;
	vertices.reserve(4);

	if (tilemap >= 0 && tilemap < t.tilemap.size()) {
		LE::Texture::Tile& tm = t.tilemap[tilemap];

		auto [xx1, yy1] = xy_to_float2(tm.x,      tm.y,      t.w, t.h);
		auto [xx2, yy2] = xy_to_float2(tm.x,      tm.y+tm.h, t.w, t.h);
		auto [xx3, yy3] = xy_to_float2(tm.x+tm.w, tm.y+tm.h, t.w, t.h);
		auto [xx4, yy4] = xy_to_float2(tm.x+tm.w, tm.y,      t.w, t.h);

		if (tm.degree == 0 || tm.degree == 360 || tm.degree == -360)
		{
			vertices.push_back({  x,      y,    xx1, yy1 });
			vertices.push_back({  x,     (y+h), xx2, yy2 });
			vertices.push_back({ (x+w),  (y+h), xx3, yy3 });
			vertices.push_back({ (x+w),   y,    xx4, yy4 });
		}
		else if (tm.degree == 90 || tm.degree == -270)
		{
			vertices.push_back({  x,     y,    xx2, yy2 });
			vertices.push_back({  x,    (y+h), xx3, yy3 });
			vertices.push_back({ (x+w), (y+h), xx4, yy4 });
			vertices.push_back({ (x+w),  y,    xx1, yy1 });
		}
		else if (tm.degree == 180 || tm.degree == -180)
		{
			vertices.push_back({  x,     y,    xx3, yy3 });
			vertices.push_back({  x,    (y+h), xx4, yy4 });
			vertices.push_back({ (x+w), (y+h), xx1, yy1 });
			vertices.push_back({ (x+w),  y,    xx2, yy2 });
		}
		else if (tm.degree == 270 || tm.degree == -90)
		{
			vertices.push_back({  x,     y,    xx4, yy4 });
			vertices.push_back({  x,    (y+h), xx1, yy1 });
			vertices.push_back({ (x+w), (y+h), xx2, yy2 });
			vertices.push_back({ (x+w) , y,    xx3, yy3 });
		}
	}
	else {
		vertices.push_back({  x,      y,    0, 0 });
		vertices.push_back({  x,     (y+h), 0, 1 });
		vertices.push_back({ (x+w),  (y+h), 1, 1 });
		vertices.push_back({ (x+w),   y,    1, 0 });
	}

	drawBatchedRectangles(vertices, GL_POLYGON);
}

/*
void LE::Object::drawRect(Camera& c, Texture& t, mi tilemap)
{
	float x = this->x+(c.x);
	float y = this->y+(c.y);

	glEnable(GL_TEXTURE_2D);
		// draw
		if (!t.name.empty())
		glColor4f(t.color[0], t.color[1], t.color[2], t.color[3]);
		glBindTexture(GL_TEXTURE_2D, t.num);

		// lines
			if (tilemap >= 0) {
			if (tilemap < t.tilemap.size()) {
				LE::Texture::Tile& tm = t.tilemap[tilemap];

				if (tm.degree == 0 && (tm.degree > 360 || tm.degree < -360)) return; // fix ?

				glBegin(GL_POLYGON);

				auto [xx1, yy1] = xy_to_float2(tm.x,      tm.y,      t.w, t.h);
				auto [xx2, yy2] = xy_to_float2(tm.x,      tm.y+tm.h, t.w, t.h);
				auto [xx3, yy3] = xy_to_float2(tm.x+tm.w, tm.y+tm.h, t.w, t.h);
				auto [xx4, yy4] = xy_to_float2(tm.x+tm.w, tm.y,      t.w, t.h);

				if (tm.degree == 0 || tm.degree == 360 || tm.degree == -360)
				{
					glTexCoord2f(xx1, yy1);
					glVertex2f(xy_to_float(x,     y,     c.w, c.h));
					glTexCoord2f(xx2, yy2);
					glVertex2f(xy_to_float(x,     (y+h), c.w, c.h));
					glTexCoord2f(xx3, yy3);
					glVertex2f(xy_to_float((x+w), (y+h), c.w, c.h));
					glTexCoord2f(xx4, yy4);
					glVertex2f(xy_to_float((x+w), y,     c.w, c.h));
				}
				else if (tm.degree == 90 || tm.degree == -270)
				{
					glTexCoord2f(xx2, yy2);
					glVertex2f(xy_to_float(x,     y,     c.w, c.h));
					glTexCoord2f(xx3, yy3);
					glVertex2f(xy_to_float(x,     (y+h), c.w, c.h));
					glTexCoord2f(xx4, yy4);
					glVertex2f(xy_to_float((x+w), (y+h), c.w, c.h));
					glTexCoord2f(xx1, yy1);
					glVertex2f(xy_to_float((x+w), y,     c.w, c.h));
				}
				else if (tm.degree == 180 || tm.degree == -180)
				{
					glTexCoord2f(xx3, yy3);
					glVertex2f(xy_to_float(x,     y,     c.w, c.h));
					glTexCoord2f(xx4, yy4);
					glVertex2f(xy_to_float(x,     (y+h), c.w, c.h));
					glTexCoord2f(xx1, yy1);
					glVertex2f(xy_to_float((x+w), (y+h), c.w, c.h));
					glTexCoord2f(xx2, yy2);
					glVertex2f(xy_to_float((x+w), y,     c.w, c.h));
				}
				else if (tm.degree == 270 || tm.degree == -90)
				{
					glTexCoord2f(xx4,yy4);
					glVertex2f(xy_to_float(x,     y,     c.w, c.h));
					glTexCoord2f(xx1,yy1);
					glVertex2f(xy_to_float(x,     (y+h), c.w, c.h));
					glTexCoord2f(xx2,yy2);
					glVertex2f(xy_to_float((x+w), (y+h), c.w, c.h));
					glTexCoord2f(xx3,yy3);
					glVertex2f(xy_to_float((x+w), y,     c.w, c.h));
				}
			} }
			else
			{
				glBegin(GL_POLYGON);

				glTexCoord2f(0, 0); glVertex2f(xy_to_float(x,     y,     c.w, c.h));
				glTexCoord2f(0, 1); glVertex2f(xy_to_float(x,     (y+h), c.w, c.h));
				glTexCoord2f(1, 1); glVertex2f(xy_to_float((x+w), (y+h), c.w, c.h));
				glTexCoord2f(1, 0); glVertex2f(xy_to_float((x+w), y,     c.w, c.h));
			}
		glEnd();
	// --
	//glDisable(GL_TEXTURE_2D);
	//glPopMatrix();

	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();

	//glMatrixMode(GL_MODELVIEW);
}
*/