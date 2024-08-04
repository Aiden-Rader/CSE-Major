/* Spring 2022 EECS 1510
 * Instructor: Dr. Hobbs
 * Written By: Dr. Hobbs
 * This is Exercise 08-21 -- Revel Ch. 8 Prog. Project 5
 * 
 * (Central city)
 * 
 * Given a set of cities, the central city is the city that has 
 * the shortest total distance to all other cities.
 * Write a program that prompts the user to enter the number of 
 * the cities and the locations of the cities (coordinates), and 
 * finds the central city and its total distance to all other cities.
 * 
 * Sample Run
 * 
 * Enter the number of cities: 5
 * Enter the coordinates of the cities: 2.5 5 5.1 3 1 9 5.4 54 5.5 2.1
 * The central city is at (2.5, 5.0)
 * The total distance to all other cities is 60.81
 * Class Name: Exercise08_21
 * 
 * 
 */

import java.util.Scanner;

public class Exercise08_21 
{
  public static void main(String[] args) 
  {
    
	  //need a scanner.
	  Scanner input = new Scanner(System.in);

	  //ask user for number of cities
	  System.out.print("Enter the number of cities: ");
	  
	  //read in the number of cities
	  int numberOfCities = input.nextInt();
    
	  //ask user to enter the coords of each city
	  System.out.print("Enter the coordinates of the cities: ");
	  
	  //need a place to store the coords. Each city has 2 coords
	  double[][] cities = new double[numberOfCities][2];
	  
	  //for each city, read in and store the coords. I know each city
	  //has 2 coords.
	  for (int i = 0; i < cities.length; i++) 
	    {
	      cities[i][0] = input.nextDouble();
	      cities[i][1] = input.nextDouble();     
	    }
    
	    // Find the central city and the total distance from the 
	    // central city to all other cities
	    double minTotal = totalDistance(cities, 0); //First, find the distance of city 0 to all other  
	    											//cities and make that the initial central 
	    											//city.
	    int minIndex = 0;							//setting the initial central city to the 
	    											//first city.
	
	    for (int i = 1; i < cities.length; i++)     //loop starts at 1 because we already found the 
	    											//total distance for city 0 and we set it as the 
	    											//central city.
	    {
	      double total = totalDistance(cities, i); //first time through, we are finding the distance
	      										   //from city 1 to all other cities.
	      
	      if (minTotal > total) 
	      {
	        minTotal = total;   //if the total distance of the current city is less than the 
	        					//previous min, we reset the minTotal to the current cities total
	        minIndex = i;		//AND we need to update the index so we know WHICH city is the new
	        				    //central city.
	      }
	    }
	    
	    System.out.println("The central city is at (" +
	      cities[minIndex][0] + ", " + cities[minIndex][1] + ")"); //we only need minIndex because
	    														   //we know each city has 2 coords
	    														   //in the same row, column index 0
	    														   //and column index 1.
	    System.out.println("The total distance to all other cities is " +
	      minTotal);
	    input.close();
	  }
	
	  public static double totalDistance(double[][] cities, int i) //array of objects is of size
	  															   //number of cities, 2. So for 5
	  															   //cities, my array would be 5x2
	  															   //i is my loop control variable from
	  															   //for loop on line 63.
	  {
	    //need a variable to store the total		  
		  double total = 0;
	    //need to find the total distance for each city
		  
		  for (int j = 0; j < cities.length; j++) 
			  
			  //need to find the distance from one city to another
			  //gonna call another method
			  
			  total += distance(cities[i], cities[j]); //find distance from city i to every other city
		  											   //for 5 cities, we would make this call 5 times
		  								 

		  return total;
	  }
	  
	  //method for finding the distance between two cities
	  //So, first call finds the distance from city i to city 0. That value is returned and added 
	  //to total. The for loop on line 92 is then executed again. 
	  public static double distance(double[] c1, double[] c2) 
	  {
	    return Math.sqrt((c1[0] - c2[0]) * (c1[0] - c2[0]) +
	      (c1[1] - c2[1]) * (c1[1] - c2[1]));
	  }
	}
