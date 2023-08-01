create table links
	(movieId		int,
	 imdbId		varchar(7),
	 tmdbId		varchar(7)
	);
create table movies
	(movieId		int,
	 title		varchar(200),
	 genres		varchar(200)
	);	
	
create table ratings
	(userId		varchar(7),
	 movieId		int,
	 rating 	numeric(2,1),
	 timestamp		int
	);
		
create table tags
	(userId		varchar(7),
	 movieId		int,
	 tag 	varchar(100),
	 timestamp		int
	);


