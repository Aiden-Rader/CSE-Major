
-- “Show me any engagements in October 2017 that start between noon and 5 p.m.” --
USE EntertainmentAgencyExample;
SELECT EngagementNumber, StartDate, EndDate, StartTime, StopTime
FROM Engagements
WHERE StartDate >= '2017-10-01' AND 
	  EndDate < '2017-11-01' AND
	  StartTime >= '12:00:00' AND 
	  StopTime <= '17:00:00' AND 
	  StopTime >= '12:00:00'
ORDER BY StartDate ASC;