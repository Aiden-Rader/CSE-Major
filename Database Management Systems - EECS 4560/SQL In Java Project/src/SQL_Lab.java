import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Scanner;
import java.sql.CallableStatement;

public class SQL_Lab
{
	// Declare any global variables needed here
	//private static final String jdbcDriver = "com.microsoft.sqlserver.jdbc.SQLServerDriver"; // Don't need this variable/Unused
	private static final String jdbcURL = "jdbc:sqlserver://localhost;integratedSecurity=true;databaseName=PublicLibrary;encrypt=false";
	private static Scanner keyboard = new Scanner(System.in);
	private static Connection databaseConnection = null;

	
	public static void main(String[] args) 
	{
		System.out.println("Program Started");
		
        // load the JDBC driver 
		try
		{
		DriverManager.registerDriver(new com.microsoft.sqlserver.jdbc.SQLServerDriver());
		System.out.print("JDBC Driver Loaded");
		}
		catch(Exception e)
		{
			System.err.print("Error loading JDBC Driver");
			e.printStackTrace(System.err);
			System.exit(0);
		}

		// Establish a connection to the local SQL Server with the PublicLibrary database on it
        try {
            
        	// Connect to the database
            databaseConnection = DriverManager.getConnection(jdbcURL);
            System.out.println("Connected to the database");

            // Call the menu (the main driver of the main method)
            displayMenu();

        } catch (SQLException e) {
            System.err.println("Error connecting to the database:");
            e.printStackTrace(System.err);
            System.exit(0);
        } 

	    // Close the connection and end the program
	    try 
	    {
			databaseConnection.close();
			System.out.println("Database connection closed");
			
		} 
	    catch (SQLException e) 
	    {
			System.err.print("Error closing database connection");
			e.printStackTrace(System.err);
			System.exit(0);
		}
	    
	   System.out.println("Program has finished");
	   
	} // End Main

	
	private static void displayMenu()
	{
		while (true)
		{
			System.out.println("\n\n");
			System.out.println("         MAIN MENU      ");
			System.out.println("------------------------");
			System.out.println("1. Look up Book         ");
			System.out.println("2. Check Out Book       ");
			System.out.println("3. Return Book          ");
			System.out.println("4. View Book History    ");
			System.out.println("5. View Customer History");
			System.out.println("6. Show Books On Loan   \n");
			System.out.println("7. Exit                 \n");
			System.out.print  ("Enter Option (1-7): ");
			int option = keyboard.nextInt();
			
			if      (option == 1) lookUpBook();
			else if (option == 2) CheckOutBook();
			else if (option == 3) ReturnBook();        
			else if (option == 4) ViewBookHistory();   // NEW <-- Yours to write
			else if (option == 5) ViewCustHistory();   // NEW <-- Yours to write
			else if (option == 6) ShowBooksOnLoan();   // NEW <-- Yours to write
			else if (option == 7) return;
			else                  System.out.println("Please use an option between 1 and 7");
		}	
	}
	
	private static void ShowBooksOnLoan() // DONE
	{
	    try 
	    {
	        // Execute the query to fetch the books currently on loan
	        String query = "SELECT ISBN FROM TITLE "
	        		+ "WHERE Date_Out IS NOT NULL";
	        PreparedStatement pstmt = databaseConnection.prepareStatement(query);
	        ResultSet rs = pstmt.executeQuery();

	        DisplayBookOnLoanHeader();

	        while (rs.next()) 
	        {
	            String isbn = rs.getString("ISBN");

	            // Fetch corresponding title and customer information
	            String bookQuery = "SELECT T.Title AS Title, "
	                    + "CONCAT(C.FirstName, ' ', C.LastName) AS CustomerName, "
	                    + "T.Card_ID AS Card_ID, "
	                    + "T.Date_Out AS DateOut, "
	                    + "DATEDIFF(day, T.Date_Out, GETDATE()) AS DaysOut "
	                    + "FROM TITLE T "
	                    + "JOIN CUSTOMER C ON T.Card_ID = C.Card_ID "
	                    + "WHERE T.ISBN = ? "
	                    + "ORDER BY T.Date_Out ASC";
	            PreparedStatement bookPstmt = databaseConnection.prepareStatement(bookQuery);
	            bookPstmt.setString(1, isbn);
	            ResultSet bookRs = bookPstmt.executeQuery();

	            // Display book and customer information
	            if (bookRs.next()) 
	            {
	                String title = bookRs.getString("Title");
	                String customer = bookRs.getString("CustomerName");
	                String cardID = bookRs.getString("Card_ID");
	                String checkedOut = bookRs.getString("DateOut");
	                int daysOut = bookRs.getInt("DaysOut");
	                
	                int maxTitleLength = 50; 
	                String truncatedTitle = title.length() > maxTitleLength ? title.substring(0, maxTitleLength - 3) + "..." : title;
	                
	                /// Print out the information for that result set
	                System.out.printf("%-52s %-14s %-31s %-10s %-12s %-8d\n",
	                        truncatedTitle, isbn, customer, cardID, checkedOut, daysOut);
	            }
	        }
	        rs.close();
	        pstmt.close();
	    } 
	    catch (SQLException err) 
	    {
	        System.err.println("Error fetching all books currently on loan");
	        err.printStackTrace(System.err);
	    }
	}

	// Only displays the customers history with what books they HAVE checked out in the past, not currently checked out
	private static void ViewCustHistory() // DONE
	{
		
		System.out.print("Enter Customer's Card_ID: ");
		String custID = keyboard.next();
		
		// Look up this customer
		try
		{
			Statement sqlStatement = databaseConnection.createStatement();
			String queryString = "SELECT COUNT(*) as N FROM CUSTOMER WHERE Card_ID='" + custID + "';";
			ResultSet rs = sqlStatement.executeQuery(queryString);
			rs.next(); 	// Go to the first (only) record
			if (rs.getInt("N") == 0)
			{
				System.out.println("Customer's Card_ID Not Found\n");
				return;
			}
		}
		catch (SQLException err)
		{
			System.out.println("SQL Exception " + err.getMessage() + " occurred looking up customer\n");
		}
		
		try
		{	
			// Execute the query to fetch the Customer history
	        String query = "SELECT CONCAT(C.FirstName, ' ', C.LastName) AS CustomerName, "
                    + "T.Title AS Title, "
                    + "T.ISBN AS ISBN, "
                    + "H.Date_Out AS CheckedOut, "
                    + "H.Date_In AS BackIn, "
                    + "DATEDIFF(day, H.Date_Out, H.Date_In) AS DaysOut, "
                    + "H.Fine_Due AS FineDue "
                    + "FROM HISTORY H "
                    + "JOIN CUSTOMER C ON H.Card_ID = C.Card_ID "
                    + "JOIN TITLE T ON H.ISBN = T.ISBN "
                    + "WHERE H.Card_ID = ? "
                    + "ORDER BY H.Date_Out ASC";
	        
	        // Prepare the statement and set the ISBN parameter
	        PreparedStatement pstmt = databaseConnection.prepareStatement(query);
	        pstmt.setString(1, custID);
			ResultSet rs = pstmt.executeQuery();
			
			// Display the Customer History header
			DisplayCustomerHistoryHeader();
			
			while (rs.next()) {
				String customer = rs.getString("CustomerName");
                String title = rs.getString("Title");
                String isbn = rs.getString("ISBN");
                String checkedOut = rs.getString("CheckedOut");
                String backIn = rs.getString("BackIn");
                int daysOut = rs.getInt("DaysOut");
                double fineDue = rs.getDouble("FineDue");
                
                /*	TITLE LIMITER
                 * Introduce a Title Length limit where if the title is too long 
                 * and messes with the alignment then we can limit the title length
                 * to a set number.
                 */
                int maxTitleLength = 50; 
                String truncatedTitle = title.length() > maxTitleLength ? title.substring(0, maxTitleLength - 3) + "..." : title;
	            
                // Print out the information for that result set
                System.out.printf("%-30s %-52s %-15s %-13s %-13s %-10d $%.2f\n",
                        customer, truncatedTitle, isbn, checkedOut, backIn, daysOut, fineDue);
			}	
			
			// Close the result set and the statement
    		rs.close();
    		pstmt.close();
		}
		catch (SQLException err)
		{
			System.err.print("Error fetching customer history");
			err.printStackTrace(System.err);
		}	
	}

	private static void ViewBookHistory() // DONE
	{
		// Start with looking up the books ISBN Number so we can look at the history of that specific book
		System.out.print("Enter book's ISBN: ");
		String isbn = keyboard.next();
		
		// Look up the Book 
		try
		{
			Statement sqlStatement = databaseConnection.createStatement();
			String queryString = "SELECT COUNT(*) as N FROM TITLE WHERE ISBN='" + isbn + "';";
			ResultSet rs = sqlStatement.executeQuery(queryString);
			rs.next(); 	// Go to the first (only) record
			if (rs.getInt("N") == 0)
			{
				System.out.println("Book's ISBN Not Found\n");
				return;
			}
		}
		// If the book cannot be found throw an error
		catch (SQLException err)
		{
			System.out.println("SQL Exception " + err.getMessage() + " occurred looking up Book ISBN\n");
		}
		
		try
		{
			// Execute the query to fetch the book history
	        String query = "SELECT "
	                + "H.Date_Out AS CheckedOut, "
	                + "H.Date_In AS BackIn, "
	                + "DATEDIFF(day, H.Date_Out, H.Date_In) AS DaysOut, "
	                + "H.Card_ID AS CustomerId, "
	                + "CONCAT(C.FirstName, ' ', C.LastName) AS CustomerName "
	                + "FROM dbo.HISTORY H "
	                + "JOIN dbo.CUSTOMER C ON H.Card_ID = C.Card_ID "
	                + "WHERE H.ISBN = ? "
	                + "ORDER BY H.Date_Out ASC";
			
	        // Prepare the statement and set the ISBN parameter
	        PreparedStatement pstmt = databaseConnection.prepareStatement(query);
	        pstmt.setString(1, isbn);
			ResultSet rs = pstmt.executeQuery();
			
			// Display the Book History header
			DisplayBookHistoryHeader();
			
			while(rs.next())
			{
				String checkedOut = rs.getString("CheckedOut");
				String backIn = rs.getString("BackIn");
				int daysOut = rs.getInt("DaysOut");
				String customerID = rs.getString("CustomerId");
				String customer = rs.getString("CustomerName");
				
				System.out.printf("%-12s %-11s %-10d %-13s %-12s\n", 
						checkedOut, backIn, daysOut, customerID, customer);
			}
			
			// Close the result set and the statement
			rs.close();
			pstmt.close();
		}
		catch (SQLException err)
		{
			System.err.println("Error fetching book history");
			err.printStackTrace(System.err);
		}
		
	}


	

	private static void lookUpBook()
	{
		String partialQuery = "SELECT A.Name, T.Title, T.ISBN, T.Date_out " +
							  "FROM   AUTHOR A, TITLE T, TITLE_AUTHOR TA " + 
							  "WHERE  TA.Au_ID = A.Au_ID AND T.ISBN = TA.ISBN AND ";
		
	
		System.out.println("\n\n");
		System.out.println("       BOOK LOOKUP       ");
		System.out.println("-------------------------");
		System.out.println("1. By Author             ");
		System.out.println("2. By ISBN               ");
		System.out.println("3. By Title              \n");
		System.out.println("4. Return to main menu   \n");
		System.out.print  ("Enter option (1-4): ");
		int option = keyboard.nextInt();
	
		switch(option)
		{
			case 4: return;
		
			case 1: {
						System.out.print("Enter Author Name (or partial): ");
						keyboard.nextLine(); 				// flush Scanner buffer
						String name = keyboard.nextLine();	// Get author name fragment
						try
						{
							Statement sqlStatement = databaseConnection.createStatement();
							String queryString = partialQuery + " A.Name like '%" + name + "%' ORDER BY T.ISBN, A.Name;";
							ResultSet rs = sqlStatement.executeQuery(queryString);
							displayBookList(rs);
							rs.close();
						}
						catch (SQLException err)
						{
							System.out.println("SQL Exception " + err.getMessage() + " occurred during lookup\n");
						}
						break;
			}
			
			case 2: {
						System.out.print("Enter ISBN (n-nnnnnnn-n-n) (or partial): ");
						keyboard.nextLine(); 				// flush Scanner buffer
						String isbn = keyboard.nextLine();	// Get author name fragment
						try
						{
							Statement sqlStatement = databaseConnection.createStatement();
							String queryString = partialQuery + " T.ISBN like '%" + isbn + "%' ORDER BY T.ISBN, A.Name;";
							ResultSet rs = sqlStatement.executeQuery(queryString);
							displayBookList(rs);
							rs.close();
						}
						catch (SQLException err)
						{
							System.out.println("SQL Exception " + err.getMessage() + " occurred during lookup\n");
						}
						break;
			}
			
			case 3: {
						System.out.print("Enter Book Title () (or partial): ");
						keyboard.nextLine(); 				// flush Scanner buffer
						String title = keyboard.nextLine();	// Get author name fragment
						try
						{
							Statement sqlStatement = databaseConnection.createStatement();
							String queryString = partialQuery + " T.Title like '%" + title + "%' ORDER BY T.ISBN, A.Name;";
							ResultSet rs = sqlStatement.executeQuery(queryString);
							displayBookList(rs);
							rs.close();
						}
						catch (SQLException err)
						{
							System.out.println("SQL Exception " + err.getMessage() + " occurred during lookup\n");
						}
						break;
			}
			
			default: System.out.println("Please use 1 - 4");
		}
	}
	
	private static void displayBookList(ResultSet rs)
	{
		// Accepts a ResultSet created from the book lookup menu.  The book lookup menu's ResultSets
		// consist of a Date_out (the date the book was checked out, which may be NULL),
		// The book's ISBN, the Author's Name, and the book's Title.
		try
		{
			if (!rs.isBeforeFirst())
			{
				System.out.println("No Matches Found\n");
			}
			else
			{
				System.out.println("IN?      ISBN                Author                    TITLE");
				System.out.println("---  -------------  -------------------------  ----------------------------------------------------------------------");
				while (rs.next())
				{
					System.out.printf("%3s  ", (rs.getDate("Date_out") == null) ? "YES" : "NO");
				
					System.out.printf("%13s  %-25s  %-70s\n", 
									  trimTo(rs.getString("ISBN"),  13), 
									  trimTo(rs.getString("Name"),  25), 
									  trimTo(rs.getString("Title"), 70));
				}
			}
		}
		catch (SQLException err)
		{
			System.out.println("SQL Exception " + err.getMessage() + " occurred during display\n");
		}
		
	} // end lookUpBook
	
	private static String trimTo(String s, int len)
	{
		// returns S, trimmed to no more than len characters
		if (s.length() < len) return s;
		return s.substring(0, len);
		
	} // end trimTo
	
	private static void CheckOutBook()
	{
		// In order to check out a book, we need to:
		// Get the customer's ID (and make sure they're a valid customer)
		// get the ISBN from the customer (and make sure IT's valid), and finally,
		// Set the book's Date_out to today, and the Cust_ID to the customer.
		
		System.out.print("Enter Customer's Card_ID: ");
		String custID = keyboard.next();
		
		// Look up this customer
		try
		{
			Statement sqlStatement = databaseConnection.createStatement();
			String queryString = "SELECT COUNT(*) as N FROM CUSTOMER WHERE Card_ID='" + custID + "';";
			ResultSet rs = sqlStatement.executeQuery(queryString);
			rs.next(); 	// Go to the first (only) record
			if (rs.getInt("N") == 0)
			{
				System.out.println("Customer's Card_ID Not Found\n");
				return;
			}
		}
		catch (SQLException err)
		{
			System.out.println("SQL Exception " + err.getMessage() + " occurred looking up customer\n");
		}
		
		// We know we have a valid customer's library card
		// O.K., so far, so good. Get the ISBN:
		System.out.print("Enter book's ISBN: ");
		String isbn = keyboard.next();
		
		// Look up this Book
		try
		{
			Statement sqlStatement = databaseConnection.createStatement();
			String queryString = "SELECT COUNT(*) as N FROM TITLE WHERE ISBN='" + isbn + "';";
			ResultSet rs = sqlStatement.executeQuery(queryString);
			rs.next(); 	// Go to the first (only) record
			if (rs.getInt("N") == 0)
			{
				System.out.println("Book's ISBN Not Found\n");
				return;
			}
		}
		catch (SQLException err)
		{
			System.out.println("SQL Exception " + err.getMessage() + " occurred looking up Book ISBN\n");
		}
		
		// O.K., if we get to here, we know we have a valid CUSTOMER, and we have a valid ISBN
		// The last thing to check is whether or not the book is OUT!
		try
		{
			Statement sqlStatement = databaseConnection.createStatement();
			String queryString = "SELECT COUNT(*) as N FROM TITLE WHERE ISBN='" + isbn + "' AND Date_out IS NULL;";
			ResultSet rs = sqlStatement.executeQuery(queryString);
			rs.next(); 	// Go to the first (only) record
			if (rs.getInt("N") == 0)
			{
				System.out.println("Book's is ALREADY CHECKED OUT\n");
				return;
			}
		}
		catch (SQLException err)
		{
			System.out.println("SQL Exception " + err.getMessage() + " occurred looking up Book status\n");
		}
		
		// FINALLY -- we can check it out. We need to set this book's Out_date to today, and set the customer
		// who is checking it out
		try
		{
			Statement sqlStatement = databaseConnection.createStatement();
			String update = "UPDATE TITLE SET Card_ID = " + custID + ", Date_out = GETDATE() " +
			                "WHERE ISBN = '" + isbn + "';";
			sqlStatement.executeUpdate(update);

		}
		catch (SQLException err)
		{
			System.out.println("SQL Exception " + err.getMessage() + " occurred checking out book\n");
		}

		
	} // end CheckOutBook


	private static void ReturnBook()
	{
		// Returns a book using Stored Procedure ReturnBook, which requires an ISBN as its lone
		// input parameter, and which returns the fine as the number of DIMES (days overdue) due.
		// If the book whose ISBN we supply either isn't a recognized book from the library, or
		// is not out on loan, ReturnBook will return -1 to indicate this state of affairs
		
		System.out.print("Enter the ISBN of the book to return: ");
		String isbn = keyboard.next();
		
		try
		{
			CallableStatement cstmt = databaseConnection.prepareCall("{call ReturnBook(?, ?)}");
			cstmt.setString("ISBN",  isbn);
			cstmt.registerOutParameter("RETURN_VALUE",  java.sql.Types.INTEGER);
			cstmt.execute();
			int retVal = cstmt.getInt("RETURN_VALUE");
			if (retVal == -1)
			{
				System.out.println("Either that ISBN is not valid in the library, or it isn't checked out");
			}
			else
			{
				System.out.print("Book successfully returned - ");
				if (retVal == 0) System.out.println("NO FINE DUE");
				else             System.out.printf("FINE DUE: $5.2f\n", retVal * 0.10);				
			}
			cstmt.close();			
		} // end of try block
		catch (SQLException err) 
		{
			System.out.println("SQL Exception: " + err.getMessage() + " occurred during return\n");
		}
		
	} // end of ReturnBook
	
	
	private static void DisplayBookOnLoanHeader() // Use this format for displaying all the current books on loan. 
	{
		System.out.println("TITLE                                                ISBN           CUSTOMER                        CARD_ID    CHECKED OUT  DAYS OUT");
		System.out.println("---------------------------------------------------  -------------  ------------------------------  ---------- -----------  --------");

	}

	private static void DisplayBookHistoryHeader() // Use this format for displaying the book history. 
	{
		System.out.println("CHECKED OUT   BACK IN    DAYS OUT   CUSTOMER_ID   CUSTOMER                      ");
		System.out.println("-----------  ----------  --------   -----------   ------------------------------");

	}
	
	private static void DisplayCustomerHistoryHeader() // Use this format for displaying the customer history.
	{
		System.out.println("CUSTOMER                       TITLE                                                ISBN           CHECKED OUT   BACK IN       DAYS OUT   FINE DUE");
		System.out.println("----------------------------   ---------------------------------------------------  -------------  -----------   -----------   --------   --------");


	}
} // End Class