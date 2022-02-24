./A < ./b_better_start_small.in.txt > B.out
echo -e "$(cat B.out | nl | tail -1 | awk '{print $1 / 2;}')\n$(cat B.out)" > B.out2

./A < ./c_collaboration.in.txt > C.out
echo -e "$(cat C.out | nl | tail -1 | awk '{print $1 / 2;}')\n$(cat C.out)" > C.out2

./A < ./d_dense_schedule.in.txt > D.out
echo -e "$(cat D.out | nl | tail -1 | awk '{print $1 / 2;}')\n$(cat D.out)" > D.out2

./A < ./e_exceptional_skills.in.txt > E.out
echo -e "$(cat E.out | nl | tail -1 | awk '{print $1 / 2;}')\n$(cat E.out)" > E.out2

./A < ./f_find_great_mentors.in.txt > F.out
echo -e "$(cat F.out | nl | tail -1 | awk '{print $1 / 2;}')\n$(cat F.out)" > F.out2

