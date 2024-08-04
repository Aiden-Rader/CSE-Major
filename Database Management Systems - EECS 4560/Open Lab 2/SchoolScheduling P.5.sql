
-- “List all the subjects that have a subject code starting ‘MUS’.” --
USE SchoolSchedulingExample;
SELECT SubjectCode
FROM Subjects
WHERE SubjectCode LIKE 'MUS%'
ORDER BY SubjectCode ASC;
