-- list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred

SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = "Bradley Cooper"
AND title IN
(
    SELECT title from movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
    WHERE people.name = "Jennifer Lawrence"
);
