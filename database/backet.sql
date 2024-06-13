create table COMPANY
(id int(5) not null,
 name varchar(50) not null unique,
 primary key(id));

create table MAP
(id int(5) not null,
 lat double(10,10),
 lng double(10,10),
 image varchar(50) unique,
 floor  int(5),
 primary key(id));

create table employee
(id int(5) not null,
 name varchar(30) not null,
 pass varchar(100) not null,
 co_id int(5) unique,
 primary key(id),
 foreign key(co_id) references COMPANY(id)
); 

create table trash
(id int(5) auto_increment,
 name varchar(20) unique,
 situ char(2) not null,
 co_id int(5) not null,
 em_id int(5) ,
 primary key(id),
 foreign key(co_id) references company(id),
 foreign key(em_id) references employee(id));
