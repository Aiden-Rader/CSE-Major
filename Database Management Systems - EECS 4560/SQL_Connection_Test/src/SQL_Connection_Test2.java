import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;


public class SQL_Connection_Test2 
{

	public static void main(String[] args) 
	{
		String connectionURL = "jdbc:sqlserver://localhost;databaseName=PublicLibrary;integratedSecurity=true;encrypt=false";
		
		try 
		{
			Connection con = DriverManager.getConnection(connectionURL);
			Statement stmt = con.createStatement();
			
			String query = "SELECT Au_ID, NAME FROM AUTHOR WHERE Au_ID % 2 != 0";
			ResultSet resultset = stmt.executeQuery(query);
			
			while(resultset.next())
			{		
				int auId = resultset.getInt("Au_ID");
				String name = resultset.getString("Name");
				
				System.out.println("Au_ID: " + auId + ", Name: " + name);
			}
			
		} 
		catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
