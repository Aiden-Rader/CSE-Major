
--  “Find the bowlers who live in the same ZIP Code.” --
USE BowlingLeagueExample;
SELECT b1.BowlerFirstName, b1.BowlerLastName, b1.BowlerZip, b2.BowlerFirstName, b2.BowlerLastName, b1.BowlerZip
FROM Bowlers AS b1
INNER JOIN Bowlers AS b2 ON b1.BowlerZip = b2.BowlerZip AND b1.BowlerID <> b2.BowlerID