WITH range_values AS (SELECT 
	type, 
	(case 
		when type = 'WEEK' then 
			'1999-12-27'::date
		when type = 'FRIDAY_THE_13TH' then 
			'1999-12-24'::date
		when type = 'REVIEW' then
			'2000-04-01'::date
		else 
			'2000-01-01'::date
	end)::date as series_start,
	(case
		when type = 'QUARTER' then
			'3 month'
		when type = 'FRIDAY_THE_13TH' then 
			'1 week'
		when type = 'REVIEW' then
			'6 month'
		else concat('1 ', "type")
	end)::interval as inte,
	date_from as s, date_to as t FROM "input"), 
RAW_SERIES as (SELECT type, inte, s, t, generate_series(series_start, t, inte) as date_from from range_values),
SERIES as (
	SELECT type, inte, s, t, date_from from RAW_SERIES where date_from >= s and (type <> 'FRIDAY_THE_13TH' or extract (day from date_from) = 13)
		union all
	SELECT type, inte, s, t, s as date_from from range_values
	    union all
	SELECT type, inte, s, t, t + '1 day'::interval as date_from from range_values
),
INDEXED_INTERVALS as (select row_number() over (order by date_from) as i, inte, s, t, date_from from SERIES),
INTERVALS as (
	select orig.i, orig.inte, orig.s, orig.t, orig.date_from, dup.date_from - '1 day'::interval as date_to from INDEXED_INTERVALS orig
		inner join INDEXED_INTERVALS dup on orig.i + 1 = dup.i

)
select date_from::date, date_to::date from INTERVALS where date_from <= date_to  order by date_from
