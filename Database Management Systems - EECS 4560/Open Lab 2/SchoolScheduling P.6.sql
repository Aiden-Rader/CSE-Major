
-- “Produce a list of the ID numbers all the Associate Professors who are employed full time” --
USE SchoolSchedulingExample;
SELECT StaffID ,Title, Status
FROM Faculty
WHERE Title = 'Associate Professor' AND
      Status = 'Full Time';