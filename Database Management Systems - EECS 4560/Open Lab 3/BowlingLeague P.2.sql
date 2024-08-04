
-- “Display the bowlers, the matches they played in, and the bowler game scores.” --
USE BowlingLeagueExample;
SELECT Bowlers.BowlerFirstName, Bowlers.BowlerLastName, Bowler_Scores.MatchID, Bowler_Scores.RawScore 
FROM Bowlers
INNER JOIN Bowler_Scores ON Bowlers.BowlerID = Bowler_Scores.BowlerID