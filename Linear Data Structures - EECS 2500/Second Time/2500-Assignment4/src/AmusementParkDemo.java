
public class AmusementParkDemo 
{
	private static final int CLOSING_TIME = 18000; //5 hours in minutes
	private static final int START_LEAVING_TIME = 900; //15 Minutes
	private static final int STATUS_TIME = 600; //10 Minutes
	
	public static void main(String[] args) 
	{
		AmusementPark park = new AmusementPark(CLOSING_TIME, START_LEAVING_TIME, STATUS_TIME);
		
		park.open();
		
		park.close();
		
		park.printDailyRecap();
	}

}
