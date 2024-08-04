import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;


public class Ride //Park Rides
{
    private String name;          // Name of the ride
    private int peoplePerLoad;    // Riders per load
    private int waitTimePerLoad;  // Time to wait between loads
    private int lastLoadStarted;  // Time the last group loaded
    @SuppressWarnings("unused")
	private int riderCount;       // Riders in current load
    private int totalLoadCount;   // Number of loads of riders
    private int totalRiderCount;  // Total riders for the day

    public Queue<Rider> queue;   // Waiting line queue for the ride

    /**
     * Creates a ride using its name, number of people that fit in each load
     * on the ride, and how long each load lasts (how long to wait between rides).
     * @param name Name of the ride
     * @param peoplePerLoad People on each load of the ride
     * @param waitTimePerLoad How long the wait is between loads on the ride
     */
    public Ride(String name, int peoplePerLoad, int waitTimePerLoad)
    {
        this.name = name;
        this.peoplePerLoad = peoplePerLoad;
        this.waitTimePerLoad = waitTimePerLoad;
        this.lastLoadStarted = 0;
        this.riderCount = 0;
        this.totalLoadCount = 0;
        this.totalRiderCount = 0;
        this.queue = new LinkedList<Rider>();
    }

    /**
     * Gets the name of this ride.
     * @return Name of the ride
     */
    public String getName()
    {
        return name;
    }

    /**
     * Checks to see if the ride is available, meaning that it had a previous load
     * of riders on the ride and the ride just finished this second.
     * @param time Current clock time in the park
     * @return true if a load finished and the ride is available for more riders, false otherwise
     */
    public boolean available(int time)
    {
        return lastLoadStarted != time && (time % waitTimePerLoad == 0);
    }
  
    /**
     * Gets the current waiting time for this ride in seconds.
     * @return Seconds a rider entering the line for this ride will have to wait before riding
     */
    
    public int getWaitTime()
    {
        int peopleInLine = queue.size();
        int loads = (int)Math.ceil((double)peopleInLine / peoplePerLoad);
        int waitTime = loads * waitTimePerLoad;
        return waitTime;
    }
    
    public int getRideCount() //A count of those rides can be returned by this method. 
    {
    	return queue.size();
    }
    
    public List<Rider> exitRide() //Gets a list of riders from the load that just finished riding this ride and removes each of those riders from the queue for this ride.
    {
    	List<Rider> ridee = new ArrayList<Rider>();
    	for(int i = 0; i<riderCount; i++)
    	{
    		ridee.add(queue.remove());
    	}
    	
    	totalRiderCount += riderCount;
    	riderCount = 0;
    	return ridee;
    }
    
    public void enterLine(Rider rider) //Adds a rider to the waiting queue for this ride.
    {
    	queue.add(rider);    	
    }
    
    public int loadRide(int time) //- loads the ride by remembering the time this load started riding and the number of riders in the load. It also increments the ride's total number of loads for the day.
    {    		
    	totalLoadCount++;
    	return riderCount = Math.min(queue.size(), peoplePerLoad);    	
    }
    
    public int getTotalRiderCount() //Gets the total number of riders who rode the ride today.
    {
    	return totalRiderCount;
    }
    
    public int getTotalLoadCount() //Gets the total number of loads of riders that were on the ride today.
    {
    	return totalLoadCount;
    }
    
    public String toString() //Returns a string representing the ride, showing its name, wait time in minutes, and the number or riders waiting, including those riding right now.

    {
    	int waitTimeMinutes = Math.floorDiv(getWaitTime(),60);
    			
    	return "[" + name + " " + waitTimeMinutes + " min ("  + queue.size() + ")]";//return String of name of ride, wait time in minutes, number of riders waiting!
    }
}