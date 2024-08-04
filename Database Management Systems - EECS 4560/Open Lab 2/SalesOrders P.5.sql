
-- “Which vendors do we work with that don’t have a Web site?” --USE SalesOrdersExample;SELECT VendName, VendWebPageFROM VendorsWHERE VendWebPage IS NULL;