
-- “Show me the vendors and the products they supply to us for products that cost less than $100.” --
USE SalesOrdersExample;
SELECT Vendors.VendName, Products.ProductName, Products.RetailPrice
FROM Vendors 
INNER JOIN Product_Vendors ON Vendors.VendorID = Product_Vendors.VendorID
INNER JOIN Products ON Product_Vendors.ProductNumber = Products.ProductNumber
WHERE Products.RetailPrice < 100;