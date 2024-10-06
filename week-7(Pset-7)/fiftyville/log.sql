-- Retrieve interview transcripts from the crime scene on July 28, 2021
SELECT transcript
FROM interviews
WHERE month = 7
  AND day = 28;

-- Get crime scene descriptions from Humphrey Street on July 28, 2021
SELECT description
FROM crime_scene_reports
WHERE month = 7
  AND day = 28
  AND street = 'Humphrey Street';

-- Find people who exited the bakery between 10:15 and 10:25 AM on July 28, 2021
-- The 'activity' column indicates the 'exit' event
SELECT name
FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28
  AND month = 7
  AND year = 2023
  AND hour = 10
  AND minute >= 15
  AND minute < 25
  AND activity = 'exit';

-- Check activity logs at 10:20 AM on July 28, 2021
SELECT activity
FROM bakery_security_logs
WHERE month = 7
  AND day = 28
  AND hour = 10
  AND minute = 20;

-- Find people who withdrew money from the ATM on Leggett Street on July 28, 2021
SELECT name
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE day = 28
  AND month = 7
  AND year = 2021
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw';

-- Find phone calls with a duration less than 60 seconds on July 28, 2021
-- To identify who made and received short phone calls
SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE day = 28
  AND month = 7
  AND year = 2023
  AND duration < 60;

SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE day = 28
  AND month = 7
  AND year = 2023
  AND duration < 60;

-- Find the receiver of a phone call made by Bruce on July 28, 2021
-- This helps to identify Bruce's accomplice
SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE day = 28
  AND month = 7
  AND year = 2023
  AND duration < 60
  AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce'); /* Robin */

-- Find the city where flight ID 36 is heading on July 29, 2021
-- The thief chose the earliest flight available
SELECT city
FROM airports
WHERE id = (SELECT destination_airport_id
            FROM flights
            WHERE flights.id = 36); /* New York */

-- Find the earliest flight on July 29, 2021
SELECT hour, minute
FROM flights
WHERE year = 2023
  AND day = 29
  AND month = 7
ORDER BY hour, minute
LIMIT 1;

-- Find the ID of the earliest flight at 8:20 AM
SELECT id
FROM flights
WHERE hour = 8
  AND minute = 20;

-- Find the names of passengers on flight ID 36
SELECT name
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE passengers.flight_id = 36;
