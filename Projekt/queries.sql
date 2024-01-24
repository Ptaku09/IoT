SELECT
    worker_id,
    first_name,
    last_name,
    AVG(daily_work_hours) AS avg_daily_work_hours
FROM (
    SELECT
        w.id AS worker_id,
        w.first_name,
        w.last_name,
        strftime('%Y-%m-%d', s.start_time) AS work_date,
        COALESCE(SUM((julianday(COALESCE(s.end_time, CURRENT_TIMESTAMP)) - julianday(s.start_time)) * 24), 0) AS daily_work_hours
    FROM
        workers w
    JOIN
        cards c ON w.card_id = c.uuid
    LEFT JOIN
        sessions s ON w.card_id = s.card_id
    GROUP BY
        w.id, w.first_name, w.last_name, work_date
) AS subquery
GROUP BY
    worker_id, first_name, last_name
ORDER BY
    worker_id;



SELECT
    w.id AS worker_id,
    w.first_name,
    w.last_name,
    SUM((julianday(s.end_time) - julianday(s.start_time)) * 24) AS total_work_hours
FROM
    workers w
JOIN
    cards c ON w.card_id = c.uuid
LEFT JOIN
    sessions s ON w.card_id = s.card_id
GROUP BY
    w.id, w.first_name, w.last_name
ORDER BY
    worker_id;
