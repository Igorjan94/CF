    
SELECT id, min(date_from) as date_from, max(date_to) as date_to, type
  FROM (SELECT id, type, date_from, date_to,
               max(new_start) OVER (ORDER BY date_from, date_to) AS left_edge
          FROM (SELECT id, type, date_from, date_to, CASE WHEN date_from < max(le) OVER (ORDER BY date_from,date_to) THEN null ELSE date_from END AS new_start
                  FROM (SELECT id, 
              unnest( 
       	case when type <> 'NULL' then ARRAY[wi.type] else
         ARRAY['DARK', 'LIGHT', 'OPEN_SPACE']
       end) as type, 
                  date_from, date_to, lag(date_to) OVER (ORDER BY date_from,date_to) AS le FROM work_interval wi) s1) s2) s3
 GROUP BY (left_edge, id, type) order by (id, type);
