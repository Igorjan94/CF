CREATE FUNCTION inter(integer, integer, integer, integer, integer, integer, integer, integer)
RETURNS boolean AS 'select sign($1*$4-$2*$3-$1*$6+$2*$5+$3*$6-$4*$5) != sign($1*$4-$2*$3-$1*$8+$2*$7+$3*$8-$4*$7)'
LANGUAGE SQL
IMMUTABLE
RETURNS NULL ON NULL INPUT;

select id 
    from Points
        where _X_LEFT_ <= "x" and "x" <= _X_RIGHT_ and _Y_BOTTOM_ <= "y" and "y" <= _Y_TOP_
union all

select id
    from Lines
        where 
            (_X_LEFT_ <= "begin_x" and "begin_x" <= _X_RIGHT_ and _Y_BOTTOM_ <= "begin_y" and "begin_y" <= _Y_TOP_)
                or (_X_LEFT_ <= "end_x" and "end_x" <= _X_RIGHT_ and _Y_BOTTOM_ <= "end_y" and "end_y" <= _Y_TOP_)
                or inter("begin_x", "begin_y", "end_x", "end_y", _X_LEFT_, _Y_BOTTOM_, _X_LEFT_, _Y_TOP_)
                or inter("begin_x", "begin_y", "end_x", "end_y", _X_LEFT_, _Y_BOTTOM_, _X_RIGHT_, _Y_BOTTOM_)
                or inter("begin_x", "begin_y", "end_x", "end_y", _X_RIGHT_, _Y_TOP_, _X_LEFT_, _Y_TOP_)
                or inter("begin_x", "begin_y", "end_x", "end_y", _X_RIGHT_, _Y_TOP_, _X_RIGHT_, _Y_BOTTOM_);

select id 
    from Points
        where 1 <= "x" and "x" <= 2 and 1 <= "y" and "y" <= 2
union all

select id
    from Lines
        where 
            (1 <= "begin_x" and "begin_x" <= 2 and 1 <= "begin_y" and "begin_y" <= 2)
                or
            (1 <= "end_x" and "end_x" <= 2 and 1 <= "end_y" and "end_y" <= _Y_TOP)

