
-- “Display all orders, the products in each order, and the amount owed for each product, in order number sequence.” --
USE SalesOrdersExample;
SELECT Orders.OrderNumber, Products.ProductName, Order_Details.QuantityOrdered, Order_Details.QuotedPrice
FROM Orders
INNER JOIN Order_Details ON Orders.OrderNumber = Order_Details.OrderNumber 
INNER JOIN Products ON Order_Details.ProductNumber = Products.ProductNumber
ORDER BY Orders.OrderNumber;