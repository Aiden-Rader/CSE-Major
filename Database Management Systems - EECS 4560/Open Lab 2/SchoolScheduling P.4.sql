
-- “Which students live outside of the Pacific Northwest?” --
USE SchoolSchedulingExample;
SELECT StudFirstName, StudLastName, StudState
FROM Students
WHERE StudState NOT IN ('OR','WA','ID', 'MT', 'WY'); -- List of 5 states in the Pacific Northwest -- 