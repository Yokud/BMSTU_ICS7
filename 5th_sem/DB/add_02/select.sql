with extra_table as (
    select department, fio, date, status,
           min(date) over (partition by department, fio, status) as min_date,
           max(date) over (partition by department, fio, status) as max_date
    from romashka
    order by fio, max_date
)
select distinct  department, fio, min_date as DateFrom, max_date as DateTo, status
from extra_table
order by department desc, DateFrom;