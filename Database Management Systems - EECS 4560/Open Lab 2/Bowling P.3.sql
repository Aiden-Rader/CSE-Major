
-- “Give me a list of the tournaments held during September 2017.” (4 rows). --
USE BowlingLeagueExample;
SELECT TourneyID, TourneyDate
FROM Tournaments
WHERE TourneyDate >= '2017/09/01' AND 
      TourneyDate < '2017/10/01';