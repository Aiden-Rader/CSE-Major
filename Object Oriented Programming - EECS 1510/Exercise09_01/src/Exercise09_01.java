
public class Exercise09_01
{
	public static void main(String[] args)
	{

		Rectangle rectangle1 = new Rectangle(4, 40);
		System.out.println("The area of a rectangle with width " + rectangle1.width + " and height " + rectangle1.height
				+ " is " + rectangle1.getArea());
		System.out.println("The perimeter of a rectangle is " + rectangle1.getPerimeter());

		Rectangle rectangle2 = new Rectangle(3.5, 35.9);
		System.out.println("The area of a rectangle with width " + rectangle2.width + " and height " + rectangle2.height
				+ " is " + rectangle2.getArea());
		System.out.println("The perimeter of a rectangle is " + rectangle2.getPerimeter());
	}
}

class Rectangle
{
	double width = 1;
	double height = 1;

	public Rectangle()
	{

	}

	public Rectangle(double width, double height)
	{
		this.width = width;
		this.height = height;
	}

	public double getArea()
	{
		return width * height;
	}

	public double getPerimeter()
	{
		return 2 * (width + height);
	}
}
