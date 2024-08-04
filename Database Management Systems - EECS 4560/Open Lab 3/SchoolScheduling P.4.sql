
-- “Show me the students who have a grade of 85 or better in art and who also have a grade of 85 or better in any computer course.” --
USE SchoolSchedulingExample;
SELECT 
    Students.StudentID, 
    Students.StudFirstName, 
    Students.StudLastName, 
    ArtSubject.SubjectName AS ArtSubjectName, 
    ArtSchedule.Grade AS ArtGrade,
    CompSubject.SubjectName AS CompSubjectName,
    CompSchedule.Grade AS CompGrade

FROM Students
INNER JOIN Student_Schedules AS ArtSchedule ON Students.StudentID = ArtSchedule.StudentID

INNER JOIN Classes AS ArtClass ON ArtSchedule.ClassID = ArtClass.ClassID
INNER JOIN Subjects AS ArtSubject ON ArtClass.SubjectID = ArtSubject.SubjectID

INNER JOIN Student_Schedules AS CompSchedule ON Students.StudentID = CompSchedule.StudentID

INNER JOIN Classes AS CompClass ON CompSchedule.ClassID = CompClass.ClassID
INNER JOIN Subjects AS CompSubject ON CompClass.SubjectID = CompSubject.SubjectID

WHERE ArtSubject.SubjectName LIKE '%Art%' AND ArtSchedule.Grade >= 85
AND CompSubject.SubjectName LIKE '%Computer%' AND CompSchedule.Grade >= 85
AND ArtSubject.SubjectID != CompSubject.SubjectID;

