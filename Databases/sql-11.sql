-- Проверял у себя в postgres
-- Добавим данные и таблицы

CREATE TABLE Students (
  student_id INT PRIMARY KEY,
  name VARCHAR(50),
  faculty VARCHAR(50),
  enrollment_year INT
);
INSERT INTO Students VALUES
(1, 'Иван Иванов', 'Информатика', 2020),
(2, 'Петр Петров', 'Математика', 2021),
(3, 'Сергей Сергеев', 'Физика', 2020),
(4, 'Анна Аннова', 'Информатика', 2021),
(5, 'Мария Мариева', 'Биология', 2022),
(6, 'Алексей Алексеев', 'Информатика', 2020),
(7, 'Елена Еленова', 'Математика', 2022),
(8, 'Дмитрий Дмитриев', 'Физика', 2021),
(9, 'Ольга Ольгова', 'Информатика', 2022),
(10, 'Николай Николаев', 'Химия', 2020);

CREATE TABLE Teachers (
  teacher_id INT PRIMARY KEY,
  name VARCHAR(50),
  department VARCHAR(50),
  hire_year INT
);

INSERT INTO Teachers VALUES
(1, 'Александр Александров', 'Информатика', 2015),
(2, 'Борис Борисов', 'Математика', 2018),
(3, 'Виктор Викторов', 'Физика', 2016),
(4, 'Галина Галинова', 'Информатика', 2020),
(5, 'Дарья Дарьева', 'Биология', 2019),
(6, 'Евгений Евгеньев', 'Информатика', 2017),
(7, 'Жанна Жаннова', 'Математика', 2021),
(8, 'Зоя Зоева', 'Физика', 2018),
(9, 'Игорь Игорев', 'Информатика', 2019),
(10, 'Кирилл Кириллов', 'Химия', 2017);

CREATE TABLE Courses (
  course_id INT PRIMARY KEY,
  title VARCHAR(100),
  department VARCHAR(50),
  credits INT
);
INSERT INTO Courses VALUES
(1, 'Введение в программирование', 'Информатика', 4),
(2, 'Алгебра', 'Математика', 3),
(3, 'Механика', 'Физика', 4),
(4, 'Базы данных', 'Информатика', 5),
(5, 'Генетика', 'Биология', 3),
(6, 'Операционные системы', 'Информатика', 5),
(7, 'Математический анализ', 'Математика', 4),
(8, 'Электродинамика', 'Физика', 5),
(9, 'Веб-разработка', 'Информатика', 4),
(10, 'Органическая химия', 'Химия', 4);

CREATE TABLE StudentCourses (
  student_id INT,
  course_id INT,
  semester VARCHAR(20),
  grade INT,
  PRIMARY KEY (student_id, course_id, semester),
  FOREIGN KEY (student_id) REFERENCES Students(student_id),
  FOREIGN KEY (course_id) REFERENCES Courses(course_id)
);

INSERT INTO StudentCourses VALUES
(1, 1, '2020-2021 Fall', 5),
(1, 4, '2021-2022 Spring', 4),
(2, 2, '2021-2022 Fall', 5),
(2, 7, '2022-2023 Spring', 3),
(3, 3, '2020-2021 Fall', 4),
(3, 8, '2021-2022 Spring', 5),
(4, 1, '2021-2022 Fall', 5),
(4, 6, '2022-2023 Spring', 4),
(5, 5, '2022-2023 Fall', 3),
(6, 1, '2020-2021 Fall', 4),
(6, 4, '2021-2022 Spring', 5),
(6, 6, '2022-2023 Fall', 4),
(7, 2, '2022-2023 Fall', 5),
(8, 3, '2021-2022 Fall', 4),
(9, 1, '2022-2023 Fall', 5),
(10, 10, '2020-2021 Fall', 3);

CREATE TABLE TeacherCourses (
  teacher_id INT,
  course_id INT,
  semester VARCHAR(20),
  PRIMARY KEY (teacher_id, course_id, semester),
  FOREIGN KEY (teacher_id) REFERENCES Teachers(teacher_id),
  FOREIGN KEY (course_id) REFERENCES Courses(course_id)
);

INSERT INTO TeacherCourses VALUES
(1, 1, '2020-2021 Fall'),
(1, 4, '2021-2022 Spring'),
(2, 2, '2021-2022 Fall'),
(2, 7, '2022-2023 Spring'),
(3, 3, '2020-2021 Fall'),
(3, 8, '2021-2022 Spring'),
(4, 1, '2021-2022 Fall'),
(4, 6, '2022-2023 Spring'),
(5, 5, '2022-2023 Fall'),
(6, 1, '2020-2021 Fall'),
(6, 4, '2021-2022 Spring'),
(6, 6, '2022-2023 Fall'),
(7, 2, '2022-2023 Fall'),
(8, 3, '2021-2022 Fall'),
(9, 1, '2022-2023 Fall'),
(10, 10, '2020-2021 Fall');



-- 1  Найти все уникальные названия факультетов/кафедр из таблиц студентов и преподавателей
SELECT DISTINCT faculty AS name FROM Students
UNION
SELECT DISTINCT department FROM Teachers;

-- 2 Найти студентов, которые получали и оценку 5, и оценку 4
SELECT student_id
FROM StudentCourses
GROUP BY student_id
HAVING COUNT(DISTINCT grade) FILTER (WHERE grade = 5) > 0
   AND COUNT(DISTINCT grade) FILTER (WHERE grade = 4) > 0;

-- 3  Найти преподавателей, которые начали работать после 2018 года, но не ведут курсы по информатике
SELECT t.teacher_id, t.name
FROM Teachers t
WHERE t.hire_year > 2018
  AND NOT EXISTS (
    SELECT 1
    FROM TeacherCourses tc
    JOIN Courses c ON tc.course_id = c.course_id
    WHERE tc.teacher_id = t.teacher_id AND c.department = 'Информатика'
);

-- 4 Найти курсы с 4 кредитами, которые не являются курсами по информатике:
SELECT *
FROM Courses
WHERE credits = 4 AND department != 'Информатика';

-- 5 Найти все уникальные года (поступления/найма) из таблиц студентов и преподавателей:
SELECT DISTINCT enrollment_year AS year FROM Students
UNION
SELECT DISTINCT hire_year FROM Teachers;

-- 6  Найти преподавателей, которые ведут и курсы по информатике, и курсы по математике
SELECT tc.teacher_id, t.name
FROM TeacherCourses tc
JOIN Courses c ON tc.course_id = c.course_id
JOIN Teachers t ON tc.teacher_id = t.teacher_id
WHERE c.department IN ('Информатика', 'Математика')
GROUP BY tc.teacher_id, t.name
HAVING COUNT(DISTINCT c.department) = 2;

-- 7  Найти студентов факультета "Информатика", которые не записаны на курс "Базы данных":
SELECT s.student_id, s.name
FROM Students s
WHERE s.faculty = 'Информатика'
  AND NOT EXISTS (
    SELECT 1
    FROM StudentCourses sc
    JOIN Courses c ON sc.course_id = c.course_id
    WHERE c.title = 'Базы данных' AND sc.student_id = s.student_id
);

-- 8 Найти все уникальные семестры, когда велись курсы:
SELECT DISTINCT semester FROM TeacherCourses;

-- 9  Найти курсы, которые велись и в 2020-2021, и в 2022-2023 учебных годах:
SELECT course_id
FROM TeacherCourses
WHERE semester LIKE '2020-2021%' OR semester LIKE '2022-2023%'
GROUP BY course_id
HAVING COUNT(DISTINCT SUBSTRING(semester FROM 1 FOR 9)) = 2;

-- 10 Найти студентов, которые учились в 2021 году, но не получали оценку 5
SELECT DISTINCT sc.student_id, s.name
FROM StudentCourses sc
JOIN Students s ON sc.student_id = s.student_id
WHERE sc.semester LIKE '%2021%'
  AND sc.student_id NOT IN (
    SELECT student_id FROM StudentCourses WHERE grade = 5
);

-- 11 Найти все уникальные оценки (из StudentCourses) и кредиты (из Courses):
SELECT DISTINCT grade FROM StudentCourses
UNION
SELECT DISTINCT credits FROM Courses;

-- 12 Найти преподавателей, которые ведут курсы и осенью, и весной:
SELECT tc.teacher_id, t.name
FROM TeacherCourses tc
JOIN Teachers t ON tc.teacher_id = t.teacher_id
GROUP BY tc.teacher_id, t.name
HAVING COUNT(DISTINCT CASE 
                         WHEN semester ILIKE '%Fall%' THEN 'Fall'
                         WHEN semester ILIKE '%Spring%' THEN 'Spring'
                       END) = 2;

-- 13 Найти курсы по информатике, которые не ведет преподаватель с id=1:
SELECT c.course_id, c.title
FROM Courses c
WHERE c.department = 'Информатика'
  AND c.course_id NOT IN (
    SELECT course_id FROM TeacherCourses WHERE teacher_id = 1
);
