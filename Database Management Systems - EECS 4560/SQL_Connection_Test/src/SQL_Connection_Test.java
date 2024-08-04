import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class SQL_Connection_Test 
{

	public static void main(String[] args) 
	{
		String connectionUrl = "jdbc:sqlserver://localhost;integratedSecurity=true;encrypt=false";
		
		try(Connection con = DriverManager.getConnection(connectionUrl);
				Statement stmt = con.createStatement();)
		{
			String SQL = "SELECT @@VERSION AS Version";
			ResultSet rs = stmt.executeQuery(SQL);
			
			while (rs.next())
			{
				System.out.println(rs.getString("Version"));
			}
		}
		
		catch(SQLException e)
		{
			e.printStackTrace();
		}
	}

}
