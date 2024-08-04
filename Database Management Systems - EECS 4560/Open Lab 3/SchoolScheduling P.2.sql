
-- “List students and all the classes in which they are currently enrolled.” --
USE SchoolSchedulingExample;
SELECT Students.StudFirstName, Students.StudLastName, Classes.ClassID
FROM Students
INNER JOIN Student_Schedules ON Students.StudentID = Student_Schedules.StudentID
INNER JOIN Classes ON Student_Schedules.ClassID = Classes.ClassID