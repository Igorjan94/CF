select id from pickup_point zzz where branded_since = :targetDate
 	and not exists (select pickup_point_id from brand_data bd where bd.pickup_point_id in (
 		with recursive name_tree as (
	   	select id, prev_id
	   from pickup_point
	   where id = zzz.id -- this is the starting point you want in your recursion
	   union all
	   select c.id, c.prev_id
	   from pickup_point c
	     join name_tree p on p.prev_id = c.id and c.id <> zzz.id  -- this is the recursion
	) 
	select id from name_tree)
)
