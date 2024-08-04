
-- “List the bowling teams and all the team members.” --
USE BowlingLeagueExample;
SELECT Teams.TeamName, Bowlers.BowlerID, Bowlers.BowlerFirstName, Bowlers.BowlerLastName
FROM Teams
INNER JOIN Bowlers ON Teams.TeamID = Bowlers.TeamID