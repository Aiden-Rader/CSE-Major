
-- “List the bowlers who live on the Eastside (Bellevue, Bothell, Duvall, Redmond, or Woodinville) and who are on teams 5, 6, 7, or 8.” (9 rows). --
USE BowlingLeagueExample;
SELECT BowlerFirstName, BowlerLastName, BowlerCity, TeamID
FROM Bowlers
WHERE BowlerCity IN ('Bellevue', 'Bothell', 'Duvall', 'Redmond', 'Woodinville') AND   
      TeamID BETWEEN 5 AND 8;