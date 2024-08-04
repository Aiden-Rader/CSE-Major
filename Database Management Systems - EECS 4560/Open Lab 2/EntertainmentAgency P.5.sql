
-- “List all the engagements that start and end on the same day.” --
USE EntertainmentAgencyExample
SELECT EngagementNumber, StartDate, EndDate
FROM Engagements
WHERE StartDate = EndDate;