
-- “Display buildings and all the classrooms in each building.” --
USE SchoolSchedulingExample;
SELECT Buildings.BuildingName, Buildings.BuildingCode, Class_Rooms.ClassRoomID
FROM Buildings
INNER JOIN Class_Rooms ON Buildings.BuildingCode = Class_Rooms.BuildingCode