import java.util.ArrayList;
import java.util.List;

public class Rider //Park Visitor class
{
    private String name; // the rider's name
    private List<String> rides; // the rides they rode on

    /**
     * Creates a Rider with the specified name and initializes
     * an empty list of rides ridden on by the rider.
     * @param name Name of the rider
     */
    public Rider(String name)
    {
        this.name = name;
        this.rides = new ArrayList<String>();
    }
    
    public String getName() //Returns the name of the rider
    {
    	return name; //returns name of rider to where ever it was called from!
    }
    
    public void rememberRide(String string) //Each ride is added to the list of rides using this method.
    {
    	rides.add(name); //Adds each name of the rider to the "rides" list
    }
    
    public int getRideCount() //A count of those rides can be returned by this method. 
    {
    	return rides.size();
    }
    
    public String toString() //Returns a displayable version of the Rider containing the rider's name and number of rides they have ridden so far.
    {
    	return (getName() + "has ridden" + getRideCount() + "number of rides!");
    }

}