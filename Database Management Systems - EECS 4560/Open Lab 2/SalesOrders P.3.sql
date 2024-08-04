
-- “Give me the names of all vendors based in Ballard, Bellevue, or Redmond.” --
USE SalesOrdersExample;
SELECT VendName, VendCity
FROM Vendors
WHERE VendCity IN ('Redmond', 'Ballard', 'Bellevue');