DROP TABLE IF EXISTS ball_by_ball;
DROP TABLE IF EXISTS umpire_match;
DROP TABLE IF EXISTS player_match;
DROP TABLE IF EXISTS match;
DROP TABLE IF EXISTS owner;
DROP TABLE IF EXISTS venue;
DROP TABLE IF EXISTS player;
DROP TABLE IF EXISTS umpire;
DROP TABLE IF EXISTS team;

CREATE TABLE team (
    team_id INT,
    team_name TEXT,
    PRIMARY KEY(team_id)
);

CREATE TABLE umpire (
    umpire_id INT,
    umpire_name TEXT,
    country_name TEXT,
    PRIMARY KEY(umpire_id)
);

CREATE TABLE player (
    player_id INT,
    player_name TEXT, 
    dob DATE,
    batting_hand TEXT,
    bowling_skill TEXT,
    country_name TEXT,
    PRIMARY KEY(player_id)
);

CREATE TABLE venue (
    venue_id INT,
    venue_name TEXT,
    city_name TEXT,
    country_name TEXT,
    capacity INT,
    PRIMARY KEY(venue_id)
);

CREATE TABLE owner (
    owner_id INT,
    owner_name TEXT,
    owner_type TEXT,
    team_id INT,
    stake INT,
    PRIMARY KEY(owner_id),
    FOREIGN KEY(team_id) REFERENCES team(team_id) ON DELETE set null
);

CREATE TABLE match (
    match_id INT,
    season_year INT,
    team1 INT,
    team2 INT,
    venue_id INT,
    toss_winner INT,
    match_winner INT,
    toss_name TEXT,
    win_type TEXT,
    man_of_match INT,
    win_margin INT,
    attendance INT,
    PRIMARY KEY(match_id),
    FOREIGN KEY(venue_id) REFERENCES venue ON DELETE set null,
    FOREIGN KEY(team1) REFERENCES team ON DELETE set null,
    FOREIGN KEY(team2) REFERENCES team ON DELETE set null,
    FOREIGN KEY(toss_winner) REFERENCES team ON DELETE set null,
    FOREIGN KEY(match_winner) REFERENCES team ON DELETE set null,
    FOREIGN KEY(man_of_match) REFERENCES player ON DELETE set null
);

CREATE TABLE player_match (
    playermatch_key bigINT,
    match_id INT,
    player_id INT,
    role_desc TEXT,
    team_id INT ,
    PRIMARY KEY(playermatch_key),
    FOREIGN KEY(match_id) REFERENCES match ON DELETE set null,
    FOREIGN KEY(player_id) REFERENCES player ON DELETE set null,
    FOREIGN KEY(team_id) REFERENCES team ON DELETE set null
);

CREATE TABLE umpire_match (
    umpirematch_key bigINT,
    match_id INT,
    umpire_id INT,
    role_desc TEXT,
    PRIMARY KEY(umpirematch_key),
    FOREIGN KEY(match_id) REFERENCES match ON DELETE set null,
    FOREIGN KEY(umpire_id) REFERENCES umpire ON DELETE set null
);

CREATE TABLE ball_by_ball (
    match_id INT,
    innings_no INT,
    over_id INT,
    ball_id INT,
    runs_scored INT,
    extra_runs INT,
    out_type TEXT,
    striker INT,
    non_striker INT,
    bowler INT,
    PRIMARY KEY(match_id, innings_no, over_id, ball_id),
    FOREIGN KEY(match_id) REFERENCES match ON DELETE set null,
    FOREIGN KEY(striker) REFERENCES player ON DELETE set null,
    FOREIGN KEY(non_striker) REFERENCES player ON DELETE set null,
    FOREIGN KEY(bowler) REFERENCES player ON DELETE set null
);
