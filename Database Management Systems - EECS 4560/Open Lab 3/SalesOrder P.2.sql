
-- “List employees and the customers for whom they booked an order.” --
USE SalesOrdersExample;
SELECT Employees.EmpFirstName, Employees.EmpLastName, Customers.CustFirstName, Customers.CustLastName
FROM Employees 
INNER JOIN Orders ON Employees.EmployeeID = Orders.EmployeeID 
INNER JOIN Customers ON Orders.CustomerID = Customers.CustomerID;