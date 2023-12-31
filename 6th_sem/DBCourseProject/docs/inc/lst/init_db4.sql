	if months_diff > 18 then
		delete from CostStory where AvailabilityID = new_avail_id and ID = old_date_id;
	end if;
	return new;
end
$$ language plpgsql;

drop trigger update_coststory on CostStory;
create trigger update_coststory after insert on CostStory
	for each row execute function remove_too_old_coststory();

create user "user";
grant connect on database spsr_lt_db to "user";
grant usage on schema public to "user";
grant select on table Shops, Products, Availability, Costs to "user";
alter user "user" with password 'user';

create user "analyst" with password 'analyst';
grant connect on database spsr_lt_db to "analyst";
grant usage on schema public to "analyst";
grant select on table Shops, Products, Availability, CostStory to "analyst";
grant select on table Costs to "analyst";

create user "admin" with password 'admin';
grant connect on database spsr_lt_db to "admin";
grant usage on schema public to "admin";
grant select, insert, update, delete on all tables in schema public to "admin";

drop user if exists "user";
drop user if exists "analyst";
drop user if exists "admin";