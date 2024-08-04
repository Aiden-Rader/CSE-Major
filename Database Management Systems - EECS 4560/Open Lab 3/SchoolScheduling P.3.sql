
-- “List the faculty staff and the subject each teaches.” --
USE SchoolSchedulingExample;
SELECT Faculty.StaffID,Staff.StfFirstName, Staff.StfLastname, Subjects.SubjectName AS SubjectTaught
FROM Faculty
INNER JOIN Faculty_Subjects ON Faculty.StaffID = Faculty_Subjects.StaffID
INNER JOIN Subjects ON Faculty_Subjects.SubjectID = Subjects.SubjectID
INNER JOIN Staff ON Faculty.StaffID = Staff.StaffID
ORDER BY Faculty.StaffID