
public class Exercise09_09
{
	public static void main(String[] args)
	{
		RegularPolygon polygon1 = new RegularPolygon();
		RegularPolygon polygon2 = new RegularPolygon(6, 4);
		RegularPolygon polygon3 = new RegularPolygon(10, 4, 5.6, 7.8);

		System.out.println("Polygon 1 perimeter: " + polygon1.getPerimeter());
		System.out.println("Polygon 1 area: " + polygon1.getArea());

		System.out.println("Polygon 2 perimeter: " + polygon2.getPerimeter());
		System.out.println("Polygon 2 area: " + polygon2.getArea());

		System.out.println("Polygon 3 perimeter: " + polygon3.getPerimeter());
		System.out.println("Polygon 3 area: " + polygon3.getArea());
	}

}

class RegularPolygon
{
	private int n = 3;
	private double side = 1;
	private double x = 0;
	private double y = 0;

	public RegularPolygon()
	{

	}

	public RegularPolygon(int n, double side)
	{
		this.n = n;
		this.side = side;
		x = 0;
		y = 0;
	}

	public RegularPolygon(int n, double side, double x, double y)
	{
		this.n = n;
		this.side = side;
		this.x = x;
		this.y = y;
	}

	public int getN()
	{ // n is an int format
		return n;
	}

	public double getSide()
	{ // double format
		return side;
	}

	public double getX()
	{ // double format
		return x;
	}

	public double getY()
	{ // double format
		return y;
	}

	public double getPerimeter()
	{
		return n * side;
	}

	public double getArea()
	{
		return (n * side * side) / (4 * Math.tan(Math.PI / n));
	}

	public void setX(double x)
	{
		this.x = x;
	}

	public void setY(double y)
	{
		this.y = y;
	}
}
