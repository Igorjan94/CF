select person_name, count(kurultai_id) from (SELECT
  PR.person_name, PR.kurultai_id, count(KV.id) as visitors
FROM person_roles PR 
join kurultai_visitors KV on(KV.kurultai_id = pr.kurultai_id)
where is_owner = true
	and not exists (select * from kurultai_visitor_sessions kvs where kvs.kurultai_visitor_id = kv.id and kvs.exit_time <= (kvs.enter_time + INTERVAL '30 seconds'))
group by pr.person_name, pr.kurultai_id) as alias where visitors >= 10 group by person_name
order by count desc, person_name asc limit 10 
