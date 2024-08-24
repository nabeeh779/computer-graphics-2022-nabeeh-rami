# Assignment 1 part a

step by step:
*check that the gradient is extra than 1, or much less than -1, or among 0, 1, or between-1 and zero, in the first two cases I speak between x and y.
*test the point and the way I head down the line (left to right or right to the left), if he's proper to the left, I atilp among the 2 factors.
*test if there is a reflection case, (in mirrored image, I stated fee y or x, in step with the situation).

Code:

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{


	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	if (abs(dy) < abs(dx))
	{
		if (p1.x < p2.x)
		{
			int x1 = p1.x;
			int y1 = p1.y;
			int yi = 1;
			int e = -dx;
			if (dy < 0)
			{
				yi = -1;
				dy = -dy;
			}
			while (x1 <= p2.x)
			{
				if (e > 0)
				{
					y1 += yi;
					e -= 2 * dx;
				}
				PutPixel(x1, y1, color);
				x1 += 1;
				e += 2 * dy;

			}
		}
		else if (p1.x > p2.x)
		{
			int x2 = p2.x;
			int y2 = p2.y;
			int yi = 1;
			int e;
			dx = p1.x - p2.x;
			dy = p1.y - p2.y;
			e = -dx;

			if (dy < 0)
			{
				yi = -1;
				dy = -dy;
			}
			while (x2 <= p1.x)
			{
				if (e > 0)
				{
					y2 += yi;
					e -= 2 * dx;
				}
				PutPixel(x2, y2, color);
				x2 += 1;
				e += 2 * dy;

			}

		}
	}
	else
	{
		if (p1.y < p2.y)
		{

			int x1 = p1.x;
			int y1 = p1.y;
			int xi = 1;
			int e;
			dx = p2.x - p1.x;
			dy = p2.y - p1.y;
			e = -dy;

			if (dx < 0)
			{
				xi = -1;
				dx = -dx;
			}
			while (y1 <= p2.y)
			{
				if (e > 0)
				{
					x1 += xi;
					e -= 2 * dy;
				}
				PutPixel(x1, y1, color);
				y1 += 1;
				e += 2 * dx;

			}


		}
		else if (p1.y > p2.y)
		{
			int x2 = p2.x;
			int y2 = p2.y;
			int xi = 1;
			int e;
			dx = p1.x - p2.x;
			dy = p1.y - p2.y;
			e = -dy;

			if (dx < 0)
			{
				xi = -1;
				dx = -dx;
			}
			while (y2 <= p1.y)
			{
				if (e > 0)
				{
					x2 += xi;
					e -= 2 * dy;
				}
				PutPixel(x2, y2, color);
				y2 += 1;
				e += 2 * dx;

			}




		}

	}

}



sanity screen shot - https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/sanity.jpeg

drawing screen shot - https://github.com/HaifaGraphicsCourses/computer-graphics-2022-nabeeh-rami/blob/master/my%20own.jpeg



